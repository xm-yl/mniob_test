/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2023/04/24.
//

#include <limits>
#include "storage/trx/mvcc_trx.h"
#include "storage/field/field.h"
#include "storage/clog/clog.h"
#include "storage/db/db.h"
#include "storage/clog/clog.h"

using namespace std;

MvccTrxKit::~MvccTrxKit()
{
  vector<Trx *> tmp_trxes;
  tmp_trxes.swap(trxes_);
  
  for (Trx *trx : tmp_trxes) {
    delete trx;
  }
}

RC MvccTrxKit::init()
{
  fields_ = vector<FieldMeta>{
    FieldMeta("__trx_xid_begin", AttrType::INTS, 0/*attr_offset*/, 4/*attr_len*/, false/* nullable*/, false/*visible*/),
    FieldMeta("__trx_xid_end",   AttrType::INTS, 0/*attr_offset*/, 4/*attr_len*/, false/* nullable*/, false/*visible*/)
  };

  LOG_INFO("init mvcc trx kit done.");
  return RC::SUCCESS;
}

const vector<FieldMeta> *MvccTrxKit::trx_fields() const
{
  return &fields_;
}

int32_t MvccTrxKit::next_trx_id()
{
  return ++current_trx_id_;
}

int32_t MvccTrxKit::max_trx_id() const
{
  return numeric_limits<int32_t>::max() / 10;
}

Trx *MvccTrxKit::create_trx(CLogManager *log_manager)
{
  Trx *trx = new MvccTrx(*this, log_manager);
  if (trx != nullptr) {
    lock_.lock();
    trxes_.push_back(trx);
    lock_.unlock();
  }
  return trx;
}

Trx *MvccTrxKit::create_trx(int32_t trx_id)
{
  Trx *trx = new MvccTrx(*this, trx_id);
  if (trx != nullptr) {
    lock_.lock();
    trxes_.push_back(trx);
    if (current_trx_id_ < trx_id) {
      current_trx_id_ = trx_id;
    }
    lock_.unlock();
  }
  return trx;
}

void MvccTrxKit::destroy_trx(Trx *trx)
{
  lock_.lock();
  for (auto iter = trxes_.begin(), itend = trxes_.end(); iter != itend; ++iter) {
    if (*iter == trx) {
      trxes_.erase(iter);
      break;
    }
  }
  lock_.unlock();

  delete trx;
}

Trx *MvccTrxKit::find_trx(int32_t trx_id)
{
  lock_.lock();
  for (Trx *trx : trxes_) {
    if (trx->id() == trx_id) {
      lock_.unlock();
      return trx;
    }
  }
  lock_.unlock();

  return nullptr;
}

void MvccTrxKit::all_trxes(std::vector<Trx *> &trxes)
{
  lock_.lock();
  trxes = trxes_;
  lock_.unlock();
}

////////////////////////////////////////////////////////////////////////////////

MvccTrx::MvccTrx(MvccTrxKit &kit, CLogManager *log_manager) : trx_kit_(kit), log_manager_(log_manager)
{}

MvccTrx::MvccTrx(MvccTrxKit &kit, int32_t trx_id) : trx_kit_(kit), trx_id_(trx_id)
{
  started_ = true;
  recovering_ = true;
}

MvccTrx::~MvccTrx()
{
}


void MvccTrx::create_index_keys(Index* index, Record &record, char* &l_key, char* &r_key, int &attr_len) {
  auto metas = index->field_metas();

  for(int i = 0;i < metas.size(); i++){
    attr_len += metas[i].len();
  }
  //初始化字段拼接是index里面的record数据
  l_key = new char[attr_len];
  r_key = new char[attr_len];

  memset(l_key, 0, attr_len);
  memset(r_key, 0, attr_len);

  int offset = 0;
  for(int i = 0;i < int(metas.size()) - 1; i++){
    int field_len = metas[i].len();
    int field_offset = metas[i].offset();
    memcpy(l_key + offset, record.data() + field_offset, field_len);
    memcpy(r_key + offset, record.data() + field_offset, field_len);
    offset += field_len;
  }
  int l_least = -trx_kit_.max_trx_id();
  int r_most = trx_kit_.max_trx_id();

  memcpy(l_key + offset, &l_least, sizeof(l_least));

  memcpy(r_key + offset, &r_most, sizeof(r_most));
}

bool MvccTrx::unique_index_dup(Table* table, Record & record) {
  Field begin_field;
  Field end_field;
  trx_fields(table, begin_field, end_field);

  auto indexes = table->indexes();
  for (auto & index: indexes) {
    if (index->is_unique() == false) continue;

    char* l = nullptr, *r = nullptr;
    int len = 0;

    create_index_keys(index, record, l, r, len);
    auto scanner = index->create_scanner(l, len, true, r, len, true);
    if(scanner == nullptr) continue;

    RID rid;
    Record index_record;
    RC rc = RC::SUCCESS;
    while((rc = scanner->next_entry(&rid)) == RC::SUCCESS) {
      table->get_record(rid, index_record);

      int end_xid = end_field.get_int(index_record);

      if (end_xid > 0) {
        if (trx_id_ <= end_xid) {
          rc = RC::SUCCESS;
        } else {
          rc = RC::RECORD_INVISIBLE;
        }
      } else {
        if(-end_xid == trx_id_) {
          //delete by my self;
          rc = RC::RECORD_INVISIBLE;
        } else {
          rc = RC::SUCCESS;
        }
      }

      if(rc == RC::SUCCESS) {
        delete []l;
        delete []r;
        scanner->destroy();
        LOG_DEBUG("record dup in insert");
        return true;
      }
    }

    scanner->destroy();
    delete []l;
    delete []r;
  }
  return false;
}


RC MvccTrx::insert_record(Table *table, Record &record)
{
  Field begin_field;
  Field end_field;
  trx_fields(table, begin_field, end_field);

  begin_field.set_int(record, -trx_id_);
  end_field.set_int(record, trx_kit_.max_trx_id());

  if (this->unique_index_dup(table, record) == true) {
      LOG_DEBUG("record dup in insert");
    return RC::RECORD_DUPLICATE_KEY;
  }

  RC rc = table->insert_record(record);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to insert record into table. rc=%s", strrc(rc));
    return rc;
  }

  rc = log_manager_->append_log(CLogType::INSERT, trx_id_, table->table_id(), record.rid(), record.len(), 0/*offset*/, record.data());
  ASSERT(rc == RC::SUCCESS, "failed to append insert record log. trx id=%d, table id=%d, rid=%s, record len=%d, rc=%s",
      trx_id_, table->table_id(), record.rid().to_string().c_str(), record.len(), strrc(rc));

  pair<OperationSet::iterator, bool> ret = 
        operations_.insert(Operation(Operation::Type::INSERT, table, record.rid()));
  if (!ret.second) {
    rc = RC::INTERNAL;
    LOG_WARN("failed to insert operation(insertion) into operation set: duplicate");
  }
  return rc;
}

RC MvccTrx::delete_record(Table * table, Record &record)
{
  Field begin_field;
  Field end_field;
  trx_fields(table, begin_field, end_field);

  [[maybe_unused]] int32_t end_xid = end_field.get_int(record);
  /// 在删除之前，第一次获取record时，就已经对record做了对应的检查，并且保证不会有其它的事务来访问这条数据
  ASSERT(end_xid > 0, "concurrency conflit: other transaction is updating this record. end_xid=%d, current trx id=%d, rid=%s",
         end_xid, trx_id_, record.rid().to_string().c_str());
  if (end_xid != trx_kit_.max_trx_id()) {
    // 当前不是多版本数据中的最新记录，不需要删除
    return RC::SUCCESS;
  }

  for(auto &index: table->indexes()) {
    if(index->is_unique() == false) continue;
    index->delete_entry(record.data(), &record.rid());
  }

  end_field.set_int(record, -trx_id_);

  for(auto &index: table->indexes()) {
    if(index->is_unique() == false) continue;
    index->insert_entry(record.data(), &record.rid());
  }
  
  RC rc = log_manager_->append_log(CLogType::DELETE, trx_id_, table->table_id(), record.rid(), 0, 0, nullptr);
  ASSERT(rc == RC::SUCCESS, "failed to append delete record log. trx id=%d, table id=%d, rid=%s, record len=%d, rc=%s",
      trx_id_, table->table_id(), record.rid().to_string().c_str(), record.len(), strrc(rc));

  operations_.insert(Operation(Operation::Type::DELETE, table, record.rid()));

  return RC::SUCCESS;
}

RC MvccTrx::update_record(Table *table, Record &record, std::vector<const Value*> update_values,std::vector<const FieldMeta*> update_fields) {
  Field begin_field;
  Field end_field;
  trx_fields(table, begin_field, end_field);

  Record updated_record;
  //make a copy of original and update it
  RC rc = RC::SUCCESS;
  const TableMeta &table_meta_ = table->table_meta();
  char * r = new char[table_meta_.record_size()];
  memcpy(r, record.data(), table_meta_.record_size());

  // update the values one by one.
  const int sys_field_num = table_meta_.sys_field_num();
  int sys_len = 0;
  for(int i = 0;i < sys_field_num; i++) sys_len += table_meta_.field(i)->len();
  const int field_num = table_meta_.field_num() - sys_field_num;
  for(int i = 0; i < update_fields.size(); i++ ){
    AttrType update_value_type = update_values.at(i)->attr_type();
    const FieldMeta *update_field_meta = update_fields.at(i);
    int update_location = sys_len;
    int update_field_length = 0;
    
    //Get the offset of updating values.(update_location)
    for(int j = 0; j < field_num;j++){
      const FieldMeta *field_meta = table_meta_.field(j + sys_field_num);
      AttrType field_type = field_meta->type();
      const char * field_name = field_meta->name();
    
      //check the validation of the value type and name.
      if(strcmp(field_name,update_field_meta->name())==0 && field_type==update_value_type){
          update_field_length = field_meta->len();
          break;
      }
      update_location += field_meta->len();
    }
    
    // LOG_DEBUG("[Table:update_record] before-> r[0]:%d, r[1]:%d, r[2]:%d, r[3]:%d, value:%d", *(r), *(r+4), *(r+8), *(r+12), *(value->data()));
    // update by memcpy
    char *tmp = new char[update_field_length];
    memset(tmp, 0, sizeof(char) * update_field_length);
    memcpy(tmp, update_values.at(i)->data(), min(update_field_length, update_values.at(i)->length()));
    // LOG_DEBUG("field_length is %d,Update location is %d",update_field_length,update_location);
    memcpy(r + update_location, tmp, update_field_length);
    delete []tmp;
  }

  if(OB_FAIL(rc)) {
    //LOG_WARN("mvcc update record failed: rc", strrc(rc));
    return rc;
  }

  updated_record.set_data_owner(r, table_meta_.record_size());
  begin_field.set_int(updated_record, -trx_id_);
  end_field.set_int(updated_record, trx_kit_.max_trx_id());


  for(auto &index: table->indexes()) {
    if(index->is_unique() == false) continue;
    index->delete_entry(record.data(), &record.rid());
  }

  if (this->unique_index_dup(table, updated_record) == true) {
    for(auto &index: table->indexes()) {
      if(index->is_unique() == false) continue;
      index->insert_entry(record.data(), &record.rid());
    }
    LOG_DEBUG("record dup in insert");
    return RC::RECORD_DUPLICATE_KEY;
  }


  //delete
  end_field.set_int(record, -trx_id_);
  for(auto &index: table->indexes()) {
    if(index->is_unique() == false) continue;
    index->insert_entry(record.data(), &record.rid());
  }

  rc = log_manager_->append_log(CLogType::DELETE, trx_id_, table->table_id(), record.rid(), 0, 0, nullptr);
  operations_.insert(Operation(Operation::Type::DELETE, table, record.rid()));

  //insert
  rc = table->insert_record(updated_record);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to insert record into table. rc=%s", strrc(rc));
    return rc;
  }

  rc = log_manager_->append_log(CLogType::INSERT, trx_id_, table->table_id(), updated_record.rid(), 
    updated_record.len(), 0/*offset*/, updated_record.data());
  pair<OperationSet::iterator, bool> ret = 
        operations_.insert(Operation(Operation::Type::INSERT, table, updated_record.rid()));
  if (!ret.second) {
    rc = RC::INTERNAL;
    LOG_WARN("failed to insert operation(insertion) into operation set: duplicate");
  }

  if(OB_FAIL(rc)) {
    LOG_WARN("mvcc update record failed: rc", strrc(rc));
  }
  return rc;
}

RC MvccTrx::get_rc(int32_t begin_xid, int32_t end_xid, bool readonly) {
  RC rc = RC::SUCCESS;
  if (begin_xid > 0 && end_xid > 0) {
    if (trx_id_ >= begin_xid && trx_id_ <= end_xid) {
      rc = RC::SUCCESS;
    } else {
      rc = RC::RECORD_INVISIBLE;
    }
  } else if (begin_xid < 0) {
    // begin xid 小于0说明是刚插入而且没有提交的数据
    rc = (-begin_xid == trx_id_) ? RC::SUCCESS : RC::RECORD_INVISIBLE;
  } else if (end_xid < 0) {
    // end xid 小于0 说明是正在删除但是还没有提交的数据
    if (readonly) {
      // 如果 -end_xid 就是当前事务的事务号，说明是当前事务删除的
      rc = (-end_xid != trx_id_) ? RC::SUCCESS : RC::RECORD_INVISIBLE;
    } else {
      // 如果当前想要修改此条数据，并且不是当前事务删除的，简单的报错
      // 这是事务并发处理的一种方式，非常简单粗暴。其它的并发处理方法，可以等待，或者让客户端重试
      // 或者等事务结束后，再检测修改的数据是否有冲突
      rc = (-end_xid != trx_id_) ? RC::LOCKED_CONCURRENCY_CONFLICT : RC::RECORD_INVISIBLE;
    }
  }
  return rc;
}

RC MvccTrx::visit_record(Table *table, Record &record, bool readonly)
{
  Field begin_field;
  Field end_field;
  trx_fields(table, begin_field, end_field);

  int32_t begin_xid = begin_field.get_int(record);
  int32_t end_xid = end_field.get_int(record);

  return get_rc(begin_xid, end_xid, readonly);
}

/**
 * @brief 获取指定表上的事务使用的字段
 * 
 * @param table 指定的表
 * @param begin_xid_field 返回处理begin_xid的字段
 * @param end_xid_field   返回处理end_xid的字段
 */
void MvccTrx::trx_fields(Table *table, Field &begin_xid_field, Field &end_xid_field) const
{
  const TableMeta &table_meta = table->table_meta();
  const std::pair<const FieldMeta *, int> trx_fields = table_meta.trx_fields();
  ASSERT(trx_fields.second >= 2, "invalid trx fields number. %d", trx_fields.second);

  begin_xid_field.set_table(table);
  begin_xid_field.set_field(&trx_fields.first[0]);
  end_xid_field.set_table(table);
  end_xid_field.set_field(&trx_fields.first[1]);
}

RC MvccTrx::start_if_need()
{
  if (!started_) {
    ASSERT(operations_.empty(), "try to start a new trx while operations is not empty");
    trx_id_ = trx_kit_.next_trx_id();
    LOG_DEBUG("current thread change to new trx with %d", trx_id_);
    RC rc = log_manager_->begin_trx(trx_id_);
    ASSERT(rc == RC::SUCCESS, "failed to append log to clog. rc=%s", strrc(rc));
    started_ = true;
  }
  return RC::SUCCESS;
}

RC MvccTrx::commit()
{
  int32_t commit_id = trx_kit_.next_trx_id();
  return commit_with_trx_id(commit_id);
}

RC MvccTrx::commit_with_trx_id(int32_t commit_xid)
{
  // TODO 这里存在一个很大的问题，不能让其他事务一次性看到当前事务更新到的数据或同时看不到
  RC rc = RC::SUCCESS;
  started_ = false;
  
  for (const Operation &operation : operations_) {
    switch (operation.type()) {
      case Operation::Type::INSERT: {
        RID rid(operation.page_num(), operation.slot_num());
        Table *table = operation.table();
        Field begin_xid_field, end_xid_field;
        trx_fields(table, begin_xid_field, end_xid_field);

        auto record_updater = [this, &begin_xid_field, commit_xid, table](Record &record) {
          LOG_DEBUG("before commit insert record. trx id=%d, begin xid=%d, commit xid=%d, lbt=%s",
                    trx_id_, begin_xid_field.get_int(record), commit_xid, lbt());
          ASSERT(begin_xid_field.get_int(record) == -this->trx_id_, 
                 "got an invalid record while committing. begin xid=%d, this trx id=%d", 
                 begin_xid_field.get_int(record), trx_id_);

          RC rc = RC::SUCCESS;
          begin_xid_field.set_int(record, commit_xid);
        };

        rc = operation.table()->visit_record(rid, false/*readonly*/, record_updater);
        ASSERT(rc == RC::SUCCESS, "failed to get record while committing. rid=%s, rc=%s",
               rid.to_string().c_str(), strrc(rc));
      } break;

      case Operation::Type::DELETE: {
        Table *table = operation.table();
        RID rid(operation.page_num(), operation.slot_num());
        
        Field begin_xid_field, end_xid_field;
        trx_fields(table, begin_xid_field, end_xid_field);

        auto record_updater = [this, &end_xid_field, commit_xid, table](Record &record) {
          (void)this;
          ASSERT(end_xid_field.get_int(record) == -trx_id_, 
                 "got an invalid record while committing. end xid=%d, this trx id=%d", 
                 end_xid_field.get_int(record), trx_id_);
                
          for(auto &index: table->indexes()) {
            if(index->is_unique() == false) continue;
            index->delete_entry(record.data(), &record.rid());
          }

          end_xid_field.set_int(record, commit_xid);

          for(auto &index: table->indexes()) {
            if(index->is_unique() == false) continue;
            index->insert_entry(record.data(), &record.rid());
          }
        };

        rc = operation.table()->visit_record(rid, false/*readonly*/, record_updater);
        ASSERT(rc == RC::SUCCESS, "failed to get record while committing. rid=%s, rc=%s",
               rid.to_string().c_str(), strrc(rc));
      } break;

      default: {
        ASSERT(false, "unsupported operation. type=%d", static_cast<int>(operation.type()));
      }
    }
  }

  operations_.clear();

  if (!recovering_) {
    rc = log_manager_->commit_trx(trx_id_, commit_xid);
  }
  LOG_TRACE("append trx commit log. trx id=%d, commit_xid=%d, rc=%s", trx_id_, commit_xid, strrc(rc));
  return rc;
}

RC MvccTrx::rollback()
{
  RC rc = RC::SUCCESS;
  started_ = false;
  
  for (const Operation &operation : operations_) {
    switch (operation.type()) {
      case Operation::Type::INSERT: {
        RID rid(operation.page_num(), operation.slot_num());
        Record record;
        Table *table = operation.table();
        // TODO 这里虽然调用get_record好像多次一举，而且看起来放在table的实现中更好，
        // 而且实际上trx应该记录下来自己曾经插入过的数据
        // 也就是不需要从table中获取这条数据，可以直接从当前内存中获取
        // 这里也可以不删除，仅仅给数据加个标识位，等垃圾回收器来收割也行
        rc = table->get_record(rid, record); 
        ASSERT(rc == RC::SUCCESS, "failed to get record while rollback. rid=%s, rc=%s", 
               rid.to_string().c_str(), strrc(rc));
        rc = table->delete_record(record);
        ASSERT(rc == RC::SUCCESS, "failed to delete record while rollback. rid=%s, rc=%s",
              rid.to_string().c_str(), strrc(rc));
      } break;

      case Operation::Type::DELETE: {
        Table *table = operation.table();
        RID rid(operation.page_num(), operation.slot_num());
        
        ASSERT(rc == RC::SUCCESS, "failed to get record while rollback. rid=%s, rc=%s",
              rid.to_string().c_str(), strrc(rc));
        Field begin_xid_field, end_xid_field;
        trx_fields(table, begin_xid_field, end_xid_field);

        auto record_updater = [this, &end_xid_field, table](Record &record) {
          ASSERT(end_xid_field.get_int(record) == -trx_id_, 
                "got an invalid record while rollback. end xid=%d, this trx id=%d", 
                end_xid_field.get_int(record), trx_id_);

          RC rc = RC::SUCCESS;
          for(auto index: table->indexes()) {
            if(index->is_unique() == false) continue;
            rc = index->delete_entry(record.data(), &record.rid());
            ASSERT(rc == RC::SUCCESS, "failed to get record while rollback. rid=%s, rc=%s", 
                rid.to_string().c_str(), strrc(rc));
          }

          end_xid_field.set_int(record, trx_kit_.max_trx_id());

          for(auto index: table->indexes()) {
            if(index->is_unique() == false) continue;
            rc = index->insert_entry(record.data(), &record.rid());
            ASSERT(rc == RC::SUCCESS, "failed to get record while rollback. rid=%s, rc=%s", 
                rid.to_string().c_str(), strrc(rc));
          }
        };
        
        rc = table->visit_record(rid, false/*readonly*/, record_updater);
        ASSERT(rc == RC::SUCCESS, "failed to get record while committing. rid=%s, rc=%s",
               rid.to_string().c_str(), strrc(rc));
      } break;

      default: {
        ASSERT(false, "unsupported operation. type=%d", static_cast<int>(operation.type()));
      }
    }
  }

  operations_.clear();

  if (!recovering_) {
    rc = log_manager_->rollback_trx(trx_id_);
  }
  LOG_TRACE("append trx rollback log. trx id=%d, rc=%s", trx_id_, strrc(rc));
  return rc;
}

RC find_table(Db *db, const CLogRecord &log_record, Table *&table)
{
  switch (clog_type_from_integer(log_record.header().type_)) {
    case CLogType::INSERT:
    case CLogType::DELETE: {
      const CLogRecordData &data_record = log_record.data_record();
      table = db->find_table(data_record.table_id_);
      if (nullptr == table) {
        LOG_WARN("no such table to redo. table id=%d, log record=%s",
                 data_record.table_id_, log_record.to_string().c_str());
        return RC::SCHEMA_TABLE_NOT_EXIST;
      }
    } break;
    default:{
      // do nothing
    } break;
  }
  return RC::SUCCESS;
}

RC MvccTrx::redo(Db *db, const CLogRecord &log_record)
{
  Table *table = nullptr;
  RC rc = find_table(db, log_record, table);
  if (OB_FAIL(rc)) {
    return rc;
  }

  switch (log_record.log_type()) {
    case CLogType::INSERT: {
      const CLogRecordData &data_record = log_record.data_record();
      Record record;
      record.set_data(const_cast<char *>(data_record.data_), data_record.data_len_);
      record.set_rid(data_record.rid_);
      RC rc = table->recover_insert_record(record);
      if (OB_FAIL(rc)) {
        LOG_WARN("failed to recover insert. table=%s, log record=%s, rc=%s",
                 table->name(), log_record.to_string().c_str(), strrc(rc));
        return rc;
      }
      operations_.insert(Operation(Operation::Type::INSERT, table, record.rid()));
    } break;

    case CLogType::DELETE: {
      const CLogRecordData &data_record = log_record.data_record();
      Field begin_field;
      Field end_field;
      trx_fields(table, begin_field, end_field);

      auto record_updater = [this, &end_field](Record &record) {
        (void)this;
        ASSERT(end_field.get_int(record) == trx_kit_.max_trx_id(), 
               "got an invalid record while committing. end xid=%d, this trx id=%d", 
               end_field.get_int(record), trx_id_);
                
        end_field.set_int(record, -trx_id_);
      };

      RC rc = table->visit_record(data_record.rid_, false/*readonly*/, record_updater);
      ASSERT(rc == RC::SUCCESS, "failed to get record while committing. rid=%s, rc=%s",
             data_record.rid_.to_string().c_str(), strrc(rc));
      
      operations_.insert(Operation(Operation::Type::DELETE, table, data_record.rid_));
    } break;

    case CLogType::MTR_COMMIT: {
      const CLogRecordCommitData &commit_record = log_record.commit_record();
      commit_with_trx_id(commit_record.commit_xid_);
    } break;

    case CLogType::MTR_ROLLBACK: {
      rollback();
    } break;
    
    default: {
      ASSERT(false, "unsupported redo log. log_record=%s", log_record.to_string().c_str());
      return RC::INTERNAL;
    } break;
  }

  return RC::SUCCESS;
}

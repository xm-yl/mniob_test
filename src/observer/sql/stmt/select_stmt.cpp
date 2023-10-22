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
// Created by Wangyunlai on 2022/6/6.
//

#include "sql/stmt/select_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "sql/parser/parse_defs.h"

SelectStmt::~SelectStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

static void wildcard_fields(Table *table, std::vector<Field> &field_metas, AggrOp aggr_op = AggrOp::NO_AGGR_OP)
{
  ASSERT(aggr_op==AggrOp::NO_AGGR_OP || aggr_op==AggrOp::AGG_COUNT,"Wildcard field can only be aggrgated with func COUNT");
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num();
  if(aggr_op==AggrOp::AGG_COUNT){
    //auto star_num = Field::get_next_star_num();
    int i = table_meta.sys_field_num();
    field_metas.push_back(Field(table, table_meta.field(i),aggr_op,true));
    //Field::add_next_star_num();
  }
  else if(aggr_op==AggrOp::NO_AGGR_OP){
    for (int i = table_meta.sys_field_num(); i < field_num; i++) {
      field_metas.push_back(Field(table, table_meta.field(i)));
    }
  }
}

RC SelectStmt::create(Db *db, const SelectSqlNode &select_sql, Stmt *&stmt)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  // collect tables in `from` statement
  std::vector<Table *> tables;
  std::unordered_map<std::string, Table *> table_map;
  for (size_t i = 0; i < select_sql.relations.size(); i++) {
    const char *table_name = select_sql.relations[i].c_str();
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    tables.push_back(table);
    table_map.insert(std::pair<std::string, Table *>(table_name, table));
  }

  // collect query fields in `select` statement
  std::vector<Field> query_fields;
  std::vector<AggrOp> attr_ops;
  for (int i = static_cast<int>(select_sql.attributes.size()) - 1; i >= 0; i--) {
    const RelAttrSqlNode &relation_attr = select_sql.attributes[i];
    const AggrOp aggr_op = relation_attr.aggr_op;
    LOG_DEBUG("Total %d aggr_op , this is the %d th aggr_op with op %d",select_sql.attributes.size(),i,aggr_op);
    attr_ops.push_back(relation_attr.aggr_op);
    //若表名为空，且查询为*，则全部查                             select * from id1，id2 ...
    if (common::is_blank(relation_attr.relation_name.c_str()) &&
        0 == strcmp(relation_attr.attribute_name.c_str(), "*")) {
      for (Table *table : tables) {
        if(aggr_op!=AggrOp::NO_AGGR_OP && aggr_op!= AggrOp::AGG_COUNT){
          LOG_WARN("Aggregation Operation Not Allowd for *");
          return RC::SCHEMA_FIELD_TYPE_MISMATCH;
        }
        wildcard_fields(table, query_fields , aggr_op);
      }
    //若表名不空，即table.id 的查询方式                           select *.* from id1,id2 ...
    //表名为*时，field也必须为*，即*.* 查询所有表的所有id          select id1.*, id2.*from id1,id2
    //表名不是*时，首先匹配表名，其次组成查询Field(table,id)【若id为*时就wildcard】
    } else if (!common::is_blank(relation_attr.relation_name.c_str())) {
      const char *table_name = relation_attr.relation_name.c_str();
      const char *field_name = relation_attr.attribute_name.c_str();

      if (0 == strcmp(table_name, "*")) {
        if (0 != strcmp(field_name, "*")) {
          LOG_WARN("invalid field name while table is *. attr=%s", field_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        for (Table *table : tables) {
          if(aggr_op!=AggrOp::NO_AGGR_OP && aggr_op!= AggrOp::AGG_COUNT){
          LOG_WARN("Aggregation Operation Not Allowd for *");
          return RC::SCHEMA_FIELD_TYPE_MISMATCH;
          }
          wildcard_fields(table, query_fields, aggr_op);
        }
      } else {
        auto iter = table_map.find(table_name);
        if (iter == table_map.end()) {
          LOG_WARN("no such table in from list: %s", table_name);
          return RC::SCHEMA_FIELD_MISSING;
        }

        Table *table = iter->second;
        if (0 == strcmp(field_name, "*")) {
          if(aggr_op!=AggrOp::NO_AGGR_OP && aggr_op!= AggrOp::AGG_COUNT){
          LOG_WARN("Aggregation Operation Not Allowd for *");
          return RC::SCHEMA_FIELD_TYPE_MISMATCH;
          }
          wildcard_fields(table, query_fields,aggr_op);
        } else {
          const FieldMeta *field_meta = table->table_meta().field(field_name);
          if (nullptr == field_meta) {
            LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
            return RC::SCHEMA_FIELD_MISSING;
          }

          query_fields.push_back(Field(table, field_meta,aggr_op));
        }
      }
    } else {
      if (tables.size() != 1) {
        LOG_WARN("invalid. I do not know the attr's table. attr=%s", relation_attr.attribute_name.c_str());
        return RC::SCHEMA_FIELD_MISSING;
      }

      Table *table = tables[0];
      const FieldMeta *field_meta = table->table_meta().field(relation_attr.attribute_name.c_str());
      if (nullptr == field_meta) {
        LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), relation_attr.attribute_name.c_str());
        return RC::SCHEMA_FIELD_MISSING;
      }
      // 算术聚合操作仅适用于int和float
      if((aggr_op==AggrOp::AGG_AVG || aggr_op==AggrOp::AGG_MAX || 
          aggr_op==AggrOp::AGG_SUM || aggr_op==AggrOp::AGG_MIN)
          && (field_meta->type() != AttrType::INTS && field_meta->type() != AttrType::FLOATS)){
            LOG_WARN("Aggregation Operation Not Allowed from the data type");
            return RC::SCHEMA_FIELD_TYPE_MISMATCH;
          }
      query_fields.push_back(Field(table, field_meta, aggr_op));
    }
  }

  LOG_INFO("got %d tables in from stmt and %d fields in query stmt", tables.size(), query_fields.size());

  Table *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
  }

  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  RC rc = FilterStmt::create(db,
      default_table,
      &table_map,
      select_sql.conditions.data(),
      static_cast<int>(select_sql.conditions.size()),
      filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }
  // everything alright
  SelectStmt *select_stmt = new SelectStmt();
  // TODO add expression copy
  select_stmt->tables_.swap(tables);
  select_stmt->query_fields_.swap(query_fields);
  select_stmt->filter_stmt_ = filter_stmt;
  stmt = select_stmt;
  return RC::SUCCESS;
}

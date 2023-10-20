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
// Created by Wangyunlai on 2022/5/22.
//

#include "sql/stmt/update_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/db/db.h"
#include "storage/table/table.h"


UpdateStmt::UpdateStmt(Table *table, 
                      Value *values, 
                      int value_amount, 
                      const std::string& update_attribute,
                      FilterStmt* filter_stmt)
    :table_(table), values_(values), value_amount_(value_amount), update_attribute_(update_attribute),filter_stmt_(filter_stmt)
{}

RC UpdateStmt::create(Db *db, const UpdateSqlNode &update, Stmt *&stmt)
{
  // #TODO
  //get table
  const char *table_name = update.relation_name.c_str();
  if (nullptr == db || nullptr == table_name ) {
    LOG_WARN("invalid argument. db=%p, table_name=%p",
        db, table_name);
    return RC::INVALID_ARGUMENT;
  }

  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  //get update_attribute and check validate
  std::string update_attribute = update.attribute_name;
  AttrType value_type = update.value.attr_type();
  const TableMeta &table_meta = table->table_meta();
  const int sys_field_num = table_meta.sys_field_num();
  const int field_num = table_meta.field_num() - sys_field_num;
  int update_location = 0;
  for(update_location; update_location<field_num;update_location++){
    const FieldMeta *field_meta = table_meta.field(update_location + sys_field_num);
    AttrType field_type = field_meta->type();
    const char * field_name = field_meta->name();
    //field_name 和 type 都要一致 才算合法的update。
    if(strcmp(field_name,update_attribute.c_str())==0 && field_type==value_type){
        break;
      }
  }
  if(update_location==field_num){
    LOG_WARN("field name or type mismatch");
    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  }


  //get values
  Value* value = const_cast<Value*>(&update.value);
  
  //get filter_stmt
  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(std::string(table_name), table));
  FilterStmt *filter_stmt = nullptr;
  RC rc = FilterStmt::create(
      db, table, &table_map, update.conditions.data(), static_cast<int>(update.conditions.size()), filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }
  stmt = new UpdateStmt(table,value,1,update_attribute,filter_stmt);
  return RC::SUCCESS;
}

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

#include <algorithm>

#include "sql/stmt/update_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

UpdateStmt::UpdateStmt(Table *table, 
                      const std::vector<Expression *> &update_exprs, 
                      const std::vector<SelectStmt *> &update_sub_querys,
                      int value_amount, 
                      const std::vector<const FieldMeta*> &update_fields,
                      FilterStmt* filter_stmt)
    :table_(table), update_exprs_(update_exprs), update_sub_querys_(update_sub_querys),
     value_amount_(value_amount), update_fields_(update_fields),filter_stmt_(filter_stmt)
{}
UpdateStmt::~UpdateStmt(){
  for(int i = 0; i < update_exprs_.size(); i++){
    delete update_exprs_.at(i);
  }
  for(int i = 0; i < update_sub_querys_.size(); i++){
    delete update_sub_querys_.at(i);
  }
}
RC UpdateStmt::create(Db *db, const UpdateSqlNode &update, Stmt *&stmt)
{
  // #TODO
  // struct UpdateSqlNode
  // std::string                   relation_name;         ///< Relation to update
  // std::vector<std::string>      attribute_name;        ///< 更新的字段, 已支持 多字段更新
  // std::vector<ConditionSqlNode> update_conditions;     ///< 更新的值,为了支持子查询更新,使用条件语句存储
  // std::vector<Value>            value;                 ///< 更新的值，已支持多字段更新
  // std::vector<ConditionSqlNode> conditions;
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
  
  //get all attribute_name from update_conditions and check validate.
  //construct all rigth value expr value with valueexpr and subquery with subqueryexpr
  std::vector<std::string> update_attribute;
  std::vector<Expression *> update_exprs;
  std::vector<SelectStmt *> update_sub_query_stmts;
  for (int i = 0; i < static_cast<int>(update.update_conditions.size()); i++){
    // get update_attribute name ;
    const std::string& update_attribute_name = update.update_conditions.at(i).left_attr.attribute_name;
    update_attribute.push_back(update_attribute_name);
    
    // get update_exprs
    bool is_sub_query = update.update_conditions.at(i).right_is_sub_query;
    if(is_sub_query){
      Expression * update_expr = new SubQueryExpr(std::vector<Value>());
      update_exprs.push_back(update_expr);
      Stmt* update_sub_query_stmt;
      RC rc = SelectStmt::create(db,*update.update_conditions.at(i).right_sub_query,update_sub_query_stmt);
      update_sub_query_stmts.push_back(static_cast<SelectStmt*>(update_sub_query_stmt));
    }
    else{
      const Value &update_value = update.update_conditions.at(i).right_value;
      Expression * update_expr = new ValueExpr(update_value);
      update_exprs.push_back(update_expr);
    }
  }
  
  std::vector<const FieldMeta*> update_fields;
  std::vector<const Value*> update_values;
  for(int i = 0; i < update_attribute.size(); i++){
    
    // 检查更新的field是否合法.
    const FieldMeta *meta = table->table_meta().field(update_attribute.at(i).c_str());
    if(nullptr == meta){
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }

    // 检查更新的值是否合法,跳过子查询的检查
    if(update_exprs.at(i)->type() == ExprType::VALUE){
      const Value& value = static_cast<ValueExpr*>(update_exprs.at(i))->get_value();
      bool field_nullable = meta->nullable();
      if(field_nullable && value.is_null()) {
        //TODO num_value_ changes with int
        int attr_len = std::min(meta->len(), (int)sizeof(int));;
        const_cast<Value&>(value).set_type(meta->type());
        const_cast<Value&>(value).set_length(attr_len);
      }


      if(meta->type() != value.attr_type()){
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
    }
    update_fields.push_back(meta);
  }

  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(std::string(table_name), table));
  FilterStmt *filter_stmt = nullptr;
  RC rc = FilterStmt::create(
      db, table, &table_map, update.conditions.data(), static_cast<int>(update.conditions.size()), filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }
  
  // 将要更新的表,阈,和更新表达式传入构造UpdateStmt
  stmt = new UpdateStmt(table,update_exprs,update_sub_query_stmts,update_exprs.size(),update_fields,filter_stmt);
  return RC::SUCCESS;
}

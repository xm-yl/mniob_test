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

#include "common/rc.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"


FilterStmt::~FilterStmt()
{
  for (FilterUnit *unit : filter_units_) {
    delete unit;
  }
  filter_units_.clear();
  for (SelectStmt* sub_query: this->sub_querys_){
    if(sub_query !=nullptr) delete sub_query;
  }
}

RC FilterStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const ConditionSqlNode *conditions, int condition_num, FilterStmt *&stmt)
{
  RC rc = RC::SUCCESS;
  stmt = nullptr;

  FilterStmt *tmp_stmt = new FilterStmt();
  for (int i = 0; i < condition_num; i++) {
    FilterUnit *filter_unit = nullptr;
    rc = create_filter_unit(db, default_table, tables, conditions[i], filter_unit);
    if (rc != RC::SUCCESS) {
      delete tmp_stmt;
      LOG_WARN("failed to create filter unit. condition index=%d", i);
      return rc;
    }
    tmp_stmt->filter_units_.push_back(filter_unit);
  }
  
  //create the subquerystmt(selectstmt) according to filter_units_
  for(int i = 0; i < condition_num; i++) {
    if(!conditions[i].right_is_sub_query){
      tmp_stmt->sub_querys_.push_back(nullptr);
    }
    else {
      const CompOp this_op = conditions[i].comp;
      const SelectSqlNode& a = *conditions[i].right_sub_query;
      const AggrOp this_aggr_op = a.attributes.front().aggr_op;
      const int field_num = default_table->table_meta().field_num();
      const std::string domain = a.attributes.front().attribute_name;
      
      //子查询的语法检查
      // 1. 没有聚合函数时候使用等于类的比较        (比较不支持多行)
      // 2. 没有聚合函数时候使用*查询且表列数大于1   (不支持多列)
      // 3. 查询列数大于1                          (不支持多列)
      if(this_op>=EQUAL_TO && this_op <=GREAT_THAN && this_aggr_op==NO_AGGR_OP){
        LOG_WARN("Didnt support multi row for comparsion =,<,>,<> and so on");
        return RC::INTERNAL;        
      }
      if(this_aggr_op==NO_AGGR_OP && (domain == std::string("*") && field_num != 1)){
        LOG_WARN("Didnt support * for subquery without aggregation");
        return RC::INTERNAL;
      }
      if(a.attributes.size() > 1){
        LOG_WARN("Didnt support multiple domain for subquery");
        return RC::INTERNAL;
      }
      
      Stmt *sub_query_stmt = nullptr;
      rc = SelectStmt::create(db, *conditions[i].right_sub_query, sub_query_stmt);
      if (rc != RC::SUCCESS){
        LOG_ERROR("Create %d th sub_query stmt failed, %s", i, strrc(rc));
        return rc;
      }
      tmp_stmt->sub_querys_.push_back(dynamic_cast<SelectStmt *>(sub_query_stmt));
    }
  }

  stmt = tmp_stmt;
  return rc;
}

RC get_table_and_field(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const RelAttrSqlNode &attr, Table *&table, const FieldMeta *&field)
{
  if (common::is_blank(attr.relation_name.c_str())) {
    table = default_table;
  } else if (nullptr != tables) {
    auto iter = tables->find(attr.relation_name);
    if (iter != tables->end()) {
      table = iter->second;
    }
  } else {
    table = db->find_table(attr.relation_name.c_str());
  }
  if (nullptr == table) {
    LOG_WARN("No such table: attr.relation_name: %s", attr.relation_name.c_str());
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  field = table->table_meta().field(attr.attribute_name.c_str());
  if (nullptr == field) {
    LOG_WARN("no such field in table: table %s, field %s", table->name(), attr.attribute_name.c_str());
    table = nullptr;
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  return RC::SUCCESS;
}

RC FilterStmt::create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const ConditionSqlNode &condition, FilterUnit *&filter_unit)
{
  RC rc = RC::SUCCESS;

  CompOp comp = condition.comp;
  if (comp < EQUAL_TO || comp >= NO_OP) {
    LOG_WARN("invalid compare operator : %d", comp);
    return RC::INVALID_ARGUMENT;
  }

  filter_unit = new FilterUnit;

  if (condition.left_is_attr) {
    Table *table = nullptr;
    const FieldMeta *field = nullptr;
    rc = get_table_and_field(db, default_table, tables, condition.left_attr, table, field);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr");
      return rc;
    }
    FilterObj filter_obj;
    filter_obj.init_attr(Field(table, field));
    filter_unit->set_left(filter_obj);
  } else {
    FilterObj filter_obj;
    filter_obj.init_value(condition.left_value);
    filter_unit->set_left(filter_obj);
  }
  if (!condition.right_is_sub_query){
    if (condition.right_is_attr) {
      Table *table = nullptr;
      const FieldMeta *field = nullptr;
      rc = get_table_and_field(db, default_table, tables, condition.right_attr, table, field);
      if (rc != RC::SUCCESS) {
        LOG_WARN("cannot find attr");
        return rc;
      }
      FilterObj filter_obj;
      filter_obj.init_attr(Field(table, field));
      filter_unit->set_right(filter_obj);
    } else {
      FilterObj filter_obj;
      filter_obj.init_value(condition.right_value);
      filter_unit->set_right(filter_obj);
    }
  }
  else{
    FilterObj filter_obj;
    filter_obj.init_values();
    filter_unit->set_right(filter_obj);
  }

  filter_unit->set_comp(comp);

  // 检查两个类型是否能够比较
  return rc;
}

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
// Created by Wangyunlai on 2022/07/05.
//

#pragma once
#include <string>
#include "storage/table/table.h"
#include "storage/field/field_meta.h"
#include "sql/parser/parse_defs.h"

/**
 * @brief 字段
 * 
 */
class Field 
{
public:
  Field() = default;
  Field(const Table *table, const FieldMeta *field , AggrOp aggr_op=AggrOp::NO_AGGR_OP,bool is_star=false,int star_num=-1) 
  : table_(table), field_(field),aggr_op_(aggr_op),is_star_(is_star),star_num_(star_num)
  {
    name_with_oper = std::string(field->name());
    if(aggr_op != AggrOp::NO_AGGR_OP){
      std::string field_name(field->name());
      const std::string lbrace = "(";
      const std::string star = "*";
      const std::string rbrace = ")";
      switch (aggr_op) {
        case AggrOp::AGG_AVG: {
          std::string aggr_func = "AVG";
          name_with_oper = aggr_func + lbrace + field_name + rbrace;
        } break;
        case AggrOp::AGG_MAX: {
          std::string aggr_func = "MAX";
          name_with_oper = aggr_func + lbrace + field_name + rbrace;
        } break;
        case AggrOp::AGG_MIN: {
          std::string aggr_func = "MIN";
          name_with_oper = aggr_func + lbrace + field_name + rbrace;
        } break;
        case AggrOp::AGG_SUM: {
          const std::string aggr_func = "SUM";
          name_with_oper = aggr_func + lbrace + field_name + rbrace;
        } break;
        case AggrOp::AGG_COUNT: {
          if(is_star){
            field_name = "*";
          }
          std::string aggr_func = "COUNT";
          name_with_oper = aggr_func + lbrace + field_name + rbrace;
        } break;
      }
    }
  }
  Field(const Field &) = default;

  const Table *table() const
  {
    return table_;
  }
  const FieldMeta *meta() const
  {
    return field_;
  }
  const AggrOp aggr_op() const
  {
    return aggr_op_;
  }
  const bool is_star() const
  {
    return is_star_;
  }
  const int star_num() const
  {
    return star_num_;
  }
  const char* get_name_with_oper() const
  {
    return name_with_oper.c_str();
  }

  AttrType attr_type() const
  {
    return field_->type();
  }

  const char *table_name() const
  {
    return table_->name();
  }
  const char *field_name() const
  {
    return field_->name();
  }
  void set_table(const Table *table)
  {
    this->table_ = table;
  }
  void set_field(const FieldMeta *field)
  {
    this->field_ = field;
  }
  void set_aggr_op(const AggrOp aggr_op)
  {
    this->aggr_op_ = aggr_op; 
  }
  void set_int(Record &record, int value);
  int  get_int(const Record &record);

  const char *get_data(const Record &record);
  
  static void add_next_star_num(){
    next_star_num++;
  }
  static int get_next_star_num(){
    return next_star_num;
  }
private:
  static int next_star_num;
private:
  const Table *table_ = nullptr;
  const FieldMeta *field_ = nullptr;
  AggrOp aggr_op_ = AggrOp::NO_AGGR_OP;
  bool is_star_ = false; // 是否是代表star聚合的Field
  int star_num_ = 0;
  std::string name_with_oper = "";
};

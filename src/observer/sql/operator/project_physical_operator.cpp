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
// Created by WangYunlai on 2022/07/01.
//

#include "common/log/log.h"
#include "sql/operator/project_physical_operator.h"
#include "storage/record/record.h"
#include "storage/table/table.h"

void ProjectPhysicalOperator::debug_print_cnt_info_with_depth(int dep) {
  LOG_DEBUG("[ProjectPhysicalOperator] depth:%d counts:%d", dep, this->debug_cnt);
  for(int i = 0; i < this->children_.size(); i++) {
    this->children_[i]->debug_print_cnt_info_with_depth(dep+1);
  }
}

RC ProjectPhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  PhysicalOperator *child = children_[0].get();
  RC rc = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  return RC::SUCCESS;
}

RC ProjectPhysicalOperator::next(Tuple* outer_tuple)
{ 
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    return RC::RECORD_EOF;
  }
  this->debug_cnt++;
  if (is_aggregate && !finish_aggregate){
    while(RC::SUCCESS == (rc = children_[0]->next(outer_tuple))){
      tuple_.set_tuple(children_[0]->current_tuple());
      aggregate(&tuple_);
    }
    if(rc != RC::SUCCESS && rc != RC::RECORD_EOF){
      return rc;
    }
    process_aggr_record();
    finish_aggregate = true;

    //#TODO 这里的边界条件还是有点问题, 如果聚合函数没有接受到数据,这里应应该返回EOF
    if (aggr_result__.empty()){
      pad_aggr_result();
    }
    if(rc == RC::RECORD_EOF){
      rc = RC::SUCCESS;
    }
  }
  else if(!is_aggregate){
    rc = children_[0]->next(outer_tuple);
    if(rc!=RC::SUCCESS) return rc;
  }
  else if(is_aggregate && finish_aggregate){
    return RC::RECORD_EOF;
  }
  return rc;
}

RC ProjectPhysicalOperator::close()
{
  if (!children_.empty()) {
    children_[0]->close();
  }
  // clear the aggregation token.
  if (finish_aggregate){
    finish_aggregate = false;
    aggr_result__.clear();
    count = 0;
    null_count = 0;
  }
  return RC::SUCCESS;
}
Tuple *ProjectPhysicalOperator::current_tuple()
{ 
  if(is_aggregate){
    aggr_tuple_.set_values(aggr_result__);
    return &aggr_tuple_;
  }
  else{
    tuple_.set_tuple(children_[0]->current_tuple());
    return &tuple_;
  }
  return &tuple_;
}
void ProjectPhysicalOperator::pad_aggr_result(){
  for (int i = 0; i < aggr_ops_.size(); i++){
    switch(aggr_ops_.at(i)){
      case AggrOp::AGG_COUNT:{
        Value tmp;
        tmp.set_float(0);
        aggr_result__.push_back(tmp);
      } break;
      default:{
        Value tmp;
        tmp.set_null(true);
        tmp.set_type(AttrType::FLOATS);
        tmp.set_length(sizeof(float));
        aggr_result__.push_back(tmp);
      } break;
    }
  }
}
void ProjectPhysicalOperator::aggregate(ProjectTuple* current_tuple){
  //聚合计数+1
  this->count += 1;
  RC rc = RC::SUCCESS;
  Tuple* tuple = current_tuple;

  std::vector<Value>& record_ = aggr_result__;
  const std::vector<AggrOp> aggr_ops = aggr_ops_;
  if(record_.empty()){
    for(int i= 0; i< current_tuple->cell_num();i++){
      Value current_cell;
      current_tuple->cell_at(i,current_cell);
      record_.push_back(current_cell);
      if(current_cell.is_null()) {
        this->null_count++;
        continue;
      }
    }
  }
  else{
    assert(tuple != nullptr);
    int cell_num = tuple->cell_num();
    for (int i = 0; i < cell_num; i++){
      Value value;
      rc = tuple->cell_at(i, value);

      if(value.is_null()) {
        this->null_count++;
        continue;
      }

      if(record_[i].is_null()) {
        if(value.attr_type() == INTS) {
          record_[i].set_int(value.get_int());
        } else {
          record_[i].set_float(value.get_float());
        }
        continue;
      }

      switch (aggr_ops[i]){
        case AggrOp::AGG_AVG:{
          if(value.attr_type() == AttrType::INTS){
            record_[i].set_int(record_[i].get_int() + value.get_int());
            // record[i] = record[i] + value.get_int();
          }
          else{
            record_[i].set_int(record_[i].get_float() + value.get_float());
            // record[i] = record[i] + value.get_float();
          }
        } break;
        case AggrOp::AGG_SUM:{

          if(value.attr_type() == AttrType::INTS){
            record_[i].set_int(record_[i].get_int() + value.get_int());
            // record[i] = record[i] + value.get_int();
          }
          else{
            record_[i].set_int(record_[i].get_float() + value.get_float());
            // record[i] = record[i] + value.get_float();
          }
        } break;
        case AggrOp::AGG_MAX:{
          AttrType tmp = value.attr_type();
          int result = record_[i].compare(value);
          if(result < 0) record_[i] = value;
        }break;
        case AggrOp::AGG_MIN:{
          int result = record_[i].compare(value);
          if(result > 0) record_[i] = value;
        } break;
      }
    }
  }
}
void ProjectPhysicalOperator::process_aggr_record(){
  const std::vector<AggrOp> aggr_ops = aggr_ops_;;
  for (int i = 0; i < aggr_result__.size(); i++){
    int count_with_null = is_star_[i] ? count : count - null_count;
    switch (aggr_ops[i]){
      case AggrOp::AGG_COUNT:{
        aggr_result__[i].set_type(AttrType::FLOATS);
        aggr_result__[i].set_float(count_with_null);
      } break;
      case AggrOp::AGG_AVG :{
        AttrType tmp = aggr_result__[i].attr_type();
        if(count_with_null == 0) {
          aggr_result__[i].set_type(AttrType::FLOATS);
          aggr_result__[i].set_null(true);
          continue;
        }
        if(tmp == AttrType::INTS){
          double sum = aggr_result__[i].get_int();
          aggr_result__[i].set_type(AttrType::FLOATS);
          aggr_result__[i].set_float((float)(sum/count_with_null));
        }
        else{
          aggr_result__[i].set_float(aggr_result__[i].get_float()/count_with_null);
        }
      } break;
    }
  }
}

void ProjectPhysicalOperator::add_projection(const Table *table, const FieldMeta *field_meta)
{
  // 对单表来说，展示的(alias) 字段总是字段名称，
  // 对多表查询来说，展示的alias 需要带表名字
  TupleCellSpec *spec = new TupleCellSpec(table->name(), field_meta->name(), field_meta->name());
  tuple_.add_cell_spec(spec);
}

//存储需要聚合的字段
void ProjectPhysicalOperator::add_aggregation(AggrOp aggr_op, bool is_star){
  //TupleCellSpec *spec = new TupleCellSpec(table->name(), field_meta->name(), field_meta->name());
  aggr_ops_.push_back(aggr_op);
  is_star_.push_back(is_star);
  // aggr_tuple_.add_cell_spec(spec);
  // aggr_tuple_.add_aggr_op(aggr_op);
}

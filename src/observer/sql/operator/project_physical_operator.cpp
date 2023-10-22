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

RC ProjectPhysicalOperator::next()
{
  if (children_.empty()) {
    return RC::RECORD_EOF;
  }
  RC rc = children_[0]->next();
  if(rc!=RC::SUCCESS && is_aggregate) process_aggr_record();
  return rc;
}

RC ProjectPhysicalOperator::close()
{
  if (!children_.empty()) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}
Tuple *ProjectPhysicalOperator::current_tuple()
{
  tuple_.set_tuple(children_[0]->current_tuple());
  if(is_aggregate)aggregate(&tuple_);
  return &tuple_;
}
void ProjectPhysicalOperator::aggregate(ProjectTuple* current_tuple){
  //聚合计数+1
  this->count += 1;
  RC rc = RC::SUCCESS;
  Tuple* tuple = current_tuple;
  std::vector<float>& record = aggr_result_;
  const std::vector<AggrOp> aggr_ops = aggr_ops_;
  if(aggr_result_.empty()){
    //Tuple* set_tuple = new Tuple(current_tuple);
    //aggr_tuple_.set_tuple(current_tuple);
    for(int i = 0; i < current_tuple->cell_num(); i++){
      aggr_result_.push_back(0);
    }
    aggr_result_.push_back(1);//作为是否初始化最大最小的标记
    //is_init = true;
  }
  assert(tuple != nullptr);
  int cell_num = tuple->cell_num();
  for (int i = 0; i < cell_num; i++){
    Value value;
    rc = tuple->cell_at(i, value);
    // if (rc != RC::SUCCESS) {
    //   return rc;
    // }
    switch (aggr_ops[i]){
      case AggrOp::AGG_AVG:{
        if(value.attr_type() == AttrType::INTS){
          record[i] = record[i] + value.get_int();
        }
        else record[i] = record[i] + value.get_float();
      } break;
      case AggrOp::AGG_MAX:{
        if(record[cell_num]){
          record[cell_num] = 0;
          if(value.attr_type() == AttrType::INTS){
            record[i] = value.get_int();
          }
          else record[i] = value.get_float();
        }
        else{
          if(value.attr_type() == AttrType::INTS){
            int current = value.get_int();
            if(current > record[i]) record[i] = current;
          }
          else{
            float current = value.get_float();
            if(current > record[i]) record[i] = current;
          }
        }
      }break;
      case AggrOp::AGG_MIN:{
        if(record[cell_num]){
          record[cell_num] = 0;
          if(value.attr_type() == AttrType::INTS){
            record[i] = value.get_int();
          }
          else record[i] = value.get_float();
        }
        else{
          if(value.attr_type() == AttrType::INTS){
            int current = value.get_int();
            if(current < record[i]) record[i] = current;
          }
          else{
            float current = value.get_float();
            if(current < record[i]) record[i] = current;
          }
        }
      } break;
      case AggrOp::AGG_SUM:{
        if(value.attr_type() == AttrType::INTS){
          record[i] = record[i] + value.get_int();
        }
        else record[i] = record[i] + value.get_float();
      } break;
    }
  }
  // min_init_token = true;
  // max_init_token = true;
}
void ProjectPhysicalOperator::process_aggr_record(){
  const std::vector<AggrOp> aggr_ops = aggr_ops_;;
  for (int i = 0; i < aggr_result_.size(); i++){
      switch (aggr_ops[i]){
        case AggrOp::AGG_COUNT:{
          aggr_result_[i] = count;
        } break;
        case AggrOp::AGG_AVG :{
          aggr_result_[i] = aggr_result_[i] / count;
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
void ProjectPhysicalOperator::add_aggregation(AggrOp aggr_op){
  //TupleCellSpec *spec = new TupleCellSpec(table->name(), field_meta->name(), field_meta->name());
  aggr_ops_.push_back(aggr_op);
  // aggr_tuple_.add_cell_spec(spec);
  // aggr_tuple_.add_aggr_op(aggr_op);
}

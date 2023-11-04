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

#pragma once

#include "sql/operator/physical_operator.h"

/**
 * @brief 选择/投影物理算子
 * @ingroup PhysicalOperator
 */
class ProjectPhysicalOperator : public PhysicalOperator
{
public:
  ProjectPhysicalOperator()
  {}

  virtual ~ProjectPhysicalOperator() = default;

  void add_expressions(std::vector<std::unique_ptr<Expression>> &&expressions)
  {
    
  }
  void add_projection(const Table *table, const FieldMeta *field);
  void add_aggregation(const AggrOp aggr_op, bool is_star);
  PhysicalOperatorType type() const override
  {
    return PhysicalOperatorType::PROJECT;
  }

  RC open(Trx *trx) override;
  RC next(Tuple* outer_tuple = nullptr) override;
  RC close() override;
  void aggregate(ProjectTuple* current_tuple);
  
  //遍历结束后处理聚合记录，算平均和COUNT等
  void process_aggr_record();
  
  //当子树没有返回结果时,用0和null填充返回结果
  void pad_aggr_result();

  void set_aggregate(){
    is_aggregate = true;
  }
  void debug_print_cnt_info_with_depth(int dep) override;

  int cell_num() const
  {
    return tuple_.cell_num();
  }
  std::vector<Value> get_aggrgation_result() const{
    return aggr_result__;
  }
  Tuple *current_tuple() override;

  std::vector<bool> is_star()const {
    return is_star_;
  }

private:
  ProjectTuple tuple_;
  std::vector<AggrOp> aggr_ops_;
  std::vector<bool> is_star_;
  //std::vector<float> aggr_result_;
  //这里看看能不能写成AggregationTuple
  std::vector<Value> aggr_result__;
  AggregateTuple aggr_tuple_;
  bool is_aggregate = false;
  bool finish_aggregate = false;
  int count = 0; 
  int null_count = 0;
};

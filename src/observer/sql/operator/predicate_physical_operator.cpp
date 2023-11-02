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
// Created by WangYunlai on 2022/6/27.
//

#include "common/log/log.h"
#include "sql/operator/predicate_physical_operator.h"
#include "storage/record/record.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/field/field.h"

PredicatePhysicalOperator::PredicatePhysicalOperator(std::unique_ptr<Expression> expr) : expression_(std::move(expr))
{
  ASSERT(expression_->value_type() == BOOLEANS, "predicate's expression should be BOOLEAN type");
}

void PredicatePhysicalOperator::debug_print_cnt_info_with_depth(int dep) {
  LOG_DEBUG("[PredicatePysicalOperator] depth:%d counts:%d", dep, this->debug_cnt);
  for(int i = 0; i < this->children_.size(); i++) {
    this->children_[i]->debug_print_cnt_info_with_depth(dep+1);
  }
}


RC PredicatePhysicalOperator::open(Trx *trx)
{
  if (children_.size() != 1) {
    LOG_WARN("predicate operator must has one child");
    return RC::INTERNAL;
  }
  RC rc = RC::SUCCESS;
  rc = children_.front()->open(trx);
  if(rc != RC::SUCCESS){
    LOG_WARN("Open children oper failed");
    return rc;
  }
  
  // init subquery trx
  rc = open_sub_query(trx);
  if(rc == RC::RECORD_EOF) rc = RC::SUCCESS;
  if(rc != RC::SUCCESS){
    LOG_WARN("Init subquery trx failed");
  }
  return rc;
}
RC PredicatePhysicalOperator::open_sub_query(Trx* trx){
  // Predicate 中的expr的结构如下
  // conjunctionepxr -> std::vector<ComparisonExpr>
  //                                |
  //                                ComparisonExpr  -> (leftexpr ,  rightexpr)
  //                                                                SUBQUERY
  // 子查询的出现就是当 rightexpr 的type为SUBQUERY的时候。
  // children_exprs_num 表示了 Comparision 表达式的数量, 在这个设置中，我们认为只有等式的右边会出现子查询
  RC rc = RC::SUCCESS;
  sub_query_init = true;
  int children_exprs_num = 0;
  int sub_query_count    = 0; 
  ConjunctionExpr* conj_expr = dynamic_cast<ConjunctionExpr *>(expression_.get());
  if(conj_expr != nullptr){
    children_exprs_num = conj_expr->children().size();
    LOG_DEBUG("Receive %d children which could have sub query",children_exprs_num);
  }
  for(int i = 0; i < children_exprs_num; i++){

    ComparisonExpr* children_expr = static_cast<ComparisonExpr*> (conj_expr->children().at(i).get());
    Expression*     right_expr    = children_expr->right().get();
    CompOp          this_compop   = children_expr->comp();
    Expression*     left_expr     = children_expr->left().get();
    if(right_expr->type() == ExprType::SUBQUERY){
      rc = dynamic_cast<SubQueryExpr*>(right_expr)->open(trx);
    }
  }
  return rc;
} 

RC PredicatePhysicalOperator::next(Tuple* outer_tuple)
{
  RC rc = RC::SUCCESS;
  this->debug_cnt++;
  PhysicalOperator *oper = children_.back().get();
  
  while (RC::SUCCESS == (rc = oper->next(outer_tuple))) {
    Tuple *tuple = oper->current_tuple();
    if (nullptr == tuple) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get tuple from operator");
      break;
    }
    JoinedTuple join_tuple;
    join_tuple.set_left(tuple);
    join_tuple.set_right(outer_tuple);

    // outer tuple passed in for subquery.
    Value value;
    if(outer_tuple == nullptr){
      rc = expression_->get_value(*tuple, value); 
    }
    else {
      rc = expression_->get_value(join_tuple, value);
    }
    if (rc != RC::SUCCESS) {
      return rc;
    }

    if (value.get_boolean()) {
      return rc;
    }
  }
  return rc;
}

RC PredicatePhysicalOperator::close()
{
  RC rc = RC::SUCCESS;
  for(int i = 0; i < children_.size(); i++){
    if(children_[i] == nullptr) continue;  
    rc = children_[i]->close();
  }
  return rc;
}

Tuple *PredicatePhysicalOperator::current_tuple()
{
  return children_.back()->current_tuple();
}

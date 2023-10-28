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
  if (children_.size() == 0) {
    LOG_WARN("predicate operator must has at least one child");
    return RC::INTERNAL;
  }
  RC rc = RC::SUCCESS;
  for(int i = 0; i < children_.size(); i++){
    if(children_[i]) continue;  
    rc = children_[i]->open(trx);
  }
  return rc;
}
RC PredicatePhysicalOperator::init_sub_query_expr(){
  // Predicate 中的expr的结构如下
  // conjunctionepxr -> std::vector<ComparisonExpr>
  //                                |
  //                                ComparisonExpr  -> (leftexpr ,  rightexpr)

  // 我们认为子查询的出现就是当 rightexpr 的type为SUBQUERY的时候。
  RC rc = RC::SUCCESS;
  ConjunctionExpr* conj_expr = dynamic_cast<ConjunctionExpr *>(expression_.get());
  auto children_exprs = conj_expr->children();
  int children_exprs_num = children_exprs.size();

  LOG_DEBUG("Receive %d children which could have sub query",children_exprs_num - 1);
  
  //check if contains subquery, the last is the main query so dont travese it.
  for(int i = 0; i < children_exprs_num - 1; i++){
    LOG_DEBUG(" %d th children has sub query", i);
    ComparisonExpr* children_expr = static_cast<ComparisonExpr*> (children_exprs.at(i).get());
    Expression*     right_expr    = children_expr->right().get();
    
    // Begin subquery if expr contains sub query
    if(right_expr->type() == ExprType::SUBQUERY){  
      PhysicalOperator* oper = children_.at(i).get();
      
      //get value by next()
      while(RC::SUCCESS == (rc = oper->next())){
        Tuple * tuple = oper->current_tuple();
        if(nullptr == tuple){
          rc = RC::INTERNAL;
          LOG_WARN("failed to get tuple from operator");
          return rc;
        }
        Value value;
        if(1 != tuple->cell_num()){
          rc = RC::INTERNAL;
          LOG_WARN("Multiple field in sub query is not allowed");
        }
        rc = tuple->cell_at(0,value);
        if (rc != RC::SUCCESS) {
          return rc;
        }
        dynamic_cast<SubQueryExpr*>(right_expr)->push_back(value);
      }
    }
  }
  return rc;
}

RC PredicatePhysicalOperator::next()
{
  if(!sub_query_init){
    init_sub_query_expr();
    sub_query_init = true;
  }

  this->debug_cnt++;
  RC rc = RC::SUCCESS;
  PhysicalOperator *oper = children_.back().get();
  
  while (RC::SUCCESS == (rc = oper->next())) {
    Tuple *tuple = oper->current_tuple();
    if (nullptr == tuple) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get tuple from operator");
      break;
    }

    Value value;
    rc = expression_->get_value(*tuple, value);
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

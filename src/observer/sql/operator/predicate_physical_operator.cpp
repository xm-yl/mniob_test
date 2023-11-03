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
    if(children_[i] == nullptr) continue;
    rc = children_[i]->open(trx);

    if(rc != RC::SUCCESS) {
      if(rc == RC::RECORD_EOF) continue;
      return rc;
    }
    // if(i != (children_.size() -1) && children_[i]->current_tuple()->cell_num() > 1){
    //   LOG_WARN("Multiple cell in sub query is not allowed for now");
    //   return RC::INTERNAL;
    // }
  }
  rc = init_sub_query_expr();
  if(rc == RC::RECORD_EOF) rc = RC::SUCCESS;
  return rc;
}
RC PredicatePhysicalOperator::init_sub_query_expr(){
  // Predicate 中的expr的结构如下
  // conjunctionepxr -> std::vector<ComparisonExpr>
  //                                |
  //                                ComparisonExpr  -> (leftexpr ,  rightexpr)
  //                                                                SUBQUERY
  // 子查询的出现就是当 rightexpr 的type为SUBQUERY的时候。
  // children_exprs_num 表示了 Comparision 表达式的数量
  // sub_query_count    表示需要调用子查询的count数 这个数字最终应该等于 children_.size() - 1;
  RC rc = RC::SUCCESS;
  sub_query_init = true;
  int children_exprs_num = 0;
  int sub_query_count    = 0; 
  ConjunctionExpr* conj_expr = dynamic_cast<ConjunctionExpr *>(expression_.get());
  if(conj_expr != nullptr){
    children_exprs_num = conj_expr->children().size();
  }
  LOG_DEBUG("Receive %d children which could have sub query",children_exprs_num);
  
  //check if contains subquery, the last is the main query so dont travese it.
  for(int i = 0; i < children_exprs_num; i++){

    ComparisonExpr* children_expr = static_cast<ComparisonExpr*> (conj_expr->children().at(i).get());
    Expression*     right_expr    = children_expr->right().get();
    CompOp          this_compop   = children_expr->comp();
    Expression*     left_expr     = children_expr->left().get();
    // Begin subquery if expr contains sub query
    if(right_expr->type() == ExprType::SUBQUERY){
      if(!dynamic_cast<SubQueryExpr*>(right_expr)->values().empty()){
        continue;
      }
      LOG_DEBUG(" %d th children has sub query", i);
      PhysicalOperator* oper = children_.at(sub_query_count++).get();
      
      //get value by next()
      int tuple_num_from_sub_query = 0;
      int field_num_from_sub_query = 0;
      while(RC::SUCCESS == (rc = oper->next())){
        Tuple * tuple = oper->current_tuple();
        if(nullptr == tuple){
          rc = RC::INTERNAL;
          LOG_WARN("failed to get tuple from operator");
          return rc;
        }
        Value value;
        field_num_from_sub_query = tuple->cell_num();
        tuple_num_from_sub_query++;
        
        // 目前不允许子查询返回多列,在向subquery保存的时候,我们也只保留第一列的返回值
        rc = tuple->cell_at(0,value);
        if (rc != RC::SUCCESS) {
          return rc;
        }
        dynamic_cast<SubQueryExpr*>(right_expr)->push_back(value);
      }
      if(rc != RC::SUCCESS && rc != RC::RECORD_EOF) return rc; 
      // Check Validate for comparsion and return subquery result.
      if(this_compop == CompOp::IN_OP     || this_compop == CompOp::NOT_IN_OP   ||
         this_compop == CompOp::EXISTS_OP || this_compop == CompOp::NOT_EXISTS_OP){
        if(field_num_from_sub_query > 1) return RC::INTERNAL;
      }
      else{
        if(field_num_from_sub_query > 1) return RC::INTERNAL;
        if(tuple_num_from_sub_query > 1) return RC::INTERNAL;
      }
    }
  }
  return rc;
}

RC PredicatePhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  if(!sub_query_init){
    rc = init_sub_query_expr();
    sub_query_init = true;
    if(rc != RC::SUCCESS && rc != RC::RECORD_EOF){
      LOG_WARN("Sub Query init failed");
      return rc;
    }
  }

  this->debug_cnt++;
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

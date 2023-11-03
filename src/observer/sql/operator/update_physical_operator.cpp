#include "sql/operator/update_logical_operator.h"
#include "sql/operator/update_physical_operator.h"
#include "storage/record/record.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"
#include "sql/stmt/update_stmt.h"
#include "common/log/log.h"


//更新操作的主逻辑

RC UpdatePhysicalOperator::open(Trx* trx){
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    return rc;
  }
  for(int i = 0; i < children_.size(); i++){
    std::unique_ptr<PhysicalOperator> &child = children_[i];
    rc = child->open(trx);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to open child operator: %s", strrc(rc));
      return rc;
    }
  }
  trx_ = trx;
  rc = init_sub_query_expr();
  if(rc == RC::RECORD_EOF) rc = RC::SUCCESS;
  if(rc != RC::SUCCESS) return rc;
  return rc;
}
RC UpdatePhysicalOperator::init_update_values(){
  RC rc = RC::SUCCESS;
  for(int i = 0; i < update_exprs_.size(); i++){
    Value* update_value = new Value();
    RowTuple fake_tuple;


    if(update_exprs_.at(i)->type() == ExprType::VALUE);
    else if(update_exprs_.at(i)->type() == ExprType::SUBQUERY) {

      if(static_cast<SubQueryExpr*>(update_exprs_.at(i))->get_field_num() > 1) return RC::INTERNAL; 
      if(static_cast<SubQueryExpr*>(update_exprs_.at(i))->get_tuple_num() > 1) return RC::INTERNAL;
    }
    else {
      LOG_WARN("Unsupport Expr type");
      return RC::INTERNAL;
    }
    rc = update_exprs_.at(i)->get_value(fake_tuple,*update_value);
    if(rc != RC::SUCCESS) return rc;
    update_values_.push_back(update_value);
  }
  return rc;
}
RC UpdatePhysicalOperator::init_sub_query_expr() {
  RC rc = RC::SUCCESS;
  sub_query_init = true;
  int sub_query_num = children_.size() - 1;
  int subquery_expr_index = 0;
  for (int i = 0; i < sub_query_num; i++){
    
    //找到下一个子查询的Expr
    while(update_exprs_.at(subquery_expr_index)->type() != ExprType::SUBQUERY) subquery_expr_index++;
    Expression* sub_query_expr = update_exprs_.at(subquery_expr_index);
    PhysicalOperator* oper = children_.at(i).get();
    SubQueryExpr* this_expr = static_cast<SubQueryExpr*>(sub_query_expr);
    //调用子查询,将值放到Expr中
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
      this_expr->push_back(value);
    }
    // if(field_num_from_sub_query > 1) return RC::INTERNAL;
    // if(tuple_num_from_sub_query > 1) return RC::INTERNAL;
    // 如果子查询没查到东西,就返回一个null
    if(tuple_num_from_sub_query == 0){
      Value value;
      value.set_type(update_fields_.at(subquery_expr_index)->type());
      //TODO num_value_ int_value_
      value.set_length(std::min(update_fields_.at(subquery_expr_index)->len(), (int)sizeof(int)));
      value.set_null(true);
      
      this_expr->push_back(value);
    }
    // Set the statistic result of the sub query.
    this_expr->set_field_num(std::max(field_num_from_sub_query,1));
    this_expr->set_tuple_num(std::max(tuple_num_from_sub_query,1));
    subquery_expr_index++;
  }
  return rc;
}
RC UpdatePhysicalOperator::next()
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

  if (children_.empty()) {
    return RC::RECORD_EOF;
  }
  PhysicalOperator *child = children_.back().get();
  while (RC::SUCCESS == (rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }
    
    // init update values from sub query
    if(!update_values_init){
      rc = init_update_values();
      update_values_init = true;
      if(rc != RC::SUCCESS) {
        LOG_WARN("Init update values failed!");
        return rc;
      }
    }
    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    Record &record = row_tuple->record();
    rc = trx_->update_record(table_, record, update_values_, update_fields_);
    if (rc != RC::SUCCESS) {
      trx_->rollback();
      LOG_WARN("failed to update record: %s", strrc(rc));
      return rc;
    }
  }
  return RC::RECORD_EOF;
}

RC UpdatePhysicalOperator::close()
{
  //逐个关闭子操作
  if (!children_.empty()) {
    for(int i = 0; i < children_.size(); i++){
      children_.at(i)->close();
    }
  }
  return RC::SUCCESS;
}
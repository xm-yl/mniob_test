#pragma once

#include "sql/operator/logical_operator.h"

/**
 * @brief 逻辑算子，用于执行update语句
 * @ingroup LogicalOperator
 */
class UpdateLogicalOperator : public LogicalOperator 
{
public:
  UpdateLogicalOperator(Table *table,const std::vector<Expression *> &update_exprs, const std::vector<const FieldMeta*> &update_fields);
  virtual ~UpdateLogicalOperator() = default;

  LogicalOperatorType type() const override
  {
    return LogicalOperatorType::UPDATE;
  }
  Table *table() const
  {
    return table_;
  }

  std::vector<Expression*> update_exprs() const {
    return update_exprs_;
  }
  
  std::vector<const FieldMeta*> update_fields() const{
    return update_fields_;
  }
private:
  Table *table_ = nullptr;
  std::vector<Expression *> update_exprs_;
  std::vector<const FieldMeta*> update_fields_;
};

#pragma once

#include "sql/operator/physical_operator.h"

class Trx;
class UpdateStmt;
class Value;
/**
 * @brief 物理算子，更新
 * @ingroup PhysicalOperator
 */
class UpdatePhysicalOperator : public PhysicalOperator
{
public:
  UpdatePhysicalOperator(Table *table,const std::vector<Expression*> &update_exprs, const std::vector<const FieldMeta*> &update_fields) 
                    : table_(table),update_exprs_(update_exprs),update_fields_(update_fields)
  {}

  virtual ~UpdatePhysicalOperator() = default;

  PhysicalOperatorType type() const override
  {
    return PhysicalOperatorType::UPDATE;
  }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;
  
  RC init_sub_query_expr();
  RC init_update_values();
  Tuple *current_tuple() override
  {
    return nullptr;
  }
private:
  Table *table_ = nullptr;
  Trx *trx_ = nullptr;
  std::vector<Expression *>     update_exprs_;
  std::vector<const FieldMeta*> update_fields_; 
  std::vector<const Value*>     update_values_;
  bool sub_query_init = false;
  bool update_values_init = false;
};

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
  UpdatePhysicalOperator(Table *table,std::vector<const Value*> update_values,std::vector<const FieldMeta*> update_fields) 
                    : table_(table),update_values_(update_values),update_fields_(update_fields)
  {}

  virtual ~UpdatePhysicalOperator() = default;

  PhysicalOperatorType type() const override
  {
    return PhysicalOperatorType::UPDATE;
  }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override
  {
    return nullptr;
  }

private:
  Table *table_ = nullptr;
  Trx *trx_ = nullptr;
  std::vector<const Value*> update_values_;
  std::vector<const FieldMeta*> update_fields_; 
};

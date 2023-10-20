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
  UpdatePhysicalOperator(Table *table,Value *value,const std::string& update_attribute) 
                    : table_(table),value_(value),update_attribute_(update_attribute)
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
  Value *value_ = nullptr;
  std::string update_attribute_ = std::string();
};

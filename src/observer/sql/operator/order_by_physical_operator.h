
#pragma once

#include "sql/operator/physical_operator.h"

/**
 * @brief 排序算子
 * @ingroup PhysicalOperator
 */
class OrderByPhysicalOperator: public PhysicalOperator
{
public:
  OrderByPhysicalOperator(const std::vector<Field> &f, const std::vector<bool> &as)
  {
    this->fields_=f;
    this->is_asc_=as;
  }

  virtual ~OrderByPhysicalOperator() {
    for(size_t i = 0;i < tuples_.size(); i++) {
      delete this->tuples_[i];
    }
  };

  void add_expressions(std::vector<std::unique_ptr<Expression>> &&expressions)
  {
    
  }
  PhysicalOperatorType type() const override
  {
    return PhysicalOperatorType::ORDER_BY;
  }

  RC open(Trx *trx) override;
  RC next(Tuple* outer_tuple = nullptr) override;
  RC close() override;
  
  void debug_print_cnt_info_with_depth(int dep) override;

  int cell_num() const
  {
    return tuple_->cell_num();
  }
  Tuple *current_tuple() override;

  void get_order_field_specs();
  void set_order_fields(const std::vector<Field> &f) {
    this->fields_ = f;
  }
  
  void set_is_asc(const std::vector<bool> &as) {
    this->is_asc_ = as;
  }
private:
  Tuple* tuple_;
  std::vector<Field> fields_;
  std::vector<bool> is_asc_;
  std::vector<OrderByTuple*> tuples_;
  std::vector<TupleCellSpec> cell_specs_;
  int now_tuple_index = 0;
  int count = 0;
};

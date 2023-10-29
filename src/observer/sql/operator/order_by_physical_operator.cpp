#include <algorithm>
#include "sql/operator/order_by_physical_operator.h"

RC OrderByPhysicalOperator::open(Trx *trx) {
  if (this->children_.empty()) {
    return RC::SUCCESS;
  }

  PhysicalOperator *child = children_[0].get();
  RC rc = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  return RC::SUCCESS;
}

RC OrderByPhysicalOperator::next() {
  if(this->children_.size() != 1) {
    return RC::SUCCESS;
  }
  this->debug_cnt++;
  if (this->tuples_.size() != 0) {
    if(now_tuple_index >= static_cast<int>(this->tuples_.size())) {
        return RC::RECORD_EOF;
    }
    this->tuple_ = this->tuples_[this->now_tuple_index++];
    return RC::SUCCESS;
  }

  PhysicalOperator *child = children_[0].get();
  OrderByTuple* now_tuple;
  Tuple* ret_tuple;
  RC rc;
  //LOG_DEBUG("extract tuple info start");
  while((rc = child->next()) == RC::SUCCESS) {
    ret_tuple = child->current_tuple();
    now_tuple = new OrderByTuple();
    rc = now_tuple->exract_tuple_info(ret_tuple);
    if(OB_FAIL(rc)) {
      return rc;
    }
    this->tuples_.push_back(now_tuple);
  }

  //LOG_DEBUG("extract tuple info complete");
  
  if(0 == static_cast<int>(this->tuples_.size())) {
    return RC::RECORD_EOF;
  }

  this->get_order_field_specs();

  //LOG_DEBUG("size of order by tuples:%d", this->tuples_.size());

  std::vector<int> cell_at_index(cell_specs_.size());
  const std::vector<TupleCellSpec> table_spec = this->tuples_[0]->specs();

  for(size_t i = 0;i < cell_specs_.size(); i++) {
    for(size_t j = 0;j < table_spec.size(); j++) {
      if(0 == strcmp(table_spec[j].table_name(), cell_specs_[i].table_name()) && 0 == strcmp(table_spec[j].field_name(), cell_specs_[i].field_name())) {
        cell_at_index[i] = j;
      }
    }
  }

  std::sort(this->tuples_.begin(), this->tuples_.end(), 
  [&](OrderByTuple* lhs, OrderByTuple*rhs){
    for(int i = 0;i < static_cast<int> (cell_specs_.size()); i++) {
      Value l_value, r_value;
      lhs->cell_at(cell_at_index[i], l_value);
      rhs->cell_at(cell_at_index[i], r_value);

      if(l_value.is_null() && r_value.is_null()) {
        continue;
      } else if(l_value.is_null() && (!r_value.is_null())) {
        // l_value is null and we want null to be on the top of the order by when ASC vise versa.
        // so it returns true when ASC to make the l_value on the top of the order by
        // it returns false when DESC to make the l_value on the bottom of the order by
        return is_asc_[i] == true;
      } else if ((!l_value.is_null()) && r_value.is_null()) {
        //deduce type error
        return is_asc_[i] == false;
      }

      //l_value and r_value not null
      int cmp_result = l_value.compare(r_value);
      if(cmp_result == 0) continue;

      if(is_asc_[i]) {
        return cmp_result < 0;
      } else {
        return cmp_result > 0;
      }
    }
    return false;
  });
  //LOG_DEBUG("finish order by");

  this->tuple_ = this->tuples_[now_tuple_index++];
  return RC::SUCCESS;
}

void OrderByPhysicalOperator::get_order_field_specs() {
  this->cell_specs_.clear();
  for(int i = 0;i < static_cast<int>(this->fields_.size()); i++) {
    TupleCellSpec spec = TupleCellSpec(fields_[i].table_name(), fields_[i].field_name(), fields_[i].field_name());
    this->cell_specs_.push_back(spec);
  }
}

RC OrderByPhysicalOperator::close() {
  if (!children_.empty()) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}

void OrderByPhysicalOperator::debug_print_cnt_info_with_depth(int dep) {
  LOG_DEBUG("[OrderByPysicalOperator] depth:%d counts:%d", dep, this->debug_cnt);
  for(int i = 0; i < this->children_.size(); i++) {
    this->children_[i]->debug_print_cnt_info_with_depth(dep+1);
  }
}

Tuple* OrderByPhysicalOperator::current_tuple() {
    return this->tuple_;
}
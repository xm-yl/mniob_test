
#include "sql/operator/order_by_logical_operator.h"

OrderByLogicalOperator::OrderByLogicalOperator(const std::vector<Field> &fields, const std::vector<bool> &is_asc) {
    fields_ = fields;
    is_asc_ = is_asc;
}
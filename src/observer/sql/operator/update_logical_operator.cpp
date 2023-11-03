#include "sql/operator/update_logical_operator.h"


UpdateLogicalOperator::UpdateLogicalOperator(Table *table,const std::vector<Expression *> &update_exprs, const std::vector<const FieldMeta*> &update_fields)
    :table_(table),update_exprs_(update_exprs),update_fields_(update_fields){
}
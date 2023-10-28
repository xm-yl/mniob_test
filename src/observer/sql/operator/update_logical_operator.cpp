#include "sql/operator/update_logical_operator.h"


UpdateLogicalOperator::UpdateLogicalOperator(Table *table,std::vector<const Value*> update_values,std::vector<const FieldMeta*> update_fields)
    :table_(table),update_values_(update_values),update_fields_(update_fields){
}
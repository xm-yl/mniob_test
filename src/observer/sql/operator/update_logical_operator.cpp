#include "sql/operator/update_logical_operator.h"


UpdateLogicalOperator::UpdateLogicalOperator(Table *table,Value* value,const std::string & update_attribute)
    :table_(table),value_(value),update_attribute_(update_attribute){

}
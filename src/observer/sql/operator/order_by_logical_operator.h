
#pragma once

#include <vector>
#include <memory>

#include "sql/operator/logical_operator.h"
#include "storage/field/field.h"

// used to do order by query
// it is used to accumulate the tuples and order it using std::sort
class OrderByLogicalOperator: public LogicalOperator 
{
public:
  OrderByLogicalOperator(const std::vector<Field> &fields, const std::vector<bool> &is_asc);
  virtual ~OrderByLogicalOperator() = default;

  LogicalOperatorType type() const override
  {
    return LogicalOperatorType::ORDER_BY;
  }
  const std::vector<Field> &fields() const
  {
    return fields_;
  }

  const std::vector<bool> &is_asc() const
  {
    return is_asc_;
  }
private:
  //! 投影映射的字段名称
  //! 并不是所有的select都会查看表字段，也可能是常量数字、字符串，
  //! 或者是执行某个函数。所以这里应该是表达式Expression。
  //! 不过现在简单处理，就使用字段来描述
  std::vector<Field> fields_;
  std::vector<bool> is_asc_;
};

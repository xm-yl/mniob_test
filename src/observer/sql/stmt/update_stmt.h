/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/5/22.
//

#pragma once

#include "common/rc.h"
#include "sql/stmt/stmt.h"
#include "sql/stmt/filter_stmt.h"
class Table;

/**
 * @brief 更新语句
 * @ingroup Statement
 */
class UpdateStmt : public Stmt 
{
public:
  UpdateStmt() = default;
  UpdateStmt(Table *table, const std::vector<Expression*> &update_exprs, const std::vector<SelectStmt*>& update_sub_querys , 
              int value_amount, const std::vector<const FieldMeta*>& update_fields, FilterStmt* filter_stmt);
  virtual ~UpdateStmt() override;

public:
  static RC create(Db *db, const UpdateSqlNode &update_sql, Stmt *&stmt);
  
  StmtType type() const override
  {
    return StmtType::UPDATE;
  }
public:
  Table *table() const
  {
    return table_;
  }
  std::vector<Expression*> update_exprs() const {
    return update_exprs_;
  }

  std::vector<SelectStmt*> update_sub_querys() const {
    return update_sub_querys_;
  }
  int value_amount() const
  {
    return value_amount_;
  }
  std::vector<const FieldMeta*> update_fields() const{
    return update_fields_;
  }


  FilterStmt* filter_stmt() const{
    return filter_stmt_;
  }
private:
  Table *table_ = nullptr;                          //< 更新的表 
  std::vector<Expression*>  update_exprs_;          //< 更新值表达式 (可能是Value 也可能是 SubQuery), 这个内存要自己管理 TODO
  std::vector<SelectStmt*>   update_sub_querys_;    //< 更新的子表达式(用在 SubQueryExpr中) 
  int value_amount_ = 0;                            //< 更新几个
  std::vector<const FieldMeta*> update_fields_;     //< 更新的列
  FilterStmt* filter_stmt_ = nullptr;               //< 过滤谓词
};

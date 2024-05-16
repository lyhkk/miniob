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
// Created by Lyu Yiheng on 2024/05/07
//

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "common/rc.h"
#include "sql/expr/expression.h"
#include "sql/expr/tuple.h"
#include "sql/operator/physical_operator.h"
#include "sql/parser/value.h"

class Record;
class TupleCellSpec;
class Trx;

/**
 * @brief 与Group By相关的物理算子
 * @ingroup GroupByPhysicalOperator
 */
class GroupByPhysicalOperator : public PhysicalOperator
{
public:
  GroupByPhysicalOperator() = default;
  GroupByPhysicalOperator(std::vector<std::unique_ptr<Expression>>&& groupby_fields,
    std::vector<std::unique_ptr<AggrFunctionExpr>> &&aggr_exprs,
    std::vector<std::unique_ptr<FieldExpr>> &&field_exprs);

  virtual ~GroupByPhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::GROUPBY; }
  RC open(Trx *trx) override;
  RC next()         override;
  RC close()        override;

  Tuple *current_tuple() override { return &tuple_; }

  void add_child(std::unique_ptr<PhysicalOperator> oper) { children_.emplace_back(std::move(oper)); }

  std::vector<std::unique_ptr<PhysicalOperator>> &children() { return children_; }

private:
  GroupTuple tuple_;
  std::vector<std::unique_ptr<Expression>> groupby_exprs_;
  std::vector<Value> pre_groupby_values_;
  bool is_record_eof_;
  bool is_first_;
  bool is_new_group_;
};

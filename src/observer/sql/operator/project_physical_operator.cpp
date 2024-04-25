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
// Created by WangYunlai on 2022/07/01.
//

#include "sql/operator/project_physical_operator.h"
#include "common/log/log.h"
#include "storage/record/record.h"
#include "storage/table/table.h"

RC ProjectPhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  PhysicalOperator *child = children_[0].get();
  RC                rc    = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  return RC::SUCCESS;
}

RC ProjectPhysicalOperator::next()
{
  if (children_.empty()) {
    return RC::RECORD_EOF;
  }
  return children_[0]->next();
}

RC ProjectPhysicalOperator::close()
{
  if (!children_.empty()) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}
Tuple *ProjectPhysicalOperator::current_tuple()
{
  tuple_.set_tuple(children_[0]->current_tuple());
  return &tuple_;
}

void ProjectPhysicalOperator::add_projection(std::unique_ptr<Expression>&& project)
{
  // 对单表来说，展示的(alias) 字段总是字段名称，
  // 对多表查询来说，展示的alias 需要带表名字
  // const char *table_name = field.table_name();
  // const char *field_name = field.field_name();
  // int is_length_func = field.is_length_func_;
  // int is_round_func = field.is_round_func_;
  // int round_num = field.round_num_;
  // AggregateType aggregate_type = field.aggregate_type_;
  // std::string date_format = field.date_format_;
  // TupleCellSpec *spec = new TupleCellSpec(table_name, field_name, nullptr, is_length_func, is_round_func, round_num, date_format.c_str(), aggregate_type);
  // tuple_.add_cell_spec(spec);
  tuple_.add_expr(std::move(project));
}

void ProjectPhysicalOperator::add_projections(std::vector<std::unique_ptr<Expression>> &&projections)
{
  for (auto& project : projections) {
    add_projection(std::move(project));
  }
}

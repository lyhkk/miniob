/* Copyright (c) 2023 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2023/08/16.
// Modified by Chen Jiuhe on 2024/04/12.
//

#include "sql/optimizer/logical_plan_generator.h"

#include <common/log/log.h>
#include <memory>
#include <utility>

#include "sql/operator/calc_logical_operator.h"
#include "sql/operator/delete_logical_operator.h"
#include "sql/operator/explain_logical_operator.h"
#include "sql/operator/insert_logical_operator.h"
#include "sql/operator/join_logical_operator.h"
#include "sql/operator/logical_operator.h"
#include "sql/operator/predicate_logical_operator.h"
#include "sql/operator/project_logical_operator.h"
#include "sql/operator/table_get_logical_operator.h"
#include "sql/operator/update_logical_operator.h"
#include "sql/operator/groupby_logical_operator.h"
#include "sql/operator/orderby_logical_operator.h"

#include "sql/stmt/groupby_stmt.h"
#include "sql/stmt/orderby_stmt.h"
#include "sql/stmt/calc_stmt.h"
#include "sql/stmt/delete_stmt.h"
#include "sql/stmt/explain_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/insert_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/update_stmt.h"
#include "sql/stmt/join_stmt.h"
#include "sql/stmt/stmt.h"

using namespace std;

RC LogicalPlanGenerator::create(Stmt *stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  RC rc = RC::SUCCESS;
  switch (stmt->type()) {
    case StmtType::CALC: {
      CalcStmt *calc_stmt = static_cast<CalcStmt *>(stmt);

      rc = create_plan(calc_stmt, logical_operator);
    } break;

    case StmtType::SELECT: {
      SelectStmt *select_stmt = static_cast<SelectStmt *>(stmt);

      rc = create_plan(select_stmt, logical_operator);
    } break;

    case StmtType::INSERT: {
      InsertStmt *insert_stmt = static_cast<InsertStmt *>(stmt);

      rc = create_plan(insert_stmt, logical_operator);
    } break;

    case StmtType::DELETE: {
      DeleteStmt *delete_stmt = static_cast<DeleteStmt *>(stmt);

      rc = create_plan(delete_stmt, logical_operator);
    } break;

    case StmtType::EXPLAIN: {
      ExplainStmt *explain_stmt = static_cast<ExplainStmt *>(stmt);

      rc = create_plan(explain_stmt, logical_operator);
    } break;
    case StmtType::UPDATE: {
      UpdateStmt *update_stmt = static_cast<UpdateStmt *>(stmt);

      rc = create_plan(update_stmt, logical_operator);
    } break;
    default: {
      rc = RC::UNIMPLENMENT;
    }
  }
  return rc;
}

RC LogicalPlanGenerator::create_plan(GroupByStmt *groupby_stmt, std::unique_ptr<LogicalOperator> &logical_operator) {
  if (groupby_stmt == nullptr) {
    logical_operator = nullptr;
    return RC::SUCCESS;
  }

  unique_ptr<LogicalOperator> groupby_oper(
    new GroupByLogicalOperator(std::move(groupby_stmt->groupby_exprs()),
                            std::move(groupby_stmt->aggr_exprs()),
                            std::move(groupby_stmt->field_exprs())));
  logical_operator = std::move(groupby_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(OrderByStmt *orderby_stmt, std::unique_ptr<LogicalOperator> &logical_operator) {
  if (orderby_stmt == nullptr) {
    logical_operator = nullptr;
    return RC::SUCCESS;
  }

  unique_ptr<LogicalOperator> orderby_oper(
    new OrderByLogicalOperator(std::move(orderby_stmt->order_units()), std::move(orderby_stmt->exprs())));
  logical_operator = std::move(orderby_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(CalcStmt *calc_stmt, std::unique_ptr<LogicalOperator> &logical_operator)
{
  logical_operator.reset(new CalcLogicalOperator(std::move(calc_stmt->expressions())));
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(JoinStmt *join_stmt, const std::vector<Field> &fields,
    std::unique_ptr<LogicalOperator> &logical_operator, bool readonly)
{
  unique_ptr<LogicalOperator> table_oper;
  Table                      *table = join_stmt->table();
  // vector<Field>               current_fields;
  // for (auto field : fields) {
  //   if (strcmp(table->name(), field.table_name()) == 0) {
  //     current_fields.push_back(field);
  //   }
  // }

  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, fields, readonly /*readonly*/));
  table_oper = std::move(table_get_oper);

  // TODO 表别名

  RC rc = RC::SUCCESS;
  if (join_stmt->sub_join() == nullptr) {
    logical_operator.swap(table_oper);
    return rc;
  }

  unique_ptr<LogicalOperator> sub_op;
  rc = create_plan(join_stmt->sub_join().get(), fields, sub_op, readonly);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  JoinLogicalOperator *join_oper = new JoinLogicalOperator;
  join_oper->add_child(std::move(table_oper));
  join_oper->add_child(std::move(sub_op));
  if (join_stmt->condition() == nullptr) {
    logical_operator.reset(join_oper);
  } else {
    logical_operator.reset(new PredicateLogicalOperator(std::move(join_stmt->condition())));
    logical_operator->add_child(unique_ptr<LogicalOperator>(join_oper));
  }
  return rc;
}

RC LogicalPlanGenerator::create_plan(
    SelectStmt *select_stmt, unique_ptr<LogicalOperator> &logical_operator, bool readonly)
{
  unique_ptr<LogicalOperator> father_logical_oper(nullptr);
  unique_ptr<LogicalOperator> table_oper(nullptr);
  std::vector<unique_ptr<Expression>> &projects = select_stmt->projects();

  // 目前不需要all_fields在TableGetLogicalOperator
  std::vector<Field> all_fields;
  RC rc = RC::SUCCESS;
  if (select_stmt->join_stmt()) {
    JoinStmt *join_stmt = static_cast<JoinStmt *>(select_stmt->join_stmt().get());
    rc                  = create_plan(join_stmt, all_fields, table_oper, readonly);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    father_logical_oper = std::move(table_oper);
  }

  unique_ptr<LogicalOperator> predicate_oper;
  if (select_stmt->filter_stmt() != nullptr) {
    rc = create_plan(select_stmt->filter_stmt(), predicate_oper);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
      return rc;
    }
    if (predicate_oper) {
      if (father_logical_oper) {
        predicate_oper->add_child(std::move(father_logical_oper));
      }
      father_logical_oper = std::move(predicate_oper);
    }
  }

  unique_ptr<LogicalOperator> groupby_oper;
  unique_ptr<LogicalOperator> sortby_oper;
  if (select_stmt->groupby_stmt() != nullptr) {
    rc = create_plan(select_stmt->groupby_stmt(), groupby_oper);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
      return rc;
    }
    if (select_stmt->groupby_stmt()->sortby_stmt() != nullptr) {
      rc = create_plan(select_stmt->groupby_stmt()->sortby_stmt(), sortby_oper);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
        return rc;
      }
    }
    if (sortby_oper) {
      if (father_logical_oper) {
        sortby_oper->add_child(std::move(father_logical_oper));
      }
      father_logical_oper = std::move(sortby_oper);
    }
    
    if (groupby_oper) {
      if (father_logical_oper) {
        groupby_oper->add_child(std::move(father_logical_oper));
      }
      father_logical_oper = std::move(groupby_oper);
    }
  }

  unique_ptr<LogicalOperator> having_filter_oper;
  if (select_stmt->having_filter_stmt() != nullptr) {
    rc = create_plan(select_stmt->having_filter_stmt(), having_filter_oper);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
      return rc;
    }
    if (having_filter_oper) {
      if (father_logical_oper) {
        having_filter_oper->add_child(std::move(father_logical_oper));
      }
      father_logical_oper = std::move(having_filter_oper);
    }
  }

    if (select_stmt->orderby_stmt()) {
    unique_ptr<LogicalOperator> orderby_oper;
    rc = create_plan(select_stmt->orderby_stmt(), orderby_oper);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create orderby logical plan. rc=%s", strrc(rc));
      return rc;
    }
    if(orderby_oper){
      if (father_logical_oper) {
        orderby_oper->add_child(std::move(father_logical_oper));
      }
      father_logical_oper = std::move(orderby_oper);
    }
  }
  
  unique_ptr<LogicalOperator> project_oper(new ProjectLogicalOperator(projects));
  if (father_logical_oper) {
    project_oper->add_child(std::move(father_logical_oper));
  }

  logical_operator.swap(project_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(FilterStmt *filter_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  std::vector<unique_ptr<Expression>> cmp_exprs;
  if (filter_stmt == nullptr || filter_stmt->condition() == nullptr) {
    return RC::SUCCESS;
  }

  auto process_sub_query = [](Expression* expr) {
    if (expr->type() == ExprType::SUBQUERY) {
      SubQueryExpr* sub_query_expr = static_cast<SubQueryExpr*>(expr);
      return sub_query_expr->generate_subquery_logical_oper();
    }
    return RC::SUCCESS;
  };
  if (RC rc = filter_stmt->condition()->traverse_check(process_sub_query); OB_FAIL(rc)) {
    return rc;
  }
  
  cmp_exprs.emplace_back(std::move(filter_stmt->condition()));
  unique_ptr<PredicateLogicalOperator> predicate_oper;
  if (!cmp_exprs.empty()) {
    unique_ptr<ConjunctionExpr> conjunction_expr(new ConjunctionExpr(ConjunctionExpr::Type::AND, cmp_exprs));
    predicate_oper = unique_ptr<PredicateLogicalOperator>(new PredicateLogicalOperator(std::move(conjunction_expr)));
  }

  logical_operator = std::move(predicate_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(InsertStmt *insert_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table        *table = insert_stmt->table();
  vector<Value> values(insert_stmt->values(), insert_stmt->values() + insert_stmt->value_amount());

  InsertLogicalOperator *insert_operator = new InsertLogicalOperator(table, values);
  logical_operator.reset(insert_operator);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(DeleteStmt *delete_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table             *table       = delete_stmt->table();
  FilterStmt        *filter_stmt = delete_stmt->filter_stmt();
  std::vector<Field> fields;
  for (int i = table->table_meta().sys_field_num(); i < table->table_meta().field_num(); i++) {
    const FieldMeta *field_meta = table->table_meta().field(i);
    fields.push_back(Field(table, field_meta));
  }
  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, fields, false /*readonly*/));

  unique_ptr<LogicalOperator> predicate_oper;
  RC                          rc = create_plan(filter_stmt, predicate_oper);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  unique_ptr<LogicalOperator> delete_oper(new DeleteLogicalOperator(table));

  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    delete_oper->add_child(std::move(predicate_oper));
  } else {
    delete_oper->add_child(std::move(table_get_oper));
  }

  logical_operator = std::move(delete_oper);
  return rc;
}

RC LogicalPlanGenerator::create_plan(ExplainStmt *explain_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  unique_ptr<LogicalOperator> child_oper;

  Stmt *child_stmt = explain_stmt->child();

  RC rc = create(child_stmt, child_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create explain's child operator. rc=%s", strrc(rc));
    return rc;
  }

  logical_operator = unique_ptr<LogicalOperator>(new ExplainLogicalOperator);
  logical_operator->add_child(std::move(child_oper));
  return rc;
}

RC LogicalPlanGenerator::create_plan(UpdateStmt *update_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table             *table       = update_stmt->table();
  FilterStmt        *filter_stmt = update_stmt->filter_stmt();
  std::vector<Field> fields;
  for (int i = table->table_meta().sys_field_num(); i < table->table_meta().field_num(); i++) {
    const FieldMeta *field_meta = table->table_meta().field(i);
    fields.push_back(Field(table, field_meta));
  }
  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, fields, false /*readonly*/));

  unique_ptr<LogicalOperator> predicate_oper;
  RC                          rc = RC::SUCCESS;
  if (filter_stmt != nullptr) {
    RC rc = create_plan(filter_stmt, predicate_oper);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }
  std::vector<Value> values;
  values.push_back(*(update_stmt->values()));
  unique_ptr<LogicalOperator> update_oper(new UpdateLogicalOperator(table, values, *(update_stmt->fields())));

  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    update_oper->add_child(std::move(predicate_oper));
  } else {
    update_oper->add_child(std::move(table_get_oper));
  }

  logical_operator = std::move(update_oper);
  return rc;
}
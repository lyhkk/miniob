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
// Created by Wangyunlai on 2022/6/6.
//

#include "sql/stmt/select_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "common/rc.h"
#include "sql/expr/expression.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include <memory>
#include <type_traits>
#include <vector>

SelectStmt::~SelectStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
    if (nullptr != groupby_stmt_) {
    delete groupby_stmt_;
    groupby_stmt_ = nullptr;
  }
  if (nullptr != having_filter_stmt_) {
    delete having_filter_stmt_;
    having_filter_stmt_ = nullptr;
  }
  if (nullptr != orderby_stmt_) {
    delete orderby_stmt_;
    orderby_stmt_ = nullptr;
  }
}

static void wildcard_fields(Table *table, std::vector<std::unique_ptr<Expression>> &projects_exprs_, bool is_single_table)
{
  const TableMeta &table_meta = table->table_meta();
  const int        field_num  = table_meta.field_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    const FieldMeta* field_meta = table_meta.field(i);
    if (field_meta->visible()) {
      FieldExpr *tmp = new FieldExpr(table->name(), field_meta->name());
      tmp->set_field(table, field_meta);
      if (is_single_table) {
        tmp->set_name(tmp->field_name());
      } else {
        tmp->set_name(std::string(tmp->table_name()) + "." + tmp->field_name());
      }
      projects_exprs_.emplace_back(tmp);
    }
    // int           is_length_func = relation_attr.is_length_func;
    // int           is_round_func  = relation_attr.is_round_func;
    // std::string   date_format    = relation_attr.date_format;
    // int           round_num      = relation_attr.round_num;
    // AggregateType aggregate_type = relation_attr.aggregate_type;
    // aggregation function: 只有count可以做count(*)
    // if (aggregate_type != AggregateType::NONE && aggregate_type != AggregateType::COUNT_STAR) {
    //   LOG_WARN("invalid query field. The aggregate function cannot receive more than one field.");
    //   return RC::SCHEMA_FIELD_MISSING;
    // }
    // field_metas.push_back(
    //     Field(table, table_meta.field(i), is_length_func, is_round_func, round_num, date_format, aggregate_type));
    // if (aggregate_type == AggregateType::COUNT_STAR) {
    //   break;
    // }
  }
  return;
}

RC SelectStmt::create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  // collect tables in `from` statement
  std::vector<Table *>                     tables;
  std::unordered_map<std::string, Table *> table_map;

  RC                        rc = RC::SUCCESS;
  std::unique_ptr<JoinStmt> join_stmt;
  JoinTableSqlNode         *join_table = select_sql.table;
  if (join_table != nullptr) {
    JoinStmt *join = nullptr;
    rc             = JoinStmt::create(db, join_table, join, tables, table_map);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create join stmt");
      return rc;
    }
    join_stmt.reset(join);
  }

  JoinStmt                 *join_stmt_tmp = join_stmt.get();
  std::vector<std::unique_ptr<Expression>> condition;

  while (join_stmt_tmp != nullptr) {
    if (join_stmt_tmp->condition() != nullptr) {
      condition.emplace_back(join_stmt_tmp->condition().release());
      // join_stmt_tmp->condition() = nullptr;
    }
    join_stmt_tmp = join_stmt_tmp->sub_join().get();
  }
  if (!condition.empty()) {
    ConjunctionExpr *conditionExpr = new ConjunctionExpr(ConjunctionExpr::Type::AND, condition);
    join_stmt.get()->set_condition(std::unique_ptr<Expression>(conditionExpr));
  }

  bool has_aggregate_func = false;
  bool is_single_table = (tables.size() == 1);
  Table *default_table = nullptr;
  if (is_single_table) {
    default_table = tables[0];
  }

  auto check_project_expr = [&table_map, &tables, &default_table, &has_aggregate_func](Expression *expr) -> RC {
    if (expr->type() == ExprType::FIELD) {
      FieldExpr *field_expr = static_cast<FieldExpr*>(expr);
      if (field_expr->check_field(table_map, tables, default_table) != RC::SUCCESS) {
        return RC::SCHEMA_FIELD_MISSING;
      }
    }
    else if (expr->type() == ExprType::FUNCTION) {
      FuncExpr *func_expr = static_cast<FuncExpr*>(expr);
      if (func_expr->check_function_param_type() != RC::SUCCESS) {
        return RC::SCHEMA_FIELD_MISSING;
      }
    }
    else if (expr->type() == ExprType::AGGRFUNCTION) {
      AggrFunctionExpr *agg_expr = static_cast<AggrFunctionExpr*>(expr);
      if (agg_expr->check_aggregate_func_type() != RC::SUCCESS) {
        return RC::SCHEMA_FIELD_MISSING;
      }
      has_aggregate_func = true;
    }
    else if (expr->type() == ExprType::SUBQUERY) {
      return RC::INVALID_ARGUMENT;
    }
    return RC::SUCCESS;
  };

  // projection in `select` statement
  std::vector<std::unique_ptr<Expression>> projects_query;
  for (int i = 0; i < static_cast<int>(select_sql.proj_exprs.size()); i++) {
    Expression *expr = select_sql.proj_exprs[i];
    ExprType expr_type = expr->type();
    if (expr_type == ExprType::FIELD) {
      FieldExpr  *field_expr = static_cast<FieldExpr*>(expr);
      const char *table_name = field_expr->table_name();
      const char *field_name = field_expr->field_name();
      ASSERT(!common::is_blank(field_name), "Parse ERROR!");

      if (0 == strcmp(table_name, "*") && 0 == strcmp(field_name, "*")) {
        if (tables.empty() || !field_expr->alias().empty()) {
          return RC::INVALID_ARGUMENT; // not allow: select *; select * as xxx;
        }
        for (Table *table : tables) {
          wildcard_fields(table, projects_query, is_single_table);
        }
      } 
      else if (0 == strcmp(field_name, "*")) {
        auto iter = table_map.find(table_name);
        if (iter == table_map.end()) {
          LOG_WARN("no such table in from list: %s", table_name);
          return RC::SCHEMA_FIELD_MISSING;
        }

        Table *table = iter->second;
        wildcard_fields(table, projects_query, is_single_table);
      }
      else {
        if(field_expr->check_field(table_map, tables, default_table) != RC::SUCCESS) {
          LOG_INFO("expr->check_field error!");
          return RC::SCHEMA_FIELD_MISSING;
        }
        projects_query.emplace_back(expr);
      }
    }
    else {
      if (rc = expr->traverse_check(check_project_expr); rc != RC::SUCCESS) {
        LOG_WARN("project expr traverse check_field error!");
        return rc;
      }
      projects_query.emplace_back(expr);
    }
  }
  select_sql.proj_exprs.clear();
  LOG_INFO("got %d tables in from stmt and %d fields in query stmt", tables.size(), projects_query.size());

  // create filter statement in `where` statement
  FilterStmt * filter_stmt = nullptr;
  rc                      = FilterStmt::create(db,
      default_table,
      &table_map,
      select_sql.conditions,
      filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  GroupByStmt *groupby_stmt = nullptr;
  FilterStmt *having_filter_stmt = nullptr;
  if (!select_sql.groupby_exprs.empty() || has_aggregate_func) {
    // 1. 提取 AggrFuncExpr 以及不在 AggrFuncExpr 中的 FieldExpr
    std::vector<std::unique_ptr<AggrFunctionExpr>> aggr_exprs;
    //select 子句中出现的所有 fieldexpr 都需要传递收集起来,
    std::vector<std::unique_ptr<FieldExpr>> field_exprs;//这个 vector 需要传递给 order by 算子
    std::vector<std::unique_ptr<Expression>> field_exprs_not_aggr; //select 后的所有非 aggrexpr 的 field_expr,用来判断语句是否合法 
    // 用于从 project exprs 中提取所有 aggr func exprs. e.g. min(c1 + 1) + 1
    auto collect_aggr_exprs = [&aggr_exprs](Expression * expr) {
      if (expr->type() == ExprType::AGGRFUNCTION) {
        aggr_exprs.emplace_back(static_cast<AggrFunctionExpr*>(static_cast<AggrFunctionExpr*>(expr)->unique_ptr_copy().release()));
      }
    };
    // 用于从 project exprs 中提取所有field expr,
    auto collect_field_exprs = [&field_exprs](Expression * expr) {
      if (expr->type() == ExprType::FIELD) {
        field_exprs.emplace_back(static_cast<FieldExpr*>(static_cast<FieldExpr*>(expr)->unique_ptr_copy().release()));
      }
    };
    // 用于从 project exprs 中提取所有不在 aggr func expr 中的 field expr
    auto collect_exprs_not_aggexpr = [&field_exprs_not_aggr](Expression * expr) {
        if (expr->type() == ExprType::FIELD) {
        field_exprs_not_aggr.emplace_back(static_cast<FieldExpr*>(static_cast<FieldExpr*>(expr)->unique_ptr_copy().release()));
      }
    };
    // do extract
    for (auto& project : projects_query) {
      project->traverse(collect_aggr_exprs, [](const Expression *) { return true; }); //提取所有 aggexpr
      project->traverse(collect_field_exprs, [](const Expression *) { return true; }); //提取 select clause 中的所有 field_expr,传递给groupby stmt
      //project->traverse(collect_field_exprs, [](const Expression* expr) { return expr->type() != ExprType::AGGRFUNCTION; });

      //提取所有不在 aggexpr 中的 field_expr，用于语义检查
      project->traverse(collect_exprs_not_aggexpr,[](const Expression* expr) { return expr->type() != ExprType::AGGRFUNCTION; });
    }

    // 2. 创建 having filter stmt
    if (select_sql.having_condition != nullptr) {
      rc = FilterStmt::create(db, default_table, &table_map, select_sql.having_condition, having_filter_stmt);
      if (rc != RC::SUCCESS) {
        LOG_WARN("cannot construct having filter stmt");
        return rc;
      }
      auto & filter_expr = having_filter_stmt->condition();
      filter_expr->traverse(collect_aggr_exprs, [](const Expression *) { return true; });
      filter_expr->traverse(collect_field_exprs, [](const Expression *) { return true; });
      filter_expr->traverse(collect_exprs_not_aggexpr,[](const Expression* expr) { return expr->type() != ExprType::AGGRFUNCTION; });
    }

    // 3. AggrFunction 语义检查是否有字段和聚合函数混合使用（无group by时）
    if (!field_exprs_not_aggr.empty() && select_sql.groupby_exprs.size() == 0) {
      LOG_WARN("No Group By. But Has Fields Not In Aggr Func");
      return RC::INVALID_ARGUMENT;
    }

    // 4. Group By 语义检查
    OrderByStmt *groupby_orderby_stmt = nullptr;
    if (!select_sql.groupby_exprs.empty()) {
      // 4.1 Group By 的project exprs 语义检查，投影的非聚合函数表达式必须在 group by 中
      for (auto & project_expr : projects_query) {
        if (project_expr->type() == ExprType::AGGRFUNCTION) continue;
        bool found = false;
        for (auto & groupby_expr : select_sql.groupby_exprs) {
          if (project_expr->name() == groupby_expr->name()) {
            found = true;
            break;
          }
        }
        if (!found) {
          LOG_WARN("Group By Check Failure: Project Expression Not In Group By Clause");
          return RC::INVALID_ARGUMENT;
        }
      }

      // 4.2 Group by 使用的expression的合法性检查
      for (auto & groupby_expr : select_sql.groupby_exprs) {
        if (groupby_expr->traverse_check(check_project_expr) != RC::SUCCESS) {
          LOG_WARN("Group By Check Failure: Group By Expression Check Failure");
          return RC::INVALID_ARGUMENT;
        }
      }

      // 4.3 构造 group by 的 sort stmt
      std::vector<std::unique_ptr<OrderByUnit>> groupby_orderby_units;
      std::vector<std::unique_ptr<Expression>>  sort_exprs;
      for (auto groupby_expr : select_sql.groupby_exprs) {
        Expression *unit = groupby_expr->unique_ptr_copy().release();
        groupby_orderby_units.emplace_back(std::make_unique<OrderByUnit>(unit, true));
      }
      groupby_orderby_stmt = new OrderByStmt();
      groupby_orderby_stmt->set_orderby_units(std::move(groupby_orderby_units));
      for (auto & field_expr : field_exprs) {
        sort_exprs.emplace_back(field_expr->unique_ptr_copy().release());
      }
      for (auto & groupby_expr : select_sql.groupby_exprs) {
        sort_exprs.emplace_back(groupby_expr->unique_ptr_copy().release());
      }
      groupby_orderby_stmt->set_exprs(std::move(sort_exprs));
    }
    // 5. 创建 groupby stmt
    rc = GroupByStmt::create(
      select_sql.groupby_exprs,
      groupby_stmt,
      std::move(aggr_exprs), 
      std::move(field_exprs),
      groupby_orderby_stmt);
    select_sql.groupby_exprs.clear();
  }

  OrderByStmt *orderby_stmt = nullptr;
  if (!select_sql.orderby_nodes.empty()) {

    // 1. 提取所有select子句的fields和聚合函数的结果传递给OrderByStmt，
    // 根源：因为orderby的物理算子是group_by的父亲，聚合函数在group_by中计算，所以需要传递给orderby，再传给proj
    std::vector<std::unique_ptr<Expression>> orderby_proj_fields;

    auto collect_orderby_proj = [&orderby_proj_fields](Expression * expr) {
      if (expr->type() == ExprType::FIELD) {
        orderby_proj_fields.emplace_back(static_cast<FieldExpr*>(static_cast<FieldExpr*>(expr)->unique_ptr_copy().release()));
      }
    };
    auto collect_orderby_aggr = [&orderby_proj_fields](Expression * expr) {
      if (expr->type() == ExprType::AGGRFUNCTION) {
        orderby_proj_fields.emplace_back(static_cast<AggrFunctionExpr*>(static_cast<AggrFunctionExpr*>(expr)->unique_ptr_copy().release()));
      }
    };

    for (auto& project : projects_query) {
      project->traverse(collect_orderby_aggr, [](const Expression *) { return true; });
      project->traverse(collect_orderby_proj, [](const Expression *expr) { return expr->type() != ExprType::AGGRFUNCTION; });
    }

    for (size_t i = 0 ; i < select_sql.orderby_nodes.size() ; i++){
      Expression* expr = select_sql.orderby_nodes[i].expr;
      if (rc = expr->traverse_check(check_project_expr); rc != RC::SUCCESS) {
      LOG_WARN("project expr traverse check_field error!");
      return rc;
      }
    }
    rc = OrderByStmt::create(db,
      select_sql.orderby_nodes,
      std::move(orderby_proj_fields),
      orderby_stmt);

    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot construct orderby stmt");
      return rc;
    }
    select_sql.orderby_nodes.clear();
  }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();
  select_stmt->tables_.swap(tables);
  select_stmt->projects_query_.swap(projects_query);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->join_stmt_.swap(join_stmt);
  select_stmt->groupby_stmt_ = groupby_stmt;
  select_stmt->having_filter_stmt_ = having_filter_stmt;
  select_stmt->orderby_stmt_ = orderby_stmt;
  stmt = select_stmt;

  return RC::SUCCESS;
}

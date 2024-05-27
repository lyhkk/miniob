#include "common/rc.h"
#include "common/log/log.h"
#include "sql/stmt/join_stmt.h"
#include "sql/parser/parse_defs.h"
#include "storage/table/table.h"

RC get_table(Db *db, const char *table_name, Table *&table)
{
  if (nullptr == table_name) {
    LOG_ERROR("invalid argument. relation name is null.");
    return RC::INVALID_ARGUMENT;
  }

  Table *tmp = db->find_table(table_name);
  if (nullptr == tmp) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  table = tmp;
  return RC::SUCCESS;
}

RC JoinStmt::create(Db *db, JoinTableSqlNode *&sql_node, JoinStmt *&stmt, std::vector<Table *> &tables,
    std::unordered_map<std::string, Table *> &table_map)
{
  Table *table;
  RC     rc = get_table(db, sql_node->relation_name.c_str(), table);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  tables.push_back(table);
  table_map.insert(std::pair<std::string, Table *>(sql_node->relation_name, table));

  std::string alias_name = table->name();
  // TODO 表别名alias

  stmt              = new JoinStmt;
  stmt->alias_name_ = alias_name;
  stmt->table_      = table;
  if (sql_node->sub_join == nullptr) {
    return RC::SUCCESS;
  }

  JoinStmt *sub_join = nullptr;
  rc                 = create(db, sql_node->sub_join, sub_join, tables, table_map);
  if (rc != RC::SUCCESS) {
    delete stmt;
    return rc;
  }
  stmt->sub_join_.reset(sub_join);

  auto check_condition = [&db, &table_map, &table](Expression *expr) -> RC {
    if (expr->type() == ExprType::COMPARISON) {
      ComparisonExpr* cmp_expr = static_cast<ComparisonExpr*>(expr);
      CompOp comp = cmp_expr->comp();
      if (comp < EQUAL_TO || comp >= NO_OP) {
        LOG_WARN("invalid compare operator : %d", comp);
        return RC::INVALID_ARGUMENT;
      }
    }
    else if (expr->type() == ExprType::FIELD) {
      FieldExpr* field_expr = static_cast<FieldExpr*>(expr);
      return field_expr->check_field(table_map, {}, table, {});
    }
    else if (expr->type() == ExprType::FUNCTION) {
      FuncExpr* func_expr = static_cast<FuncExpr*>(expr);
      return func_expr->check_function_param_type();
    }
    return RC::SUCCESS;
  };

  if (sql_node->sub_join != nullptr && sql_node->sub_join->join_condition != nullptr) {
    if (sql_node->sub_join->join_condition->traverse_check(check_condition) != RC::SUCCESS) {
      return RC::INVALID_ARGUMENT;
    }

    stmt->condition_ = std::unique_ptr<Expression>(sql_node->sub_join->join_condition);
  }

  return rc;
}

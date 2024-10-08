#pragma once

#include "sql/expr/expression.h"
#include "sql/parser/parse_defs.h"
#include "storage/table/table.h"
#include "storage/db/db.h"
#include "sql/stmt/filter_stmt.h"

class JoinStmt
{
public:
  Table                    *&table() { return table_; }
  std::string               &alias_name() { return alias_name_; }
  std::unique_ptr<JoinStmt> &sub_join() { return sub_join_; }
  std::unique_ptr<Expression> &condition() { return condition_; }
  void set_condition(std::unique_ptr<Expression> condition) {
    condition_ = std::move(condition);
  }

  static RC create(Db *db, JoinTableSqlNode *&sql_node, JoinStmt *&stmt, std::vector<Table *> &table,
      std::unordered_map<std::string, Table *> &table_map);

private:
  Table                    *table_ = nullptr;
  std::string               alias_name_;
  std::unique_ptr<JoinStmt> sub_join_;
  std::unique_ptr<Expression> condition_;
};
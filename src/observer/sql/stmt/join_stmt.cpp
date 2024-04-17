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

  if (!sql_node->join_condition.empty()) {
    FilterStmt               *tmp_stmt = new FilterStmt();
    std::vector<FilterUnit *> tmp_filter_units;

    for (int i = 0; i < static_cast<int>(sql_node->join_condition.size()); i++) {
      FilterUnit *filter_unit = nullptr;

      rc = FilterStmt::create_filter_unit(db, table, &table_map, sql_node->join_condition[i], filter_unit);
      if (rc != RC::SUCCESS) {
        delete tmp_stmt;
        LOG_WARN("failed to create filter unit. condition index=%d", i);
        return rc;
      }
      tmp_filter_units.push_back(filter_unit);
    }
    tmp_stmt->filter_units().swap(tmp_filter_units);
    stmt->condition_ = tmp_stmt;
  }

  return rc;
}
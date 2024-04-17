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
#include "sql/parser/parse_defs.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

SelectStmt::~SelectStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

static RC wildcard_fields(Table *table, std::vector<Field> &field_metas, RelAttrSqlNode relation_attr)
{
  const TableMeta &table_meta = table->table_meta();
  const int        field_num  = table_meta.field_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    int is_length_func = relation_attr.is_length_func;
    int is_round_func = relation_attr.is_round_func;
    std::string date_format = relation_attr.date_format;
    int round_num = relation_attr.round_num;
    AggregateType aggregate_type = relation_attr.aggregate_type;
    // aggregation function: 只有count可以做count(*)
    if (aggregate_type != AggregateType::NONE && aggregate_type != AggregateType::COUNT_STAR) {
      LOG_WARN("invalid query field. The aggregate function cannot receive more than one field.");
      return RC::SCHEMA_FIELD_MISSING;
    }
    field_metas.push_back(Field(table, table_meta.field(i), is_length_func, is_round_func, round_num, date_format, aggregate_type));
    if (aggregate_type == AggregateType::COUNT_STAR) {
      break;
    }
  }
  return RC::SUCCESS;
}

RC SelectStmt::create(Db *db, const SelectSqlNode &select_sql, Stmt *&stmt)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  // collect tables in `from` statement
  std::vector<Table *>                     tables;
  std::unordered_map<std::string, Table *> table_map;
  for (size_t i = 0; i < select_sql.relations.size(); i++) {
    const char *table_name = select_sql.relations[i].c_str();
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    tables.push_back(table);
    table_map.insert(std::pair<std::string, Table *>(table_name, table));
  }

  // collect query fields in `select` statement
  std::vector<Field> query_fields;
  for (int i = static_cast<int>(select_sql.attributes.size()) - 1; i >= 0; i--) {
    const RelAttrSqlNode &relation_attr = select_sql.attributes[i];

    // aggregation function: 对于count(a, b)和count()这种聚合函数调用的方法, 就要报错 -> Failure
    if (0 == strcmp(relation_attr.attribute_name.c_str(), "*") &&
        0 == strcmp(relation_attr.relation_name.c_str(), "*")) {
      LOG_WARN("invalid query field. The aggregate function cannot receive more than one field.");
      return RC::SCHEMA_FIELD_MISSING;
    }

    if (common::is_blank(relation_attr.relation_name.c_str()) &&
        0 == strcmp(relation_attr.attribute_name.c_str(), "*")) {
      for (Table *table : tables) {
        if (wildcard_fields(table, query_fields, relation_attr) != RC::SUCCESS) {
          return RC::SCHEMA_FIELD_MISSING;
        }
      }
    }
    else if (!common::is_blank(relation_attr.relation_name.c_str())) {
      const char *table_name = relation_attr.relation_name.c_str();
      const char *field_name = relation_attr.attribute_name.c_str();

      if (0 == strcmp(table_name, "*")) {
        if (0 != strcmp(field_name, "*")) {
          LOG_WARN("invalid field name while table is *. attr=%s", field_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        for (Table *table : tables) {
          if (wildcard_fields(table, query_fields, relation_attr) != RC::SUCCESS) {
            return RC::SCHEMA_FIELD_MISSING;
          }
        }
      } 
      // 一个表的一个字段
      else {
        auto iter = table_map.find(table_name);
        if (iter == table_map.end()) {
          LOG_WARN("no such table in from list: %s", table_name);
          return RC::SCHEMA_FIELD_MISSING;
        }

        Table *table = iter->second;
        if (0 == strcmp(field_name, "*")) {
          if (wildcard_fields(table, query_fields, relation_attr) != RC::SUCCESS) {
            return RC::SCHEMA_FIELD_MISSING;
          }
        } else {
          const FieldMeta *field_meta = table->table_meta().field(field_name);
          if (nullptr == field_meta) {
            LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
            return RC::SCHEMA_FIELD_MISSING;
          }
          query_fields.push_back(Field(table, field_meta, relation_attr.is_length_func, relation_attr.is_round_func, 
            relation_attr.round_num, relation_attr.date_format, relation_attr.aggregate_type));
        }
      }
    } else {
      if (tables.size() != 1) {
        LOG_WARN("invalid. I do not know the attr's table. attr=%s", relation_attr.attribute_name.c_str());
        return RC::SCHEMA_FIELD_MISSING;
      }

      Table           *table      = tables[0];
      const FieldMeta *field_meta = table->table_meta().field(relation_attr.attribute_name.c_str());
      if (nullptr == field_meta) {
        LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), relation_attr.attribute_name.c_str());
        return RC::SCHEMA_FIELD_MISSING;
      }

      Field            field      = Field(table, field_meta, relation_attr.is_length_func, relation_attr.is_round_func, 
                                            relation_attr.round_num, relation_attr.date_format, relation_attr.aggregate_type);
      
      // function: 检查函数类型是否匹配
      RC rc = field.check_function_type(relation_attr);
      if (rc != RC::SUCCESS) {
        return rc;
      }

      // aggregation function: 检查类型是否匹配
      rc = field.check_aggregate_func_type(relation_attr);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      query_fields.push_back(field);
    }
  }

  // Aggregate function: select id, max(age) from student 这种混合使用是不考虑的
  for (long unsigned int i = 0; i < query_fields.size(); i++) {
    if (query_fields[i].aggregate_type_ != AggregateType::NONE) {
      for (long unsigned int j = i + 1; j < query_fields.size(); j++) {
        if (query_fields[j].aggregate_type_ == AggregateType::NONE) {
          LOG_WARN("invalid query field. The aggregate function cannot mix with other common fields.");
          return RC::SCHEMA_FIELD_MISSING;
        }
      }
      break;
    }
    else {
      for (long unsigned int j = i + 1; j < query_fields.size(); j++) {
        if (query_fields[j].aggregate_type_ != AggregateType::NONE) {
          LOG_WARN("invalid query field. The aggregate function cannot mix with other common fields.");
          return RC::SCHEMA_FIELD_MISSING;
        }
      }
      break;
    }
  }

  LOG_INFO("got %d tables in from stmt and %d fields in query stmt", tables.size(), query_fields.size());

  Table *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
  }

  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  RC          rc          = FilterStmt::create(db,
      default_table,
      &table_map,
      select_sql.conditions.data(),
      static_cast<int>(select_sql.conditions.size()),
      filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();
  // TODO add expression copy
  select_stmt->tables_.swap(tables);
  select_stmt->query_fields_.swap(query_fields);
  select_stmt->filter_stmt_ = filter_stmt;
  stmt                      = select_stmt;
  return RC::SUCCESS;
}

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

#include "sql/stmt/filter_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "common/rc.h"
#include "storage/db/db.h"
#include "storage/index/index_meta.h"
#include "storage/table/table.h"

RC FilterStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      Expression *conditions, FilterStmt *&stmt)
{
  RC rc = RC::SUCCESS;
  stmt  = nullptr;
  if (conditions == nullptr) {
    return rc;
  }

  auto check_condition = [&db, &tables, &default_table](Expression *expr) -> RC {
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
      return field_expr->check_field(*tables, {}, default_table, {});
    }
    return RC::SUCCESS;
  };

  FilterStmt *tmp_stmt = new FilterStmt();
  if (conditions->traverse_check(check_condition) != RC::SUCCESS) {
    delete tmp_stmt;
    return RC::INVALID_ARGUMENT;
  }

  tmp_stmt->condition_ = std::unique_ptr<Expression>(conditions);
  stmt = tmp_stmt;
  return rc;
}

// RC get_table_and_field(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
//     const RelAttrSqlNode &attr, Table *&table, const FieldMeta *&field)
// {
//   if (common::is_blank(attr.relation_name.c_str())) {
//     table = default_table;
//   } else if (nullptr != tables) {
//     auto iter = tables->find(attr.relation_name);
//     if (iter != tables->end()) {
//       table = iter->second;
//     }
//   } else {
//     table = db->find_table(attr.relation_name.c_str());
//   }
//   if (nullptr == table) {
//     LOG_WARN("No such table: attr.relation_name: %s", attr.relation_name.c_str());
//     return RC::SCHEMA_TABLE_NOT_EXIST;
//   }
//   field = table->table_meta().field(attr.attribute_name.c_str());
//   if (nullptr == field) {
//     LOG_WARN("no such field in table: table %s, field %s", table->name(), attr.attribute_name.c_str());
//     table = nullptr;
//     return RC::SCHEMA_FIELD_NOT_EXIST;
//   }

//   return RC::SUCCESS;
// }

// RC FilterStmt::create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
//     const ConditionSqlNode &condition, FilterUnit *&filter_unit)
// {
//   RC rc = RC::SUCCESS;

//   CompOp comp = condition.comp;
//   if (comp < EQUAL_TO || comp >= NO_OP) {
//     LOG_WARN("invalid compare operator : %d", comp);
//     return RC::INVALID_ARGUMENT;
//   }

//   filter_unit = new FilterUnit;

//   if (condition.left_is_attr) {
//     Table           *table = nullptr;
//     const FieldMeta *field = nullptr;
//     rc                     = get_table_and_field(db, default_table, tables, condition.left_attr, table, field);
//     if (rc != RC::SUCCESS) {
//       LOG_WARN("cannot find attr");
//       return rc;
//     }
//     FilterObj filter_obj;
//     int is_length_func = condition.left_attr.is_length_func;
//     int is_round_func  = condition.left_attr.is_round_func;
//     std::string date_format = condition.left_attr.date_format;
//     int round_num = condition.left_attr.round_num;
//     Field field_obj = Field(table, field, is_length_func, is_round_func, round_num, date_format);
//     RC rc = field_obj.check_function_type(condition.left_attr);
//     if (rc != RC::SUCCESS) {
//       return rc;
//     }
//     filter_obj.init_attr(field_obj);
//     filter_unit->set_left(filter_obj);
//   } else {
//     FilterObj filter_obj;
//     filter_obj.init_value(condition.left_value);
//     filter_unit->set_left(filter_obj);
//   }

//   if (condition.right_is_attr) {
//     Table           *table = nullptr;
//     const FieldMeta *field = nullptr;
//     rc                     = get_table_and_field(db, default_table, tables, condition.right_attr, table, field);
//     if (rc != RC::SUCCESS) {
//       LOG_WARN("cannot find attr");
//       return rc;
//     }
//     FilterObj filter_obj;
//     int is_length_func = condition.right_attr.is_length_func;
//     int is_round_func  = condition.right_attr.is_round_func;
//     std::string date_format = condition.right_attr.date_format;
//     int round_num = condition.right_attr.round_num;
//     Field field_obj = Field(table, field, is_length_func, is_round_func, round_num, date_format);
//     RC rc = field_obj.check_function_type(condition.right_attr);
//     if (rc != RC::SUCCESS) {
//       return rc;
//     }
//     filter_obj.init_attr(field_obj);
//     filter_unit->set_right(filter_obj);
//   } else {
//     FilterObj filter_obj;
//     filter_obj.init_value(condition.right_value);
//     filter_unit->set_right(filter_obj);
//   }

//   filter_unit->set_comp(comp);

//   // 检查两个类型是否能够比较
//   /*
//   AttrType left_type  = filter_unit->left().field.attr_type();
//   AttrType right_type = filter_unit->right().field.attr_type();
//   // 如果是函数类型，需要检查函数返回值类型是否一致
//   if (filter_unit->left().field.get_function_type() != filter_unit->right().get_function_type()) {
//     LOG_WARN("filter left&right type mismatch");
//     return RC::INVALID_ARGUMENT;
//   }*/
//   return rc;
// }

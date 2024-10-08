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
// Created by Longda on 2021/4/13.
//

#include <string.h>
#include <string>

#include "event/sql_debug.h"
#include "parse_stage.h"

#include "common/conf/ini.h"
#include "common/io/io.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "event/session_event.h"
#include "event/sql_event.h"
#include "sql/parser/parse.h"

using namespace common;

// RC check_where_clause(ParsedSqlResult *sql_result)
// {
//   int is_right_illegal_date = 0;
//   for (auto &sql_node : sql_result->sql_nodes()) {
//     switch (sql_node->flag) {
//       case SCF_SELECT: {
//         for (auto sql_condition : sql_node.get()->selection.conditions) {
//           is_right_illegal_date = sql_condition.right_value.undefined_value();
//         }
//       }break;
//       case SCF_UPDATE: {
//         for (auto sql_condition : sql_node.get()->selection.conditions) {
//           is_right_illegal_date = sql_condition.right_value.undefined_value();
//         }
//       }
//       break;
//       default:
//         break;
//     }
//   }
//   return is_right_illegal_date == 1 ? RC::SQL_SYNTAX : RC::SUCCESS;
// }

RC ParseStage::handle_request(SQLStageEvent *sql_event)
{
  RC rc = RC::SUCCESS;

  SqlResult         *sql_result = sql_event->session_event()->sql_result();
  const std::string &sql        = sql_event->sql();

  ParsedSqlResult parsed_sql_result;

  parse(sql.c_str(), &parsed_sql_result);
  // check date format, if date format is illegal, return error
  // if (check_where_clause(&parsed_sql_result) != RC::SUCCESS) {
  //   sql_result->set_return_code(RC::INVALID_ARGUMENT);
  //   return RC::INVALID_ARGUMENT;
  // }
  if (parsed_sql_result.sql_nodes().empty()) {
    sql_result->set_return_code(RC::SUCCESS);
    sql_result->set_state_string("");
    return RC::INTERNAL;
  }

  if (parsed_sql_result.sql_nodes().size() > 1) {
    LOG_WARN("got multi sql commands but only 1 will be handled");
  }

  std::unique_ptr<ParsedSqlNode> sql_node = std::move(parsed_sql_result.sql_nodes().front());
  if (sql_node->flag == SCF_ERROR) {
    // set error information to event
    rc = RC::SQL_SYNTAX;
    sql_result->set_return_code(rc);
    sql_result->set_state_string("");
    sql_debug("parse sql error, sql:%s", sql.c_str());
    return rc;
  }

  sql_event->set_sql_node(std::move(sql_node));

  return RC::SUCCESS;
}

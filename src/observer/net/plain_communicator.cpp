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
// Created by Wangyunlai on 2023/06/25.
//

#include "net/plain_communicator.h"
#include "common/io/io.h"
#include "common/log/log.h"
#include "net/buffered_writer.h"
#include "session/session.h"
#include "sql/expr/tuple.h"
#include <cstdio>
#include <regex>
#include <cmath>

using namespace std;

static RC aggregation_output(vector<string> collum_value, BufferedWriter *writer, SqlResult *sql_result) {
  for (long unsigned int i = 0; i < collum_value.size(); i++) {
    if (i != 0) {
      const char *delim = " | ";

      RC rc = writer->writen(delim, strlen(delim));
      if (OB_FAIL(rc)) {
        LOG_WARN("failed to send data to client. err=%s", strerror(errno));
        sql_result->close();
        return rc;
      }
    }

    string cell_str;
    cell_str = collum_value[i];
    // 如果是float形式的字符串
    regex pattern("\\d+(\\.\\d+)?");
    if (regex_match(cell_str, pattern)) {
      float cell_float = stof(cell_str);
      int cell_int;
      size_t pos = cell_str.find('.');
      if (cell_str.size() - pos > 3) {
        // 精确到小数点后两位
        cell_int = round(cell_float * 100);
        cell_str = to_string(cell_int);
        cell_str.insert(cell_str.end() -  2, '.');
      }
      pos = cell_str.find('.');
      if (pos != string::npos) {
        // Find the last non-zero digit after the decimal point
        while (cell_str.back() == '0') {
          cell_str.pop_back();
        }
        if (cell_str.back() == '.') {
          cell_str.pop_back();
        }
      }
    }
    RC rc = writer->writen(cell_str.data(), cell_str.size());
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to send data to client. err=%s", strerror(errno));
      sql_result->close();
      return rc;
    }
  }
  return RC::SUCCESS;
}

static void set_avg_value(int count, vector<pair<AggregateType, string>> &cell_value, vector<string> &collum_value) {
  int i = 0;
  for (auto &it : cell_value) {
    AggregateType aggregate_type = it.first;
    if (aggregate_type == AggregateType::AVG) {
      // 精确到小数点后两位
      float value = stof(collum_value[i]);
      float avg = static_cast<double>(value) / count;
      collum_value[i] = to_string(avg);
    }
    i++;
  }
}

static void aggregation_compute(int count, vector<pair<AggregateType, string>> &cell_value, vector<string> &collum_value, vector<AttrType> &cell_type) {
  int i = 0;
  for (auto &it : cell_value) {
    AggregateType aggregate_type = it.first;
    string value = it.second;
    AttrType attr_type = cell_type[i];
    string count_str = to_string(count);
    switch (aggregate_type) {
      case AggregateType::COUNT:
        if (count == 1) {
          collum_value.push_back(count_str);
        } else {
          collum_value[i] = count_str;
        }
        break;
      case AggregateType::COUNT_STAR:
        if (count == 1) {
          collum_value.push_back(count_str);
        } else {
          collum_value[i] = count_str;
        }
        break;
      case AggregateType::MAX:
        if (count == 1) {
          collum_value.push_back(value);
        } else {
          if (attr_type == AttrType::CHARS || attr_type == AttrType::DATES) {
            collum_value[i] = collum_value[i] > value ? collum_value[i] : value;
          } else {
            float collum_float = stof(collum_value[i]);
            float value_float = stof(value);
            collum_value[i] = to_string(collum_float > value_float ? collum_float : value_float);
          }
        }
        break;
      case AggregateType::MIN:
        if (count == 1) {
          collum_value.push_back(value);
        } else {
          if (attr_type == AttrType::CHARS || attr_type == AttrType::DATES) {
            collum_value[i] = collum_value[i] < value ? collum_value[i] : value;
          } else {
            float collum_float = stof(collum_value[i]);
            float value_float = stof(value);
            collum_value[i] = to_string(collum_float < value_float ? collum_float : value_float);
          }
        }
        break;
      case AggregateType::SUM:
      case AggregateType::AVG:
        if (count == 1) {
          collum_value.push_back(value);
        } else {
          float collum_float = stof(collum_value[i]);
          float value_float = stof(value);
          collum_value[i] = to_string(collum_float + value_float);
        }
        break;
      default:
        break;
    }
    i++;
  }
}

PlainCommunicator::PlainCommunicator()
{
  send_message_delimiter_.assign(1, '\0');
  debug_message_prefix_.resize(2);
  debug_message_prefix_[0] = '#';
  debug_message_prefix_[1] = ' ';
}

RC PlainCommunicator::read_event(SessionEvent *&event)
{
  RC rc = RC::SUCCESS;

  event = nullptr;

  int data_len = 0;
  int read_len = 0;

  const int    max_packet_size = 8192;
  vector<char> buf(max_packet_size);

  // 持续接收消息，直到遇到'\0'。将'\0'遇到的后续数据直接丢弃没有处理，因为目前仅支持一收一发的模式
  while (true) {
    read_len = ::read(fd_, buf.data() + data_len, max_packet_size - data_len);
    if (read_len < 0) {
      if (errno == EAGAIN) {
        continue;
      }
      break;
    }
    if (read_len == 0) {
      break;
    }

    if (read_len + data_len > max_packet_size) {
      data_len += read_len;
      break;
    }

    bool msg_end = false;
    for (int i = 0; i < read_len; i++) {
      if (buf[data_len + i] == 0) {
        data_len += i + 1;
        msg_end = true;
        break;
      }
    }

    if (msg_end) {
      break;
    }

    data_len += read_len;
  }

  if (data_len > max_packet_size) {
    LOG_WARN("The length of sql exceeds the limitation %d", max_packet_size);
    return RC::IOERR_TOO_LONG;
  }
  if (read_len == 0) {
    LOG_INFO("The peer has been closed %s", addr());
    return RC::IOERR_CLOSE;
  } else if (read_len < 0) {
    LOG_ERROR("Failed to read socket of %s, %s", addr(), strerror(errno));
    return RC::IOERR_READ;
  }

  LOG_INFO("receive command(size=%d): %s", data_len, buf.data());
  event = new SessionEvent(this);
  event->set_query(string(buf.data()));
  return rc;
}

RC PlainCommunicator::write_state(SessionEvent *event, bool &need_disconnect)
{
  SqlResult    *sql_result   = event->sql_result();
  const int     buf_size     = 2048;
  char         *buf          = new char[buf_size];
  const string &state_string = sql_result->state_string();
  if (state_string.empty()) {
    const char *result = RC::SUCCESS == sql_result->return_code() ? "SUCCESS" : "FAILURE";
    snprintf(buf, buf_size, "%s\n", result);
  } else {
    snprintf(buf, buf_size, "%s > %s\n", strrc(sql_result->return_code()), state_string.c_str());
  }

  RC rc = writer_->writen(buf, strlen(buf));
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to send data to client. err=%s", strerror(errno));
    need_disconnect = true;
    delete[] buf;
    return RC::IOERR_WRITE;
  }

  need_disconnect = false;
  delete[] buf;

  return RC::SUCCESS;
}

RC PlainCommunicator::write_debug(SessionEvent *request, bool &need_disconnect)
{
  if (!session_->sql_debug_on()) {
    return RC::SUCCESS;
  }

  SqlDebug &sql_debug = request->sql_debug();

  const list<string> &debug_infos = sql_debug.get_debug_infos();
  for (auto &debug_info : debug_infos) {
    RC rc = writer_->writen(debug_message_prefix_.data(), debug_message_prefix_.size());
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to send data to client. err=%s", strerror(errno));
      need_disconnect = true;
      return RC::IOERR_WRITE;
    }

    rc = writer_->writen(debug_info.data(), debug_info.size());
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to send data to client. err=%s", strerror(errno));
      need_disconnect = true;
      return RC::IOERR_WRITE;
    }

    char newline = '\n';

    rc = writer_->writen(&newline, 1);
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to send new line to client. err=%s", strerror(errno));
      need_disconnect = true;
      return RC::IOERR_WRITE;
    }
  }

  need_disconnect = false;
  return RC::SUCCESS;
}

RC PlainCommunicator::write_function_value(const SQLStageEvent *sql_event, bool &need_disconnect)
{
  // bool need_disconnect = false;
  if (sql_event->sql_node()->flag != SCF_SELECT) {
    LOG_ERROR("Function part: Wrong statement call. statement_flag=%d", sql_event->sql_node()->flag);
    return RC::INVALID_ARGUMENT; // 理论不可能出现这种情况
  }
  int cell_num = sql_event->sql_node()->selection.attributes.size();
  for (int i = 0; i < cell_num; i++) {
    auto &attr = sql_event->sql_node()->selection.attributes[cell_num - i - 1];
    // assemble the alias_name and delimiter in the first line and send it to the client
    if (attr.alias_name != "") {
      RC rc = writer_->writen(attr.alias_name.c_str(), strlen(attr.alias_name.c_str()));
      if (OB_FAIL(rc)) {
        LOG_WARN("failed to send data to client. err=%s", strerror(errno));
        return rc;
      }
    }
    if (i != cell_num - 1) {
      RC rc = writer_->writen(" | ", 3);
      if (OB_FAIL(rc)) {
        LOG_WARN("failed to send data to client. err=%s", strerror(errno));
        return rc;
      }
    }
  }

  if (cell_num > 0) {
    char newline = '\n';

    RC rc = writer_->writen(&newline, 1);
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to send data to client. err=%s", strerror(errno));
      return rc;
    }
  }

  // send the function value to the client
  for (int i = 0; i < cell_num; i++) {
    auto &attr = sql_event->sql_node()->selection.attributes[cell_num - i - 1];
    if (attr.alias_name != "") {
      std::string value = attr.function_value;
      RC rc = writer_->writen(value.c_str(), strlen(value.c_str()));
      if (OB_FAIL(rc)) {
        LOG_WARN("failed to send data to client. err=%s", strerror(errno));
        return rc;
      }
    }
    if (i != cell_num - 1) {
      RC rc = writer_->writen(" | ", 3);
      if (OB_FAIL(rc)) {
        LOG_WARN("failed to send data to client. err=%s", strerror(errno));
        return rc;
      }
    }
  }

  if (cell_num > 0) {
    char newline = '\n';

    RC rc = writer_->writen(&newline, 1);
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to send data to client. err=%s", strerror(errno));
      return rc;
    }
  }
  if (!need_disconnect) {
    RC rc = writer_->writen(send_message_delimiter_.data(), send_message_delimiter_.size());
    if (OB_FAIL(rc)) {
      LOG_ERROR("Failed to send data back to client. ret=%s, error=%s", strrc(rc), strerror(errno));
      need_disconnect = true;
      return rc;
    }
  }
  writer_->flush();
  return RC::SUCCESS;
}

RC PlainCommunicator::write_aggregate_value(SqlResult *sql_result, bool &need_disconnect) {
  // aggregation func: 需要统计的数据如下
  RC rc = RC::SUCCESS;
  int count = 0;
  vector <std::string> collum_value;

  Tuple *tuple = nullptr;
  rc = sql_result->next_tuple(tuple);
  while (RC::SUCCESS == rc) {
    assert(tuple != nullptr);
    int cell_num = tuple->cell_num();
    // aggregation func: 需要统计的数据
    vector<pair<AggregateType, std::string>> cell_value;
    vector<AttrType> cell_type;

    for (int i = 0; i < cell_num; i++) {
      Value value;
      rc = tuple->cell_at(i, value);
      if (rc != RC::SUCCESS) {
        sql_result->close();
        return rc;
      }
      // min(CHARS) / max(CHARS) 
      if (value.attr_type() == AttrType::CHARS) {
        assert(value.aggregate_type_ == AggregateType::MIN || value.aggregate_type_ == AggregateType::MAX);
      }
      cell_value.push_back(std::make_pair(value.aggregate_type_, value.get_string()));
      cell_type.push_back(value.attr_type());
    }
    rc = sql_result->next_tuple(tuple);
    count++;
    aggregation_compute(count, cell_value, collum_value, cell_type);
    if (rc != RC::SUCCESS) {
      set_avg_value(count, cell_value, collum_value);
    }
  }

  RC rc1 = aggregation_output(collum_value, writer_, sql_result);
  if (OB_FAIL(rc1)) {
    LOG_WARN("failed to send data to client. err=%s", strerror(errno));
    return rc1;
  }

  char newline = '\n';
  writer_->writen(&newline, 1);
  
  if (rc == RC::RECORD_EOF) {
    rc = RC::SUCCESS;
  }
  need_disconnect = false;
  RC rc_close = sql_result->close();
  if (OB_SUCC(rc)) {
    rc = rc_close;
  }
  return rc;
}

RC PlainCommunicator::write_result(SessionEvent *event, bool &need_disconnect) // Return SUCCESS / FAILURE 
{
  RC rc = write_result_internal(event, need_disconnect);
  if (!need_disconnect) {
    RC rc1 = write_debug(event, need_disconnect);
    if (OB_FAIL(rc1)) {
      LOG_WARN("failed to send debug info to client. rc=%s, err=%s", strrc(rc), strerror(errno));
    }
  }
  if (!need_disconnect) {
    rc = writer_->writen(send_message_delimiter_.data(), send_message_delimiter_.size());
    if (OB_FAIL(rc)) {
      LOG_ERROR("Failed to send data back to client. ret=%s, error=%s", strrc(rc), strerror(errno));
      need_disconnect = true;
      return rc;
    }
  }
  writer_->flush();  // TODO handle error
  return rc;
}

RC PlainCommunicator::write_result_internal(SessionEvent *event, bool &need_disconnect)
{
  RC rc = RC::SUCCESS;

  need_disconnect = true;

  SqlResult *sql_result = event->sql_result();

  if (RC::SUCCESS != sql_result->return_code() || !sql_result->has_operator()) {
    return write_state(event, need_disconnect);
  }

  rc = sql_result->open();
  if (OB_FAIL(rc)) {
    sql_result->close();
    sql_result->set_return_code(rc);
    return write_state(event, need_disconnect);
  }

  const TupleSchema &schema   = sql_result->tuple_schema();
  const int          cell_num = schema.cell_num();
  int                flag_for_aggr_func = 0;

  for (int i = 0; i < cell_num; i++) {
    const TupleCellSpec &spec  = schema.cell_at(i);
    const char          *alias = spec.alias();

    if (spec.aggregate_type_ != AggregateType::NONE) {
      flag_for_aggr_func = 1;
    }

    if (nullptr != alias || alias[0] != 0) {
      if (0 != i) {
        const char *delim = " | ";

        rc = writer_->writen(delim, strlen(delim));
        if (OB_FAIL(rc)) {
          LOG_WARN("failed to send data to client. err=%s", strerror(errno));
          return rc;
        }
      }

      int len = strlen(alias);

      rc = writer_->writen(alias, len);
      if (OB_FAIL(rc)) {
        LOG_WARN("failed to send data to client. err=%s", strerror(errno));
        sql_result->close();
        return rc;
      }
    }
  }

  if (cell_num > 0) {
    char newline = '\n';

    rc = writer_->writen(&newline, 1);
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to send data to client. err=%s", strerror(errno));
      sql_result->close();
      return rc;
    }
  }


  if (flag_for_aggr_func == 1) {
    return write_aggregate_value(sql_result, need_disconnect);
  }

  Tuple *tuple = nullptr;
  while (RC::SUCCESS == (rc = sql_result->next_tuple(tuple))) {
    assert(tuple != nullptr);
    int cell_num = tuple->cell_num();
    for (int i = 0; i < cell_num; i++) {
      if (i != 0) {
        const char *delim = " | ";

        rc = writer_->writen(delim, strlen(delim));
        if (OB_FAIL(rc)) {
          LOG_WARN("failed to send data to client. err=%s", strerror(errno));
          sql_result->close();
          return rc;
        }
      }

      Value value;
      rc = tuple->cell_at(i, value);
      if (rc != RC::SUCCESS) {
        sql_result->close();
        return rc;
      }

      string cell_str = value.to_string();
      rc = writer_->writen(cell_str.data(), cell_str.size());
      if (OB_FAIL(rc)) {
        LOG_WARN("failed to send data to client. err=%s", strerror(errno));
        sql_result->close();
        return rc;
      }
    }
    char newline = '\n';

    rc = writer_->writen(&newline, 1);
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to send data to client. err=%s", strerror(errno));
      sql_result->close();
      return rc;
    }
  }

  if (rc == RC::RECORD_EOF) {
    rc = RC::SUCCESS;
  }

  if (cell_num == 0) {
    // 除了select之外，其它的消息通常不会通过operator来返回结果，表头和行数据都是空的
    // 这里针对这种情况做特殊处理，当表头和行数据都是空的时候，就返回处理的结果
    // 可能是insert/delete等操作，不直接返回给客户端数据，这里把处理结果返回给客户端
    RC rc_close = sql_result->close();
    if (rc == RC::SUCCESS) {
      rc = rc_close;
    }
    sql_result->set_return_code(rc);
    return write_state(event, need_disconnect);
  } else {
    need_disconnect = false;
  }

  RC rc_close = sql_result->close();
  if (OB_SUCC(rc)) {
    rc = rc_close;
  }

  return rc;
}
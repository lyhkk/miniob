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
// Created by WangYunlai on 2023/06/28.
//

#include "sql/parser/value.h"
#include "common/lang/comparator.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include <iostream>
#include <sstream>
#include <regex>
#include <cmath>

const char *ATTR_TYPE_NAME[] = {"undefined", "chars", "ints", "dates", "floats","nulls", "booleans"};

const char *attr_type_to_string(AttrType type)
{
  if (type >= UNDEFINED && type <= NULLS) {
    return ATTR_TYPE_NAME[type];
  }
  return "unknown";
}
AttrType attr_type_from_string(const char *s)
{
  for (unsigned int i = 0; i < sizeof(ATTR_TYPE_NAME) / sizeof(ATTR_TYPE_NAME[0]); i++) {
    if (0 == strcmp(ATTR_TYPE_NAME[i], s)) {
      return (AttrType)i;
    }
  }
  return UNDEFINED;
}

Value::Value(int val) { set_int(val); }

Value::Value(float val) { set_float(val); }

Value::Value(bool val) { set_boolean(val); }

Value::Value(const char *s, int len /*= 0*/)
{
  int        y, m, d;
  char      *p = (char *)s;
  std::regex pattern("\\d+-\\d+-\\d+");
  if (std::regex_match(p, pattern)) {
    sscanf(p, "%d-%d-%d", &y, &m, &d);
    if (!check_date(y, m, d)) {
      set_undefined();
      return;
    }
    set_date(10000 * y + 100 * m + d);
  } else {
    set_string(s, len);
  }
}

void Value::set_undefined()
{
  attr_type_            = UNDEFINED;
}

bool Value::check_date(int y, int m, int d)
{
  static int mon[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  bool       leap  = (y % 400 == 0 || (y % 100 && y % 4 == 0));
  return y > 0 && (m > 0) && (m <= 12) && (d > 0) && (d <= ((m == 2 && leap) ? 1 : 0) + mon[m]);
}

void Value::set_data(char *data, int length)
{
  switch (attr_type_) {
    case CHARS: {
      set_string(data, length);
    } break;
    case INTS: {
      num_value_.int_value_ = *(int *)data;
      length_               = length;
    } break;
    case DATES: {
      int ymd               = *(int *)data;
      num_value_.int_value_ = ymd;
      length_               = length;
    } break;
    case FLOATS: {
      num_value_.float_value_ = *(float *)data;
      length_                 = length;
    } break;
    case BOOLEANS: {
      num_value_.bool_value_ = *(int *)data != 0;
      length_                = length;
    } break;
    default: {
      LOG_WARN("unknown data type: %d", attr_type_);
    } break;
  }
}
void Value::set_int(int val)
{
  attr_type_            = INTS;
  num_value_.int_value_ = val;
  length_               = sizeof(val);
}

void Value::set_float(float val)
{
  attr_type_              = FLOATS;
  num_value_.float_value_ = val;
  length_                 = sizeof(val);
}
void Value::set_boolean(bool val)
{
  attr_type_             = BOOLEANS;
  num_value_.bool_value_ = val;
  length_                = sizeof(val);
}

int Value::undefined_value()
{
  if (attr_type_ == UNDEFINED) {
    return -(num_value_.int_value_) & -(int)(length_);
  }
  return 0;
}

void Value::set_string(const char *s, int len /*= 0*/)
{
  attr_type_ = CHARS;
  if (len > 0) {
    len = strnlen(s, len);
    str_value_.assign(s, len);
  } else {
    str_value_.assign(s);
  }
  length_ = str_value_.length();
}

void Value::set_date(int val)
{
  attr_type_            = DATES;
  num_value_.int_value_ = val;
  length_               = sizeof(val);
}

void Value::set_value(const Value &value)
{
  switch (value.attr_type_) {
    case INTS: {
      set_int(value.get_int());
    } break;
    case FLOATS: {
      set_float(value.get_float());
    } break;
    case CHARS: {
      set_string(value.get_string().c_str());
    } break;
    case DATES: {
      set_date(value.get_int());
    } break;
    case NULLS: {
      set_null();
    } break;
    case BOOLEANS: {
      set_boolean(value.get_boolean());
    } break;
    case UNDEFINED: {
      ASSERT(false, "got an invalid value type");
    } break;
  }
}

const char *Value::data() const
{
  switch (attr_type_) {
    case CHARS: {
      return str_value_.c_str();
    } break;
    default: {
      return (const char *)&num_value_;
    } break;
  }
}

std::string Value::to_string() const
{
  std::stringstream os;
  switch (attr_type_) {
    case INTS: {
      os << num_value_.int_value_;
    } break;
    case FLOATS: {
      os << common::double_to_str(num_value_.float_value_);
    } break;
    case DATES: {
      int y = num_value_.int_value_ / 10000;
      int m = (num_value_.int_value_ % 10000) / 100;
      int d = num_value_.int_value_ % 100;
      if (m > 0 && m < 10)
        os << y << "-0" << m << "-";
      else
        os << y << "-" << m << "-";
      if (d > 0 && d < 10)
        os << "0" << d;
      else
        os << d;
    } break;
    case NULLS: {
      os << "NULL";
    } break;
    case BOOLEANS: {
      os << num_value_.bool_value_;
    } break;
    case CHARS: {
      os << str_value_;
    } break;
    default: {
      LOG_WARN("unsupported attr type: %d", attr_type_);
    } break;
  }
  return os.str();
}

int Value::like_type_compare(const Value &other) const
{
  if (this->attr_type_ == other.attr_type_) {
    switch (this->attr_type_) {
      case CHARS: {
        return common::like_compare_string((void *)this->str_value_.c_str(),
            this->str_value_.length(),
            (void *)other.str_value_.c_str(),
            other.str_value_.length());
      } break;
      default: {
        LOG_WARN("unsupported type: %d", this->attr_type_);
      }
    }
  } else {
    LOG_WARN("not supported");
  }
  return -1;  // TODO return rc?
}

/*
 * @brief compare two values
 * @param other the other value to compare
 * @return 0 if equal, >0 if this > other, <0 if this < other
 */
int Value::compare(const Value &other) const
{
  if(this->is_null() || other.is_null())
  {
    if(this->is_null() && other.is_null() )
    {
      return 0;
    }
    else
    {
      return -1;
    }
  }
  if (this->attr_type_ == other.attr_type_) {
    switch (this->attr_type_) {
      case INTS: {
        return common::compare_int((void *)&this->num_value_.int_value_, (void *)&other.num_value_.int_value_);
      } break;
      case FLOATS: {
        return common::compare_float((void *)&this->num_value_.float_value_, (void *)&other.num_value_.float_value_);
      } break;
      case DATES: {
        return common::compare_int((void *)&this->num_value_.int_value_, (void *)&other.num_value_.int_value_);
      } break;
      case CHARS: {
        return common::compare_string((void *)this->str_value_.c_str(),
            this->str_value_.length(),
            (void *)other.str_value_.c_str(),
            other.str_value_.length());
      } break;
      case BOOLEANS: {
        return common::compare_int((void *)&this->num_value_.bool_value_, (void *)&other.num_value_.bool_value_);
      }
      default: {
        LOG_WARN("unsupported type: %d", this->attr_type_);
      }
    }
  } else if (this->attr_type_ == INTS && other.attr_type_ == FLOATS) {
    float this_data = this->num_value_.int_value_;
    return common::compare_float((void *)&this_data, (void *)&other.num_value_.float_value_);
  } else if (this->attr_type_ == FLOATS && other.attr_type_ == INTS) {
    float other_data = other.num_value_.int_value_;
    return common::compare_float((void *)&this->num_value_.float_value_, (void *)&other_data);
  } else if (this->attr_type_ == FLOATS && other.attr_type_ == CHARS) {
    float other_data = other.get_float();
    return common::compare_float((void *)&this->num_value_.float_value_, (void *)&other_data);
  } else if (this->attr_type_ == CHARS && other.attr_type_ == FLOATS) {
    float this_data = this->get_float();
    return common::compare_float((void *)&this_data, (void *)&other.num_value_.float_value_);
  }
  LOG_WARN("not supported");
  return -1;  // TODO return rc?
}

RC Value::typecast(AttrType target_type)
  {
    if(target_type == attr_type_)
    {
      return RC::SUCCESS;
    }
    if(target_type == DATES || attr_type_ == NULLS)
    {
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }
    switch (target_type)
    {
      case INTS:
      {
        int tmp = get_int_round();
        set_int(tmp);
      }
        break;
      case FLOATS:
      {
        float tmp = get_float();
        set_float(tmp);
      }
        break;
      case CHARS:
      {
        std::string tmp = get_string();
        set_string(tmp.c_str());
      }
        break;
      default:
        break;
    }
    return RC::SUCCESS;
  }

int Value::get_int_round() const
{
  switch (attr_type_) {
    case CHARS: {
      try {
        return (int)(std::stol(str_value_));
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to number. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return 0;
      }
    }
    case INTS: {
      return num_value_.int_value_;
    }
    case FLOATS: {
      return (int)(num_value_.float_value_ + 0.5);
    }
    case DATES: {
      return num_value_.int_value_;
    }
    case BOOLEANS: {
      return (int)(num_value_.bool_value_);
    }
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return 0;
    }
  }
  return 0;
}

int Value::get_int() const
{
  switch (attr_type_) {
    case CHARS: {
      try {
        return (int)(std::stol(str_value_));
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to number. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return 0;
      }
    }
    case INTS: {
      return num_value_.int_value_;
    }
    case FLOATS: {
      return (int)(num_value_.float_value_);
    }
    case DATES: {
      return num_value_.int_value_;
    }
    case BOOLEANS: {
      return (int)(num_value_.bool_value_);
    }
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return 0;
    }
  }
  return 0;
}

float Value::get_float() const
{
  switch (attr_type_) {
    case CHARS: {
      try {
        return std::stof(str_value_);
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to float. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return 0.0;
      }
    } break;
    case INTS: {
      return float(num_value_.int_value_);
    } break;
    case FLOATS: {
      return num_value_.float_value_;
    } break;
    case DATES: {
      return float(num_value_.int_value_);
    } break;
    case BOOLEANS: {
      return float(num_value_.bool_value_);
    } break;
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return 0;
    }
  }
  return 0;
}

std::string Value::get_string() const { return this->to_string(); }

bool Value::get_boolean() const
{
  switch (attr_type_) {
    case CHARS: {
      try {
        float val = std::stof(str_value_);
        if (val >= EPSILON || val <= -EPSILON) {
          return true;
        }

        int int_val = std::stol(str_value_);
        if (int_val != 0) {
          return true;
        }

        return !str_value_.empty();
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to float or integer. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return !str_value_.empty();
      }
    } break;
    case INTS: {
      return num_value_.int_value_ != 0;
    } break;
    case FLOATS: {
      float val = num_value_.float_value_;
      return val >= EPSILON || val <= -EPSILON;
    } break;
    case DATES: {
      return num_value_.int_value_ != 0;
    } break;
    case BOOLEANS: {
      return num_value_.bool_value_;
    } break;
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return false;
    }
  }
  return false;
}

void Value::add(const Value &other) {
  if (attr_type_ == AttrType::INTS) {
    int int_value = num_value_.int_value_;
    if (other.attr_type() == AttrType::INTS) {
      num_value_.int_value_ = int_value + other.get_int();
    }
    else if (other.attr_type() == AttrType::FLOATS) {
      set_float(int_value + other.get_float());
    }
  }
  else if (attr_type_ == AttrType::FLOATS) {
    float float_value = num_value_.float_value_;
    if (other.attr_type() == AttrType::INTS) {
      set_float(float_value + other.get_int());
    }
    else if (other.attr_type() == AttrType::FLOATS) {
      set_float(float_value + other.get_float());
    }
  }
}

void Value::div(const Value &other) {
  if (attr_type_ == AttrType::INTS) {
    set_float((float)get_int() / other.get_int());
  }
  else if (attr_type_ == AttrType::FLOATS) {
    set_float(get_float() / other.get_int());
  }
}
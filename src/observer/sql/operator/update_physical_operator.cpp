//
// Created by Chen Jiuhe on 2024/4/9.
//

#include "common/log/log.h"
#include "sql/operator/update_physical_operator.h"
#include "sql/expr/tuple.h"
#include "storage/record/record.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"
#include "sql/stmt/delete_stmt.h"

RC UpdatePhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  std::unique_ptr<PhysicalOperator> &child = children_[0];
  RC rc = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }
  
  trx_ = trx;
  return RC::SUCCESS;
}

RC UpdatePhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    return RC::RECORD_EOF;
  }

  PhysicalOperator *child = children_[0].get();
  while (RC::SUCCESS == (rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    Record &record = row_tuple->record();
    std::vector<Value*> values;
    RC rc2 = RC::SUCCESS;
    if (RC::SUCCESS != (rc2 = extract_old_value(record, values))) {
      if (RC::RECORD_DUPLICATE_KEY == rc2) { 
        continue;
      }
      else { 
        return rc2; 
      }
    }
    rc = table_->update_record(record, fields_, values);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to update record: %s", strrc(rc));
      for (size_t i = old_records_.size() - 1; i >= 0; i--) {
        RC rc2 = RC::SUCCESS;
        Record updated_record;
        std::vector<Value*> old_row_values;
        for (size_t j = 0; j < old_values_[i].size(); j++) {
          old_row_values.emplace_back(&old_values_[i][j]);
        }
        if (RC::SUCCESS != (rc2 = table_->get_record(old_records_[i], updated_record))) {
          LOG_ERROR("Failed to get record when try to rollback, rc=%s", strrc(rc2));
        }
        else if (RC::SUCCESS != (rc2 = table_->update_record(updated_record, fields_, old_row_values))) {
          LOG_ERROR("Failed to rollback after update failed, rc=%s", strrc(rc2));
        }
      }
      return rc;
    }
  }
  return RC::RECORD_EOF;
}

RC UpdatePhysicalOperator::extract_old_value(Record &record, std::vector<Value*> &values)
{
  RC rc = RC::SUCCESS;
  int       field_offset   = -1;
  int       field_length   = -1;
  int       field_index    = -1;
  bool      same_data      = true; // 标识当前行数据更新后，是否与之前相同
  const int sys_field_num  = table_->table_meta().sys_field_num();
  const int user_field_num = table_->table_meta().field_num() - sys_field_num;
  EmptyTuple tp;
  std::vector<Value> old_value;
  Value raw_value;
  for (size_t c_idx = 0; c_idx < fields_.size(); c_idx++) {
    std::string &attr_name = fields_[c_idx];
    for (int i = 0; i < user_field_num; ++i) {
      const FieldMeta *field_meta = table_->table_meta().field(i + sys_field_num);
      const char      *field_name = field_meta->name();
      if (0 != strcmp(field_name, attr_name.c_str())) {
        continue;
      }
      std::unique_ptr<Expression>& expr = values_[c_idx];
      
      if (expr->type() == ExprType::SUBQUERY) {
        SubQueryExpr* subquery_expr = static_cast<SubQueryExpr*>(expr.get());
        rc = subquery_expr->open(nullptr);
        if (RC::SUCCESS != rc) {
          return rc;
        }
        rc = subquery_expr->get_value(tp, raw_value);
        if (RC::RECORD_EOF == rc) {
          //子查询为空集时设置null
          raw_value.set_null();
          rc = RC::SUCCESS;
        }
        else if (RC::SUCCESS != rc) {
          return rc;
        }
        else if (subquery_expr->has_more_row(tp)) {
          //子查询为多行，直接跳过后续检查
          invalid_ = true;
          break;
        }
        subquery_expr->close();
        if (invalid_) {
          return RC::INVALID_ARGUMENT;
        }
      }
      else {
        if (rc = expr->get_value(tp, raw_value); RC::SUCCESS != rc) {
          return rc;
        }
      }
      //拿到raw_value
      AttrType attr_type  = field_meta->type();
      AttrType value_type = raw_value.attr_type();
      if (raw_value.is_null() && field_meta->nullable()) {
        // empty
      }
      else if (attr_type != value_type) {
        if (const_cast<Value&>(raw_value).typecast(field_meta->type()) != RC::SUCCESS) {
          LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
            table_->name(),
            field_meta->name(),
            attr_type,
            value_type);
          invalid_ = true;
        }
      }
      field_offset = field_meta->offset();
      field_length = field_meta->len();
      field_index = i + sys_field_num;
      old_value.emplace_back(attr_type, record.data() + field_offset, field_length);
      Value* valueptr = new Value(raw_value);
      values.emplace_back(valueptr);
      break;
    }
    if (field_length < 0 || field_offset < 0) {
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }
    // 判断新值与旧值是否相等
    const FieldMeta* null_field = table_->table_meta().null_field();
    common::Bitmap old_null_bitmap(record.data() + null_field->offset(), table_->table_meta().field_num());
    
    if (same_data) {
      if (raw_value.is_null() && old_null_bitmap.get_bit(field_index)) {
        // both null
      }
      else if (raw_value.is_null() || old_null_bitmap.get_bit(field_index)) {
        same_data = false;
      }
      else {
        char *new_value = new char[field_length + 1];
        if(raw_value.length() == field_length) {
          memcpy(new_value, raw_value.data(), raw_value.length());
        }
        else {
          memcpy(new_value, raw_value.data(), raw_value.length());
          memset(new_value + raw_value.length(), '\0', field_length - raw_value.length());
        }
        if (0 == memcmp(record.data()+field_offset, new_value, field_length)) {
          //same data
        }
        else {
          same_data = false;
        }
      }
    }
  }
  if (same_data) {
    LOG_WARN("update old value equals new value. skip this record");
    return RC::RECORD_DUPLICATE_KEY;
  }
  old_values_.emplace_back(std::move(old_value));
  old_records_.emplace_back(record.rid());
  return rc;
}

RC UpdatePhysicalOperator::close()
{
  if (!children_.empty()) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}
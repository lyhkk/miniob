//
// Created by Chen Jiuhe on 2024/4/9.
//

#pragma once

#include "sql/operator/physical_operator.h"
#include "sql/parser/parse.h"
#include "sql/parser/value.h"
#include <vector>

class Trx;
class UpdateStmt;

/**
 * @brief 更新物理算子
 * @ingroup PhysicalOperator
 */
class UpdatePhysicalOperator : public PhysicalOperator
{
public:
  UpdatePhysicalOperator(Table *table, std::vector<std::unique_ptr<Expression>> &&values, std::vector<FieldMeta> &fields) 
    : table_(table), values_(std::move(values))
  {
    for (FieldMeta &field : fields) {
      fields_.emplace_back(field.name());
    }
  }

  virtual ~UpdatePhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::UPDATE; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  RC extract_old_value(Record &record, std::vector<Value*> &values);
  Tuple *current_tuple() override { return nullptr; }

private:
  Table *table_ = nullptr;
  Trx *trx_ = nullptr;
  std::vector<std::unique_ptr<Expression>> values_;
  std::vector<std::string> fields_;
  std::vector<RID> old_records_;
  std::vector<std::vector<Value>> old_values_;
  bool invalid_ = false; //用于回滚
};
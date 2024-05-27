//
// Created by Chen Jiuhe on 2024/4/9.
//

#pragma once

#include "sql/operator/physical_operator.h"
#include "sql/parser/parse.h"
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
  UpdatePhysicalOperator(Table *table, std::vector<Value*> &values, std::vector<FieldMeta> &fields) 
    : table_(table), values_(values)
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

  RC extract_old_value(Record &record);
  Tuple *current_tuple() override { return nullptr; }

private:
  Table *table_ = nullptr;
  Trx *trx_ = nullptr;
  std::vector<Value*> values_;
  std::vector<std::string> fields_;
  std::vector<RID> old_records_;
  std::vector<std::vector<Value>> old_values_;
};
#pragma once

#include <memory>
#include <string_view>

#include "simpleml/operations/internal/operation.h"
#include "simpleml/variable.h"

namespace SimpleML {
namespace Operations {
VariableSPtr Add(const VariableSPtr& lhs, const VariableSPtr& rhs,
                 std::string_view name = nullptr);
VariableSPtr Mul(const VariableSPtr& lhs, const VariableSPtr& rhs,
                 std::string_view name = nullptr);
VariableSPtr Transpose(const VariableSPtr& value,
                       std::string_view name = nullptr);
VariableSPtr Identity(const VariableSPtr& value,
                      std::string_view name = nullptr);
}  // namespace Operations
}  // namespace SimpleML

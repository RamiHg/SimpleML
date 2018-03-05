#pragma once

#include <memory>
#include <string_view>

#include "simpleml/operations/internal/operation.h"
#include "simpleml/variable.h"

namespace SimpleML {
namespace Operations {
VariableSPtr Add(const VariableSPtr& lhs, const VariableSPtr& rhs,
                 std::string_view name = std::string_view());
VariableSPtr Mul(const VariableSPtr& lhs, const VariableSPtr& rhs,
                 std::string_view name = std::string_view());
VariableSPtr Transpose(const VariableSPtr& value,
                       std::string_view name = std::string_view());
VariableSPtr Identity(const VariableSPtr& value,
                      std::string_view name = std::string_view());
VariableSPtr Variable(const Tensor& value,
                      std::string_view name = std::string_view());
VariableSPtr Constant(const Tensor& value,
                      std::string_view name = std::string_view());
}  // namespace Operations
}  // namespace SimpleML

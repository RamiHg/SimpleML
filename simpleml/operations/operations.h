#pragma once

#include <memory>

#include "simpleml/operations/internal/operation.h"
#include "simpleml/variable.h"

namespace SimpleML {
namespace Operations {
VariableSPtr Add(const VariableSPtr& lhs, const VariableSPtr& rhs);
VariableSPtr Mul(const VariableSPtr& lhs, const VariableSPtr& rhs);
VariableSPtr Transpose(const VariableSPtr& value);
VariableSPtr Identity(const VariableSPtr& value);
}  // namespace Operations
}  // namespace SimpleML

#pragma once

#include <memory>

#include "simpleml/operations/internal/operation.h"

namespace SimpleML {
namespace Operations {
OperationPtr Add(const OperationPtr& lhs, const OperationPtr& rhs);
OperationPtr Mul(const OperationPtr& lhs, const OperationPtr& rhs);
OperationPtr Transpose(const OperationPtr& value);
}  // namespace Operations
}  // namespace SimpleML

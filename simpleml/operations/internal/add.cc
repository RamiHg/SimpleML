#include "simpleml/operations/internal/add.h"

namespace SimpleML {
Tensor AddOperation::Compute() const {
  const auto& lhs = GetInputValue(0);
  const auto& rhs = GetInputValue(1);
  return lhs + rhs;
}
}  // namespace SimpleML
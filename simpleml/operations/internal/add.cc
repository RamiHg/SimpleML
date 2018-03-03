#include "simpleml/operations/internal/add.h"

#include <cassert>

namespace SimpleML {
Tensor AddOperation::Compute() const {
  const auto& lhs = GetInputValue(0);
  const auto& rhs = GetInputValue(1);
  return lhs + rhs;
}

OperationPtr AddOperation::GetBackProp(const OperationPtr& input,
                                       const OperationPtr& gradient) const {
  assert(input.get() == inputs_[0].get() || input.get() == inputs_[1].get());
  return gradient;
}
}  // namespace SimpleML
#include "simpleml/operations/internal/add.h"

#include <cassert>

namespace SimpleML {
Tensor AddOperation::Compute() const {
  const auto& lhs = GetInputValue(0);
  const auto& rhs = GetInputValue(1);
  return lhs + rhs;
}

std::unique_ptr<Operation> AddOperation::GetBackProp(
    const std::shared_ptr<Variable>& input,
    const std::shared_ptr<Variable>& gradient) const {
  assert(input.get() == inputs_[0].get() || input.get() == inputs_[1].get());
  return gradient;
}
}  // namespace SimpleML
#include "simpleml/operations/internal/add.h"

namespace SimpleML {
Tensor AddOperation::Compute() const {
  const auto& lhs = GetInputValue(0);
  const auto& rhs = GetInputValue(1);
  return lhs + rhs;
}

std::unique_ptr<Operation> AddOperation::GetBackProp(
    Graph&, const VariableNode* input, const VariableNode* gradient) const {
  assert(input == inputs_[0] || input == inputs_[1]);
  return std::make_unique<IdentityOperation>(gradient);
}

}  // namespace SimpleML

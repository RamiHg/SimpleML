#include "simpleml/operations/internal/mul.h"

#include <cassert>

#include "simpleml/operations/operations.h"

namespace SimpleML {
Tensor MulOperation::Compute() const {
  const auto& lhs = GetInputValue(0);
  const auto& rhs = GetInputValue(1);
  return lhs + rhs;
}

std::unique_ptr<Operation> MulOperation::GetBackProp(
    const std::shared_ptr<VariableNode>& input,
    const std::shared_ptr<VariableNode>& gradient) const {
  assert(input == inputs_[0] || input == inputs_[1]);
  // AB
  if (input == inputs_[0]) {
    // d(AB) / dA * G = BGT
    return std::make_unique<MulOperation>(inputs_[1],
                                          Operations::Transpose(gradient));
  } else {
    // d(AB) / dA * G = ATG
    return std::make_unique<MulOperation>(Operations::Transpose(inputs_[0]),
                                          gradient);
  }
}
}  // namespace SimpleML
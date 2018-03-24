#include "simpleml/operations/internal/mul.h"

#include <iostream>

#include "xtensor/xeval.hpp"

namespace SimpleML {
Tensor MulOperation::Compute() const {
  const Tensor& lhs = GetInputValue(0);
  const Tensor& rhs = GetInputValue(1);
  return lhs * rhs;
}

std::unique_ptr<Operation> MulOperation::GetBackProp(
    Graph& graph, const VariableNode* input,
    const VariableNode* gradient) const {
  assert(input == inputs_[0] || input == inputs_[1]);
  // AB
  auto other_input = input == inputs_[0] ? inputs_[1] : inputs_[0];
  return std::make_unique<MulOperation>(other_input, gradient);
}

}  // namespace SimpleML

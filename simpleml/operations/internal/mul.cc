#include "simpleml/operations/internal/mul.h"

#include <iostream>

namespace SimpleML {
Tensor MulOperation::Compute() const {
  const auto lhs = GetInputValue(0);
  const auto rhs = GetInputValue(1);

  auto lhs_shape = lhs.shape();
  auto rhs_shape = rhs.shape();

  // For some reason there's a bug in xtensor where the
  // larger shape has to be on the left hand side
  // for broadcasting to be correct.
  
  std::cout << "First: ";
  for (auto item : lhs_shape)
    std::cout << item << " ";
  std::cout << "\nSecond: ";
  for (auto item : rhs_shape)
    std::cout << item << " ";
  std::cout << std::endl;

  std::cout << "LHS: \n";
  for (auto item : lhs) {
    std::cout << item << " ";
  }
  std::cout << "\nRHS: \n";
  for (auto item : rhs) {
    std::cout << item << " ";
  }
  std::cout << std::endl;
  return lhs * rhs;
}

std::unique_ptr<Operation> MulOperation::GetBackProp(
    Graph& graph, const VariableNode* input,
    const VariableNode* gradient) const {
  assert(input == inputs_[0] || input == inputs_[1]);
  // AB
  auto other_input = input == inputs_[0] ? inputs_[1] : inputs_[0];
  return std::make_unique<MulOperation>(
    other_input,
    gradient);
}

}  // namespace SimpleML

#include "simpleml/operations/internal/mul.h"

namespace SimpleML {
Tensor MulOperation::Compute() const {
  const auto& lhs = GetInputValue(0);
  const auto& rhs = GetInputValue(1);
  return lhs * rhs;
}

std::unique_ptr<Operation> MulOperation::GetBackProp(
    Graph& graph, const VariableNode* input,
    const VariableNode* gradient) const {
  assert(input == inputs_[0] || input == inputs_[1]);
  // AB
  assert(false);  // figure out how to do this.
  if (input == inputs_[0]) {
    // d(AB) / dA * G = BGT
    return std::make_unique<MulOperation>(
        inputs_[1],
        Operations::Transpose(
            gradient, std::string("gradient_wrt_") + input->GetName(), graph));
  } else {
    // d(AB) / dA * G = ATG
    return std::make_unique<MulOperation>(
        Operations::Transpose(inputs_[0],
                              std::string("gradient_") + gradient->GetName() +
                                  std::string("_wrt_") + input->GetName(),
                              graph),
        gradient);
  }
}

}  // namespace SimpleML

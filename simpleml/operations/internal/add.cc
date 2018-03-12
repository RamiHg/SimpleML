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

Shape AddOperation::GetResultShape() const {
  // Add is pretty flexible with broadcasting, therefore
  // we're just as flexible with the shaping. Simply get the
  // max across all dimensions.
  Shape shape_lhs = inputs_[0]->GetOperation().GetResultShape();
  Shape shape_rhs = inputs_[1]->GetOperation().GetResultShape();
  
  size_t final_size = std::max(shape_lhs.size(), shape_rhs.size());
  
  Shape result;
  result.resize(final_size);
  for (size_t i = 0; i < result.size(); ++i) {
    int lhs = i < shape_lhs.size()? shape_lhs[i] : -1;
    int rhs = i < shape_rhs.size()? shape_rhs[i] : -1;
    result[i] = std::max(lhs, rhs);
  }
  
  return result;
}
}  // namespace SimpleML

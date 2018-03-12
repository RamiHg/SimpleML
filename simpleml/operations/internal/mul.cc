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

Shape MulOperation::GetResultShape() const {
  // We can sometimes deduct the shape of the resultant matrix.
  // [n * m] * [m * p] = [n * p]
  Shape lhs_shape = inputs_[0]->GetOperation().GetResultShape();
  Shape rhs_shape = inputs_[1]->GetOperation().GetResultShape();

  auto get_shape_tuple = [](const Shape& shape) -> auto {
    if (shape.empty())
      return std::make_tuple(-1, -1);
    else {
      // TODO: Support tensor contraction.
      assert(shape.size() <= 2);
      if (shape.size() == 1) {
        return std::make_tuple(1, shape[0]);
      } else {
        return std::make_tuple(shape[0], shape[1]);
      }
    }
  };
  
  //assert(std::get<1>(get_shape_tuple(lhs_shape)) == std::get<0>(get_shape_tuple(rhs_shape)));

  auto num_rows = std::get<0>(get_shape_tuple(lhs_shape));
  int num_cols = std::get<1>(get_shape_tuple(rhs_shape));

  if (num_cols == 1) {
    return {num_rows};
  } else
    return {num_rows, num_cols};
}
}  // namespace SimpleML

#include "simpleml/operations/internal/operation.h"

// TODO: Remove me
#include "simpleml/variable.h"

namespace SimpleML {
Operation::Operation(const VariableList& inputs) : inputs_(inputs) {}

const Tensor& Operation::GetInputValue(size_t child_index) const {
  return inputs_.at(child_index)->GetValue();
}

Shape Operation::GetResultShape() const {
  if (inputs_.size() == 1) {
    return inputs_[0]->GetOperation().GetResultShape();
  }

  std::vector<Shape> input_shapes;
  input_shapes.reserve(inputs_.size());
  for (const auto input : inputs_) {
    input_shapes.push_back(input->GetOperation().GetResultShape());
  }

  // Number of dimensions is set by the largest element.
  size_t final_size = 0;
  for (const auto& shape : input_shapes) {
    final_size = std::max(shape.size(), final_size);
  }

  Shape result;
  result.resize(final_size);
  for (size_t i = 0; i < result.size(); ++i) {
    // Each dimension is the largest dimension across all inputs, where
    // unknown shapes win.
    int max_size = 0;
    for (const auto& shape : input_shapes) {
      if (i < shape.size()) {
        assert(shape[i] != INT32_MAX);  // INT32_MAX reserved.
        const int size = shape[i] == -1 ? INT32_MAX : shape[i];
        max_size = std::max(max_size, size);
      } else {
        // This dimension will get broadcasted.
        max_size = std::max(max_size, -1);
      }
    }
    result[i] = max_size == INT32_MAX ? -1 : max_size;
  }

  return result;
}
}  // namespace SimpleML

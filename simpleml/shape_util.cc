#include "simpleml/shape_util.h"

#include <iostream>

namespace SimpleML {

bool CheckShapesMatch(const Tensor& tensor, const Shape& shape) {
  // An empty shape indicates completely dynamic.
  if (shape.empty()) return true;

  Shape tensor_shape = ShapeFromS(tensor.shape());
  if (tensor_shape.size() != shape.size()) {
    std::cout << "Number of dimensions in tensor (" << tensor_shape.size()
              << ") does not match expected (" << shape.size() << ")\n";
    return false;
  }

  for (size_t i_dim = 0; i_dim < shape.size(); ++i_dim) {
    // An expected shape dimension of -1 means it's dynamic.
    // In this case, they implicitly match.
    if (shape[i_dim] == -1) {
      continue;
    } else if (shape[i_dim] != tensor_shape[i_dim]) {
      std::cout << i_dim << "th dimension size does not match. Actual ("
                << tensor_shape[i_dim] << "). Expected (" << shape[i_dim]
                << ")\n";
      return false;
    }
  }
  return true;
}

}  // namespace SimpleML

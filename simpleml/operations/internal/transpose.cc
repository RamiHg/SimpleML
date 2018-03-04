#include "simpleml/operations/internal/transpose.h"

#include "xtensor/xstrided_view.hpp"

namespace SimpleML {
Tensor TransposeOperation::Compute() const {
  return xt::transpose(GetInputValue(0));
}
}  // namespace SimpleML
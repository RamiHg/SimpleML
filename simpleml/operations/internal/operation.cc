#include "simpleml/operations/internal/operation.h"

// tODO Remove me
#include "simpleml/variable.h"

namespace SimpleML {
Operation::Operation(const VariableList& inputs) : inputs_(inputs) {}

const Tensor& Operation::GetInputValue(size_t child_index) const {
  return inputs_.at(child_index)->GetValue();
}
}  // namespace SimpleML
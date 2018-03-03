#pragma once

#include <memory>

#include "simpleml/operations/internal/operation.h"

namespace SimpleML {
class AddOperation : public Operation {
 public:
  AddOperation(const InputVector& inputs) : Operation(inputs) {}

  virtual Tensor Compute() const override;
  OperationPtr GetBackProp(const OperationPtr& input,
                           const OperationPtr& gradient) const override;
};
}  // namespace SimpleML
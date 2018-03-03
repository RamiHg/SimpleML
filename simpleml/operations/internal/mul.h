#pragma once

#include <memory>

#include "simpleml/operations/internal/operation.h"

namespace SimpleML {
class MulOperation : public Operation {
 public:
  MulOperation(const InputVector& inputs) : Operation(inputs) {}

  virtual Tensor Compute() const override;
  OperationPtr GetBackProp(const OperationPtr& input,
                           const OperationPtr& gradient) const override;
};
}  // namespace SimpleML
#pragma once

#include <cassert>
#include <memory>

#include "simpleml/operations/internal/operation.h"

namespace SimpleML {
class TransposeOperation : public Operation {
 public:
  TransposeOperation(const InputVector& inputs) : Operation(inputs) {
    assert(inputs.size() == 2);
  }

  virtual Tensor Compute() const override { return xt::transpose(value_); }
  OperationPtrGetBackProp(const OperationPtr& input,
                          const OperationPtr& gradient) const override {
    assert(false && "TODO: Implement backprop operation.");
  }
};
}  // namespace SimpleML
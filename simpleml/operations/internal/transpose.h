#pragma once

#include <cassert>
#include <memory>

#include "simpleml/operations/internal/operation.h"

namespace SimpleML {
class TransposeOperation : public Operation {
 public:
  TransposeOperation(const VariableList& inputs) : Operation(inputs) {
    assert(inputs.size() == 1);
  }

  virtual Tensor Compute() const override { return xt::transpose(value_); }
  virtual std::unique_ptr<Operation> GetBackProp(
      const std::shared_ptr<Variable>& input,
      const std::shared_ptr<Variable>& gradient) const override {
    assert(false && "TODO: Implement backprop operation.");
  }
};
}  // namespace SimpleML
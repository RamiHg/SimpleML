#pragma once

#include <cassert>
#include <memory>

#include "simpleml/operations/internal/operation.h"
#include "simpleml/variable.h"

namespace SimpleML {
class TransposeOperation : public Operation {
 public:
  TransposeOperation(const VariableSPtr& input) : Operation({input}) {}

  virtual Tensor Compute() const override;
  virtual std::unique_ptr<Operation> GetBackProp(
      const std::shared_ptr<VariableNode>& input,
      const std::shared_ptr<VariableNode>& gradient) const override {
    assert(false && "TODO: Implement backprop operation.");
  }
};
}  // namespace SimpleML
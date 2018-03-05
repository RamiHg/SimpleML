#pragma once

#include "simpleml/operations/internal/operation.h"
#include "simpleml/variable.h"

namespace SimpleML {
class VariableOperation : public Operation {
 public:
  VariableOperation(const VariableSPtr& input) : Operation({input}) {}

  virtual Tensor Compute() const override{return GetInputValue(0)};
  virtual std::unique_ptr<Operation> GetBackProp(
      const std::shared_ptr<VariableNode>& input,
      const std::shared_ptr<VariableNode>& gradient) const override {
    assert(false && "Figure out what to put here.");
    return nullptr;
  }

 private:
};
}  // namespace SimpleML
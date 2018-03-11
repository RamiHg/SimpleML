#pragma once

#include "simpleml/operations/internal/operation.h"
#include "simpleml/variable.h"

namespace SimpleML {
class ConstantOperation : public Operation {
 public:
  ConstantOperation(const Tensor& input) : Operation({}), value_(input) {}

  virtual Tensor Compute() const override { return value_; }
  virtual std::unique_ptr<Operation> GetBackProp(
    Graph&,
      const VariableNode* input, const VariableNode* gradient) const override {
    assert(false && "Figure out what to put here.");
    return nullptr;
  }

 private:
  const Tensor value_;
};
}  // namespace SimpleML

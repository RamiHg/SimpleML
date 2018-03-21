#pragma once

#include <cassert>
#include <memory>

#include "simpleml/operations/internal/operation.h"
#include "simpleml/variable.h"

namespace SimpleML {
class TransposeOperation : public Operation {
 public:
  TransposeOperation(const VariableNode* input) : Operation({input}) {}
  virtual const char* GetName() const override { return "Transpose"; }

  virtual Tensor Compute() const override {
    return xt::transpose(GetInputValue(0));
  }
  virtual std::unique_ptr<Operation> GetBackProp(
      Graph&, const VariableNode* input,
      const VariableNode* gradient) const override {
    assert(false && "TODO: Implement backprop operation.");
    return nullptr;
  }
};
}  // namespace SimpleML

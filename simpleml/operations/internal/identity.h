#pragma once

#include <cassert>
#include <memory>

#include "simpleml/operations/internal/operation.h"
#include "simpleml/variable.h"

namespace SimpleML {
class IdentityOperation : public Operation {
 public:
  IdentityOperation(const VariableNode* input) : Operation({input}) {}
  virtual const char* GetName() const override { return "Identity"; }

  virtual Tensor Compute() const override { return GetInputValue(0); }
  virtual std::unique_ptr<Operation> GetBackProp(
      Graph&, const VariableNode* input,
      const VariableNode* gradient) const override {
    assert(false);
    return nullptr;
  }
};
}  // namespace SimpleML

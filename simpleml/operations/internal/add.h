#pragma once

#include <memory>

#include "simpleml/operations/internal/identity.h"
#include "simpleml/operations/internal/operation.h"
#include "simpleml/variable.h"

namespace SimpleML {
class AddOperation : public Operation {
 public:
  AddOperation(const VariableNode* lhs, const VariableNode* rhs)
      : Operation({lhs, rhs}) {}

  virtual const char* GetName() const override { return "Add"; }

  virtual Tensor Compute() const override {
    const auto& lhs = GetInputValue(0);
    const auto& rhs = GetInputValue(1);
    return lhs + rhs;
  }
  virtual std::unique_ptr<Operation> GetBackProp(
      Graph&,
      const VariableNode* input, const VariableNode* gradient) const override {
    assert(input == inputs_[0] || input == inputs_[1]);
    return std::make_unique<IdentityOperation>(gradient);
  }
};
}  // namespace SimpleML

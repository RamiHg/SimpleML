#pragma once

#include <cassert>
#include <memory>

#include "simpleml/operations/internal/operation.h"
#include "simpleml/variable.h"

namespace SimpleML {
class GteOperation : public Operation {
 public:
  GteOperation(const VariableNode* lhs, const VariableNode* rhs)
      : Operation({lhs, rhs}) {}
  virtual const char* GetName() const override { return ">="; }

  virtual Tensor Compute() const override {
    return xt::cast<double>(GetInputValue(0) >= GetInputValue(1));
  }
};
}  // namespace SimpleML

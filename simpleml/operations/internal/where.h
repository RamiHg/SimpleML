#pragma once

#include <cassert>
#include <memory>

#include "simpleml/operations/internal/operation.h"
#include "simpleml/variable.h"

namespace SimpleML {
class WhereOperation : public Operation {
 public:
  WhereOperation(const VariableNode* cond, const VariableNode* a,
                 const VariableNode* b)
      : Operation({cond, a, b}) {}
  virtual const char* GetName() const override { return "Where"; }

  virtual Tensor Compute() const override {
    assert(
        SVectorsAreEqual(GetInputValue(1).shape(), GetInputValue(2).shape()));
    return xt::where(GetInputValue(0), GetInputValue(1), GetInputValue(2));
  }
};
}  // namespace SimpleML

#pragma once

#include <cassert>
#include <memory>

#include "simpleml/operations/internal/operation.h"
#include "simpleml/variable.h"
#include "xtensor/xstrided_view.hpp"

namespace SimpleML {
class TransposeOperation : public Operation {
 public:
  TransposeOperation(const VariableNode* input) : Operation({input}) {}
  virtual const char* GetName() const override { return "Transpose"; }
  
  virtual Shape GetResultShape() const override {
    Shape parent_shape = inputs_[0]->GetOperation().GetResultShape();
    // Simply reverse the dimensions.
    std::reverse(parent_shape.begin(), parent_shape.end());
    return parent_shape;
  }

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

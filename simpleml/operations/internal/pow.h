#pragma once

#include <string_view>

#include "simpleml/operations/internal/operation.h"
#include "simpleml/variable.h"
#include "simpleml/operations/internal/mul.h"

namespace SimpleML {
class PowOperation : public Operation {
 public:
  PowOperation(const VariableNode* variable, const VariableNode* power)
      : Operation({variable, power}) {}
  virtual const char* GetName() const override { return "pow"; }

  virtual Tensor Compute() const override {
    return xt::pow(GetInputValue(0), GetInputValue(1));
  }
  
  virtual std::unique_ptr<Operation> GetBackProp(
    Graph& graph, const VariableNode* input,
    const VariableNode* gradient) const override {
    // Can only support getting derivative w.r.t base for now.
    assert(input == inputs_[0]);
    // Subtract one from the power (TODO: Implement subtract?)
    VariableNode* new_pow = Operations::Add(inputs_[1],
      Operations::Constant(Tensor{-1.0}, std::string_view(), graph), std::string_view(), graph);
    VariableNode* new_base = Operations::Pow(inputs_[0],
      new_pow, graph);
    VariableNode* result = Operations::Mul(new_base, inputs_[1], std::string_view(), graph);
    return std::make_unique<MulOperation>(result, gradient);
  }
};
}  // namespace SimpleML

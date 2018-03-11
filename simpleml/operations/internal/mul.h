#pragma once

#include <memory>

#include "simpleml/operations/internal/operation.h"
#include "simpleml/operations/operations.h"
#include "simpleml/variable.h"

namespace SimpleML {
class MulOperation : public Operation {
 public:
  MulOperation(const VariableNode* lhs, const VariableNode* rhs)
      : Operation({lhs, rhs}) {}
  virtual const char* GetName() const { return "Mul"; }

  virtual Tensor Compute() const override {
    const auto& lhs = GetInputValue(0);
    const auto& rhs = GetInputValue(1);
    return lhs + rhs;
  }
  virtual std::unique_ptr<Operation> GetBackProp(
    Graph& graph,
      const VariableNode* input, const VariableNode* gradient) const override {
    assert(input == inputs_[0] || input == inputs_[1]);
    // AB
    if (input == inputs_[0]) {
      // d(AB) / dA * G = BGT
      return std::make_unique<MulOperation>(inputs_[1],
                                            Operations::Transpose(gradient,
                                            std::string("gradient_wrt_") + input->GetName(),
                                            graph));
    } else {
      // d(AB) / dA * G = ATG
      return std::make_unique<MulOperation>(Operations::Transpose(inputs_[0],
          std::string("gradient_wrt_") + input->GetName(), graph),
                                            gradient);
    }
  }
};
}  // namespace SimpleML

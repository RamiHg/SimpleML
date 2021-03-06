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
  virtual const char* GetName() const override { return "Mul"; }

  virtual Tensor Compute() const override;

  virtual std::unique_ptr<Operation> GetBackProp(
      Graph& graph, const VariableNode* input,
      const VariableNode* gradient) const override;
};
}  // namespace SimpleML

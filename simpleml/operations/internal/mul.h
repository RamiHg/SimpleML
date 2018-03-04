#pragma once

#include <memory>

#include "simpleml/operations/internal/operation.h"
#include "simpleml/variable.h"

namespace SimpleML {
class MulOperation : public Operation {
 public:
  MulOperation(const VariableSPtr& lhs, const VariableSPtr& rhs)
      : Operation({lhs, rhs}) {}

  virtual Tensor Compute() const override;
  virtual std::unique_ptr<Operation> GetBackProp(
      const std::shared_ptr<VariableNode>& input,
      const std::shared_ptr<VariableNode>& gradient) const override;
};
}  // namespace SimpleML
#pragma once

#include <memory>

#include "simpleml/operations/internal/operation.h"

namespace SimpleML {
class AddOperation : public Operation {
 public:
  AddOperation(const VariableList& inputs) : Operation(inputs) {}

  virtual Tensor Compute() const override;
  virtual std::unique_ptr<Operation> GetBackProp(
      const std::shared_ptr<Variable>& input,
      const std::shared_ptr<Variable>& gradient) const override;
};
}  // namespace SimpleML
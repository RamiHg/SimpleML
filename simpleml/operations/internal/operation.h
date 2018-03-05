#pragma once

#include <memory>
#include <vector>

#include "simpleml/math/tensor.h"

namespace SimpleML {

class VariableNode;
// Base class for operations.
// Defines something that can be done and taken a gradient of.
class Operation {
 public:
  using VariableList = std::vector<std::shared_ptr<VariableNode>>;

  Operation(const VariableList& inputs);
  virtual ~Operation() {}
  // Computes the value of the operation based on its inputs and returns the
  //  value.
  virtual Tensor Compute() const = 0;
  // Returns the operation to compute gradient with respect to a specific input.
  virtual std::unique_ptr<Operation> GetBackProp(
      const std::shared_ptr<VariableNode>& input,
      const std::shared_ptr<VariableNode>& gradient) const = 0;

  const VariableList& GetInputs() const { return inputs_; }

 protected:
  const Tensor& GetInputValue(size_t child_index) const;

  VariableList inputs_;
};

}  // namespace SimpleML

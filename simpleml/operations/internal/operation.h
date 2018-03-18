#pragma once

#include <memory>
#include <vector>

#include "simpleml/math/tensor.h"

namespace SimpleML {

class VariableNode;
class Graph;
// Base class for operations.
// Defines something that can be done and taken a gradient of.
class Operation {
 public:
  using VariableList = std::vector<const VariableNode*>;

  Operation(const VariableList& inputs);
  virtual ~Operation() {}
  virtual const char* GetName() const { return "GenericOperation"; }
  // Computes the value of the operation based on its inputs and returns the
  //  value.
  virtual Tensor Compute() const = 0;
  // Returns the expected shape of the operation. Will return [] if the
  // shape is completely unknown. Unknown dimension sizes will be set to -1.
  virtual Shape GetResultShape() const { return {}; }
  // Returns the operation to compute gradient with respect to a specific input.
  virtual std::unique_ptr<Operation> GetBackProp(
      Graph& graph, const VariableNode* input,
      const VariableNode* gradient) const {
      (void)input;
      (void)gradient;
    assert(false && "Operation is not differentiable.");
    return nullptr;
  }

  const VariableList& GetInputs() const { return inputs_; }

 protected:
  const Tensor& GetInputValue(size_t child_index) const;

  VariableList inputs_;
};

}  // namespace SimpleML

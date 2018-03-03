#pragma once

#include <memory>
#include <vector>

#include "simpleml/math/tensor.h"

namespace SimpleML {

class Operation;

typedef std::shared_ptr<Operation> OperationPtr;

// Base class for operations.
// Defines something that can be done and taken a gradient of.
class Operation {
 public:
  using InputVector = std::vector<std::shared_ptr<Operation>>;

  Operation(const InputVector& inputs);
  virtual ~Operation() {}
  // Computes the value of the operation based on its inputs and returns the
  //  value.
  virtual SimpleML::Tensor Compute() const = 0;
  // Returns the operation to compute gradient with respect to a specific input.
  virtual OperationPtr GetBackProp(const OperationPtr& input,
                                   const OperationPtr& gradient) const = 0;

  const Tensor& GetValue() const { return value_; }

 protected:
  const Tensor& GetInputValue(size_t child_index) const;

  InputVector inputs_;
  SimpleML::Tensor value_;
};

}  // namespace SimpleML

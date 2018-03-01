#pragma once

#include <memory>
#include <vector>

#include "simpleml/math/tensor.h"

namespace SimpleML {

// Base class for operations.
// Defines something that can be done and taken a gradient of.
class Operation {
 public:
  using InputVector = std::vector<std::shared_ptr<const Operation>>;

  Operation(const InputVector& inputs);
  virtual ~Operation() {}
  // Computes the value of the operation based on its inputs and returns the
  //  value.
  virtual SimpleML::Tensor Compute() const = 0;

  const Tensor& GetValue() const { return value_; }

 protected:
  const Tensor& GetInputValue(size_t child_index) const;

  InputVector inputs_;
  SimpleML::Tensor value_;
};

}  // namespace SimpleML

#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <unordered_set>

#include "simpleml/math/tensor.h"

namespace SimpleML {

class Operation;
class VariableNode;

typedef std::shared_ptr<VariableNode> VariableSPtr;

// A variable is not meant to be created directly. Please use SimpleML::Variable
// to create it.
class VariableNode {
 public:
  // Create a Variable node from an operation that created it.
  VariableNode(std::string_view name, std::unique_ptr<Operation> operation);

  const std::string& GetName() const { return name_; }

  void SetValue(const Tensor& value) { value_ = value; }
  const Tensor& GetValue() const { return value_; }
  const Operation& GetOperation() const { return *operation_; }

 private:
  const std::string name_;
  std::unique_ptr<Operation> operation_;
  Tensor value_;
};

}  // namespace SimpleML

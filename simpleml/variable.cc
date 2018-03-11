#include "simpleml/variable.h"

#include "simpleml/operations/internal/operation.h"

#include <algorithm>

namespace SimpleML {

VariableNode::VariableNode(std::string_view name,
                           std::unique_ptr<Operation> operation)
    : name_(name), operation_(std::move(operation)) {}

}  // namespace SimpleML

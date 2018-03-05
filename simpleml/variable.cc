#include "simpleml/variable.h"

#include "simpleml/operations/internal/operation.h"

#include <algorithm>

namespace SimpleML {

VariableNode::VariableNode(std::string_view name,
                           std::unique_ptr<Operation> operation)
    : name_(name), operation_(std::move(operation)) {
  // Add us as descendants to the operation's inputs.
  // It's kind of hacky to be put here.. But it has to be put somewhere.

  for (auto& input : operation_->GetInputs()) {
    input->AddDescendant(this);
  }
}

void VariableNode::AddDescendant(VariableNode* descendant) {
  descendants_.insert(descendant);
}

}  // namespace SimpleML
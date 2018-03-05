#include "simpleml/graph.h"

#include <vector>

#include "simpleml/operations/internal/operation.h"
#include "simpleml/variable.h"

namespace SimpleML {

Graph Graph::s_graph;

// Helper methods.
static std::vector<VariableNode*> GetGraphInputs(
    const std::list<VariableSPtr>& nodes) {
  std::vector<VariableNode*> result;

  for (const auto& node : nodes) {
    if (node->GetOperation().GetInputs().empty()) {
      result.push_back(node.get());
    }
  }

  return result;
}

Graph::Graph() : num_nodes_(0) {}

void Graph::Reset() {
  nodes_.clear();
  num_nodes_ = 0;
}

void Graph::AddNode(const std::shared_ptr<VariableNode>& node) {
  nodes_.push_back(node);
}

void Graph::ForwardPropagate() {
  auto to_process = GetGraphInputs(nodes_);

  // Depth first evaluation of inputs.
  while (!to_process.empty()) {
    VariableNode* node = to_process.back();
    to_process.pop_back();

    const Operation& operation = node->GetOperation();
    const Tensor new_value = operation.Compute();
    node->SetValue(new_value);  // move?

    const auto& descendants = node->GetDescendants();
    to_process.insert(to_process.end(), descendants.cbegin(),
                      descendants.cend());
  }
}
}  // namespace SimpleML
#include "simpleml/forward_prop.h"

#include <deque>

#include "simpleml/graph.h"
#include "simpleml/graph_util.h"
#include "simpleml/operations/internal/operation.h"
#include "simpleml/shape_util.h"

namespace SimpleML {
// Graph inputs are nodes with operations that have no inputs.
static std::deque<VariableNode*> GetGraphInputs(
    const Graph::NodeMap& node_map) {
  std::deque<VariableNode*> inputs;
  for (const auto& pair : node_map) {
    if (pair.second->GetOperation().GetInputs().empty()) {
      inputs.push_back(pair.second.get());
    }
  }
  return inputs;
}

void ForwardPropagate(Graph& graph) {
  const auto& node_map = graph.GetNodes();
  auto to_process = GetGraphInputs(node_map);
  // Get descendants of all nodes in the graph.
  AdjacencyMap descendants_map = GetNodeDescendants(graph);

  // Breadth first evaluation of inputs.
  while (!to_process.empty()) {
    VariableNode* node = to_process.front();
    to_process.pop_front();

    const Operation& operation = node->GetOperation();
    const Tensor new_value = operation.Compute();
    // Assert that the new value matches the operation shape.
    assert(CheckShapesMatch(new_value, operation.GetResultShape()));
    node->SetValue(new_value);  // move?

    const auto& descendants = descendants_map[node];
    to_process.insert(to_process.end(), descendants.cbegin(),
                      descendants.cend());
  }
}
}  // namespace SimpleML

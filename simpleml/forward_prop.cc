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

// DFS to do topological sorting as described in
// https://en.wikipedia.org/wiki/Topological_sorting
static void VisitNode(VariableNode* node,
                      std::unordered_set<VariableNode*>& unmarked_nodes,
                      const AdjacencyMap& descendants_map,
                      std::deque<VariableNode*>& sorted_nodes,
                      std::unordered_set<VariableNode*>& perm_marks,
                      std::unordered_set<VariableNode*>& temp_marks) {
  if (perm_marks.count(node)) return;
  assert(temp_marks.count(node) == 0);  // not a dag.
  temp_marks.insert(node);
  if (descendants_map.count(node) > 0) {
    for (auto descendant : descendants_map.at(node)) {
      VisitNode(descendant, unmarked_nodes, descendants_map, sorted_nodes,
                perm_marks, temp_marks);
    }
  }
  perm_marks.insert(node);
  unmarked_nodes.erase(node);
  sorted_nodes.push_front(node);
}

void ForwardPropagate(Graph& graph) {
  const auto& node_map = graph.GetNodes();
  // Get descendants of all nodes in the graph.
  AdjacencyMap descendants_map = GetNodeDescendants(graph);

  std::unordered_set<VariableNode*> unmarked_nodes, perm_marks, temp_marks;
  for (const auto& pair : node_map) {
    unmarked_nodes.insert(pair.second.get());
  }

  std::deque<VariableNode*> sorted_nodes;

  while (!unmarked_nodes.empty()) {
    VariableNode* node = *unmarked_nodes.begin();
    VisitNode(node, unmarked_nodes, descendants_map, sorted_nodes, perm_marks,
              temp_marks);
  }

  while (!sorted_nodes.empty()) {
    VariableNode* node = sorted_nodes.front();
    sorted_nodes.pop_front();

    const Operation& operation = node->GetOperation();
    const Tensor new_value = operation.Compute();
    assert(CheckShapesMatch(new_value, operation.GetResultShape()));
    // Assert that the new value matches the operation shape.

    node->SetValue(new_value);  // move?
  }
}
}  // namespace SimpleML

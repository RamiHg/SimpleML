#include "simpleml/graph_util.h"
#include "simpleml/graph.h"
#include "simpleml/operations/internal/operation.h"

namespace SimpleML {
AdjacencyMap GetNodeDescendants(const Graph& graph) {
  AdjacencyMap map;
  for (const auto& pair : graph.GetNodes()) {
    const auto& node = pair.second;
    const auto& operation = node->GetOperation();
    for (const auto* input : operation.GetInputs()) {
      map[input].push_back(node.get());
    }
  }
  return map;
}
}  // namespace SimpleML

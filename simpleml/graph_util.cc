#include "simpleml/graph_util.h"

#include <sstream>

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

static std::string NameOpVariable(std::string_view op_name,
                                  const Graph& graph) {
  std::stringstream name_stream;
  name_stream << op_name << "_" << graph.GetNumNodes();
  return name_stream.str();
}

std::string GetUniqueNodeName(const Graph& graph, std::string_view overriden,
                              std::string_view prefix) {
  return overriden.empty() ? NameOpVariable(prefix, graph)
                           : std::string(overriden);
}
}  // namespace SimpleML

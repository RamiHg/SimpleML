#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace SimpleML {
class VariableNode;
class Graph;

std::string GetUniqueNodeName(const Graph& graph, std::string_view overriden,
                              std::string_view prefix);

typedef std::unordered_map<const VariableNode*, std::vector<VariableNode*>>
    AdjacencyMap;

AdjacencyMap GetNodeDescendants(const Graph& graph);
}  // namespace SimpleML

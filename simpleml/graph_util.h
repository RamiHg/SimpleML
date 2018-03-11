#pragma once

#include <unordered_map>
#include <vector>

namespace SimpleML {
class VariableNode;
class Graph;

typedef std::unordered_map<const VariableNode*, std::vector<VariableNode*>>
    AdjacencyMap;

AdjacencyMap GetNodeDescendants(const Graph& graph);
}  // namespace SimpleML

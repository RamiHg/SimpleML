#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "simpleml/graph.h"

namespace SimpleML {

std::unique_ptr<Graph> CreateBackpropGraph(const Graph& graph,
                                           VariableNode* input,
                                           std::unordered_map<std::string, VariableNode*>& grad_table);
}

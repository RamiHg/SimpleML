#pragma once

#include <memory>

#include "simpleml/graph.h"

namespace SimpleML {

std::unique_ptr<Graph> CreateBackpropGraph(const Graph& graph,
                                           VariableNode* input);
}

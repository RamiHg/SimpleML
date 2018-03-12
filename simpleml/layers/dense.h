#pragma once

#include <string_view>

#include "simpleml/graph.h"

namespace SimpleML {

class VariableNode;

namespace Layers {

VariableNode* DenseLayer(VariableNode* input, int width,
                         Graph& graph = Graph::GetDefaultGraph(),
                         std::string_view name = std::string_view());
}
}  // namespace SimpleML

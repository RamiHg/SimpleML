#pragma once

#include "simpleml/graph.h"

namespace SimpleML {
class VariableNode;

namespace Losses {

VariableNode* MeanSquaredError(VariableNode* labels, VariableNode* predictions,
                               Graph& graph = Graph::GetDefaultGraph());
}
}  // namespace SimpleML

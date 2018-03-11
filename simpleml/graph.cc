#include "simpleml/graph.h"

#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "simpleml/operations/internal/operation.h"
#include "simpleml/operations/operations.h"
#include "simpleml/variable.h"

namespace SimpleML {

Graph Graph::s_default_graph;

// Helper methods.

Graph::Graph() {}

VariableNode* Graph::CreateVariableNode(std::string_view name,
                                        std::unique_ptr<Operation> operation) {
  VariableSPtr variable =
      std::make_shared<VariableNode>(name, std::move(operation));
  assert(nodes_.count(variable->GetName()) == 0);
  nodes_.insert(std::make_pair(variable->GetName(), variable));
  return variable.get();
}

void Graph::Reset() { nodes_.clear(); }

}  // namespace SimpleML

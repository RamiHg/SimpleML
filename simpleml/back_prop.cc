#include "simpleml/back_prop.h"

#include <algorithm>
#include <unordered_set>
#include <vector>

#include "simpleml/graph.h"
#include "simpleml/graph_util.h"
#include "simpleml/operations/internal/operation.h"
#include "simpleml/operations/operations.h"
#include "simpleml/variable.h"

namespace SimpleML {

// Returns all descendants of variables.
static std::unordered_set<VariableNode*> GetDescendantsOf(
    const std::vector<VariableNode*>& variables,
    const AdjacencyMap& descendant_map) {
  std::unordered_set<VariableNode*> visited;
  std::vector<VariableNode*> to_visit;
  to_visit.reserve(variables.size());
  for (VariableNode* variable : variables) to_visit.push_back(variable);

  while (!to_visit.empty()) {
    VariableNode* node = to_visit.back();
    to_visit.pop_back();
    auto it = descendant_map.find(node);
    if (it == descendant_map.end()) {
      // Leaf node.
      continue;
    }
    for (VariableNode* descendant : it->second) {
      if (visited.find(descendant) == visited.end()) {
        visited.insert(descendant);
        to_visit.push_back(descendant);
      }
    }
  }

  return visited;
}

// Returns all ancestor nodes of node.
static std::unordered_set<VariableNode*> GetAncestorsOf(VariableNode* node) {
  // Pretty much exactly the same as GetDescendantsOf except going backwards.
  std::unordered_set<VariableNode*> ancestors;
  std::vector<VariableNode*> to_visit = {node};
  while (!to_visit.empty()) {
    VariableNode* node = to_visit.back();
    to_visit.pop_back();
    for (const VariableNode* ptr_const : node->GetOperation().GetInputs()) {
      // This is terrible. Just terrible. Figure this out another way.
      VariableNode* ptr = const_cast<VariableNode*>(ptr_const);
      if (ancestors.find(ptr) == ancestors.end()) {
        ancestors.insert(ptr);
        to_visit.push_back(ptr);
      }
    }
  }
  return ancestors;
}

// Helper function that actually does the gradient computations.
static VariableNode* BuildGradient(
    Graph& graph, VariableNode* variable,
    const std::unordered_set<VariableNode*>& gradient_participants,
    // AdjacencyMap& descendant_map,
    std::unordered_map<std::string, VariableNode*>& grad_table) {
  // If we've already computed the gradient for this variable, early out.
  if (grad_table.find(variable->GetName()) != grad_table.end()) {
    return grad_table.at(variable->GetName());
  }

  if (gradient_participants.find(variable) == gradient_participants.end()) {
    return nullptr;
  }

  // This is TERRIBLE. Find a better way.
  AdjacencyMap descendant_map = GetNodeDescendants(graph);

  std::vector<VariableNode*> partial_gradients;
  if (descendant_map.find(variable) != descendant_map.end()) {
    for (VariableNode* descendant : descendant_map.at(variable)) {
      // Only compute gradients for variables that participate in the gradient
      // of the target.
      if (gradient_participants.find(descendant) ==
          gradient_participants.end()) {
        continue;
      }

      // Recursively call on descendant.
      VariableNode* child_gradient =
          BuildGradient(graph, descendant, gradient_participants, grad_table);
      // Crete a new variable that is the result of applying the backwards
      // propagation.
      VariableNode* gradient = graph.CreateVariableNode(
          variable->GetName() + "_" + descendant->GetName() + "_gradient",
          descendant->GetOperation().GetBackProp(graph, variable,
                                                 child_gradient));

      partial_gradients.push_back(gradient);
    }
  }

  VariableNode* gradient;
  if (partial_gradients.empty()) {
    gradient = Operations::Constant(
        Tensor{1.f}, graph, variable->GetName() + "_constant_gradient");
  } else {
    gradient = partial_gradients.back();
    partial_gradients.pop_back();
    // TODO: Create a multisum to optimize this.
    for (auto& partial_gradient : partial_gradients) {
      gradient = Operations::Add(
          gradient, partial_gradient,
          graph,
          gradient->GetName() + std::string("_partial_gradient_sum"));
    }
  }

  grad_table[variable->GetName()] = gradient;
  return gradient;
}

std::unique_ptr<Graph> CreateBackpropGraph(const Graph& input_graph,
                                           VariableNode* input) {
  // First, create a copy of the graph.
  std::unique_ptr<Graph> graph = std::make_unique<Graph>(input_graph);
  AdjacencyMap descendant_map = GetNodeDescendants(*graph);

  // TODO: Eventually figure out which variables need gradients and which
  // variables don't.
  std::vector<VariableNode*> need_gradients;
  for (const auto& pair : graph->GetNodes()) {
    // Only put nodes that have inputs.
    if (1 || !pair.second->GetOperation().GetInputs().empty()) {
      need_gradients.push_back(pair.second.get());
    }
  }

  // Find descendants of need_gradients.
  auto descendants_of_need_gradients =
      GetDescendantsOf(need_gradients, descendant_map);
  // for (auto variable : need_gradients)
  //  descendants_of_need_gradients.insert(variable);
  // Find ancestors of input.
  auto ancestors_of_input = GetAncestorsOf(input);
  ancestors_of_input.insert(input);
  // Participants in gradients is the intersection of those two sets.
  std::unordered_set<VariableNode*> gradient_participants;
  for (auto first : descendants_of_need_gradients) {
    if (ancestors_of_input.count(first) > 0) {
      gradient_participants.insert(first);
    }
  }

  std::unordered_map<std::string, VariableNode*> grad_table;
  grad_table[input->GetName()] = Operations::Constant(
      Tensor{1.f}, *graph, input->GetName() + "_initial_gradient");

  for (VariableNode* target : need_gradients) {
    BuildGradient(*graph, target, gradient_participants, grad_table);
  }

  return graph;
}

}  // namespace SimpleML

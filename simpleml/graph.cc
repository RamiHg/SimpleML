#include "simpleml/graph.h"

#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "simpleml/operations/internal/operation.h"
#include "simpleml/operations/operations.h"
#include "simpleml/variable.h"

namespace SimpleML {

Graph Graph::s_graph;

// Helper methods.
static std::vector<VariableNode*> GetGraphInputs(
    const std::list<VariableSPtr>& nodes) {
  std::vector<VariableNode*> result;

  for (const auto& node : nodes) {
    if (node->GetOperation().GetInputs().empty()) {
      result.push_back(node.get());
    }
  }

  return result;
}

static std::unordered_set<VariableNode*> GetDescendantsOf(
    const std::vector<VariableSPtr>& variables) {
  std::unordered_set<VariableNode*> visited;
  std::vector<VariableNode*> to_visit;
  to_visit.reserve(variables.size());
  for (const auto& ptr : variables) to_visit.push_back(ptr.get());

  // TODO: Could only have one set if initially put descendants of variables
  // in to_visit.
  while (!to_visit.empty()) {
    VariableNode* node = to_visit.back();
    to_visit.pop_back();
    for (VariableNode* descendant : node->GetDescendants()) {
      if (visited.find(descendant) != visited.end()) {
        visited.insert(descendant);
        to_visit.push_back(descendant);
      }
    }
  }

  return visited;
}

static std::unordered_set<VariableNode*> GetAncestorsOf(VariableNode* node) {
  // Pretty much exactly the same as GetDescendantsOf except going backwards.
  std::unordered_set<VariableNode*> ancestors;
  std::vector<VariableNode*> to_visit = {node};
  while (!to_visit.empty()) {
    VariableNode* node = to_visit.back();
    to_visit.pop_back();
    for (const VariableSPtr& ptr : node->GetOperation().GetInputs()) {
      if (ancestors.find(ptr.get()) != ancestors.end()) {
        ancestors.insert(ptr.get());
        to_visit.push_back(ptr.get());
      }
    }
  }
  return ancestors;
}

Graph::Graph() : num_nodes_(0) {}

void Graph::Reset() {
  nodes_.clear();
  num_nodes_ = 0;
}

void Graph::AddNode(const std::shared_ptr<VariableNode>& node) {
  nodes_.push_back(node);
}

void Graph::ForwardPropagate() {
  auto to_process = GetGraphInputs(nodes_);

  // Depth first evaluation of inputs.
  while (!to_process.empty()) {
    VariableNode* node = to_process.back();
    to_process.pop_back();

    const Operation& operation = node->GetOperation();
    const Tensor new_value = operation.Compute();
    node->SetValue(new_value);  // move?

    const auto& descendants = node->GetDescendants();
    to_process.insert(to_process.end(), descendants.cbegin(),
                      descendants.cend());
  }
}

// Helper function that actually does the gradient computations.
// gradient_participants is a map to shared_ptr instead of a set because I made
// a terrible design decision by having all descendants as raw pointers
// instead of weak refs. Could fix this one day. But not really.
static VariableSPtr BuildGradient(
    VariableSPtr variable, std::vector<VariableSPtr>& new_nodes,
    const std::unordered_map<VariableNode*, VariableSPtr>&
        gradient_participants,
    std::unordered_map<VariableSPtr, VariableSPtr>& grad_table) {
  if (gradient_participants.find(variable.get()) !=
      gradient_participants.end()) {
    return variable;
  }

  std::vector<VariableSPtr> partial_gradients;
  for (VariableNode* descendant : variable->GetDescendants()) {
    // Only compute gradients for nodes that participate in the gradient
    // of the target.
    if (gradient_participants.find(descendant) == gradient_participants.end()) {
      continue;
    }

    VariableSPtr descendant_sptr = gradient_participants.at(descendant);

    // Recursively call on descendant.
    const Operation& op = descendant->GetOperation();
    VariableSPtr child_gradient = BuildGradient(
        descendant_sptr, new_nodes, gradient_participants, grad_table);
    // Create a new variable that is the result of the backwards propagation.
    VariableSPtr gradient = std::make_shared<VariableNode>(
        descendant->GetName() + std::string("_gradient"),
        op.GetBackProp(variable, child_gradient));
    partial_gradients.push_back(gradient);
    new_nodes.push_back(gradient);
  }

  // TODO: Create a multisum to optimize this.
  assert(!partial_gradients.empty());
  VariableSPtr gradient = partial_gradients.back();
  partial_gradients.pop_back();
  for (auto& partial_gradient : partial_gradients) {
    gradient = Operations::Add(
        gradient, partial_gradient,
        gradient->GetName() + std::string("_partial_gradient_sum"));
    new_nodes.push_back(gradient);
  }

  grad_table[variable] = gradient;
  return gradient;
}

void Graph::BuildBackwardPropagation(const VariableSPtr& input) {
  // Get the list of all nodes that need their gradients computed.
  std::vector<VariableSPtr> need_gradients;
  for (const auto& node : nodes_) {
    if (!node->GetOperation().GetInputs().empty()) {
      need_gradients.push_back(node);
    }
  }

  // Find nodes that participate in the gradient.
  // I.e. ancestors of input, and descendants of need_gradients.
  std::unordered_set<VariableNode*> gradient_participants;
  // Find descendants of need_gradients.
  const auto descendants_of_need_gradients = GetDescendantsOf(need_gradients);
  gradient_participants.insert(descendants_of_need_gradients.begin(),
                               descendants_of_need_gradients.end());
  // Then, ancestors of input.
  const auto ancestors_of_input = GetAncestorsOf(input.get());
  gradient_participants.insert(ancestors_of_input.begin(),
                               ancestors_of_input.end());

  // Horrible hack, see documentation of BuildGradient.
  std::unordered_map<VariableNode*, VariableSPtr> gradient_participants_map;
  for (VariableSPtr& node : nodes_) {
    if (gradient_participants.find(node.get()) != gradient_participants.end()) {
      gradient_participants_map[node.get()] = node;
    }
  }

  std::unordered_map<VariableSPtr, VariableSPtr> grad_table;
  grad_table[input] = Operations::Constant(Tensor{1.});
  std::vector<VariableSPtr> new_nodes;
  // Loop over all the target set of variables and compute their gradients.
  for (VariableSPtr& target : need_gradients) {
    BuildGradient(target, new_nodes, gradient_participants_map, grad_table);
  }
}
}  // namespace SimpleML
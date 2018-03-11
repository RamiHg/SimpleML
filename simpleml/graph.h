#pragma once

#include <cstdint>
#include <memory>
#include <unordered_map>

#include "simpleml/variable.h"

namespace SimpleML {

class Graph {
 public:
  typedef std::unordered_map<std::string, VariableSPtr> NodeMap;

  Graph(const Graph& copy) = default;

  static Graph& GetDefaultGraph() { return s_default_graph; }

  const std::string& GetName() const;

  // Creates a new variable node and returns it. This is the canonical way of
  // creating new nodes in the graph.
  VariableNode* CreateVariableNode(std::string_view name,
                                   std::unique_ptr<Operation> operation);

  const auto& GetNodes() const { return nodes_; }

  int GetNumNodes() const { return nodes_.size(); }

  void ForwardPropagate();
  void BuildBackwardPropagation(const VariableSPtr& input);
  void Reset();

 private:
  Graph();

  static Graph s_default_graph;
  NodeMap nodes_;
};
}  // namespace SimpleML

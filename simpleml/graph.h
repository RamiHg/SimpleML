#pragma once

#include <cstdint>
#include <list>
#include <memory>

namespace SimpleML {

class VariableNode;

class Graph {
 public:
  static Graph& Get() { return s_graph; }

  void ForwardPropagate();
  void Reset();

  void AddNode(const std::shared_ptr<VariableNode>& node);
  int GetNumNodes() const { return num_nodes_; }

 private:
  Graph();
  Graph(const Graph& copy) = delete;

  static Graph s_graph;

  std::list<std::shared_ptr<VariableNode>> nodes_;
  int num_nodes_;
};
}  // namespace SimpleML
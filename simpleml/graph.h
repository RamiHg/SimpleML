#pragma once

#include <cstdint>
#include <list>

namespace SimpleML {

class VariableNode;

class Graph {
 public:
  static Graph& Get();

  void AddNode(const std::shared_ptr<VariableNode>& node);
  int GetNumNodes() const { return num_nodes_; }

 private:
  Graph() = delete;
  Graph(const Graph& copy) = delete;

  std::list<std::shared_ptr<VariableNode>> nodes_;
  int num_nodes_;
};
}  // namespace SimpleML
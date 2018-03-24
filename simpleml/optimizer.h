#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include "simpleml/graph.h"

namespace SimpleML {

class Optimizer {
public:
 Optimizer(Graph* graph, VariableNode* loss);
 
 void Minimize();
private:
 Graph* source_graph_;
 std::unique_ptr<Graph> backprop_graph_;
 std::unordered_map<std::string, VariableNode*> grad_table_;
};

}

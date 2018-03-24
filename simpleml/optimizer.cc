#include "simpleml/optimizer.h"

#include "simpleml/back_prop.h"

namespace SimpleML {
Optimizer::Optimizer(Graph* graph, VariableNode* loss) : source_graph_(graph) {
  backprop_graph_ = CreateBackpropGraph(*graph, loss, grad_table_);
}

void Optimizer::Minimize() {
  constexpr double kLearningRate = 0.0001;
  
  
}
}

#include "simpleml/losses/mse.h"

#include "simpleml/graph.h"
#include "simpleml/operations/operations.h"
#include "simpleml/variable.h"

namespace SimpleML {
namespace Losses {
VariableNode* MeanSquaredError(VariableNode* labels, VariableNode* predictions,
                               Graph& graph) {
  // MSE = (labels - predictions)^2
  // TODO: Actually implement subtract already!
  VariableNode* neg_predictions = Operations::Mul(
      predictions, Operations::Constant(Tensor{-1.0}, graph), graph);
  VariableNode* labels_sub_predictions =
      Operations::Add(labels, neg_predictions, graph);
  VariableNode* result = Operations::Pow(
      labels_sub_predictions, Operations::Constant(Tensor{2.0}), graph);
  return result;
}
}  // namespace Losses
}  // namespace SimpleML

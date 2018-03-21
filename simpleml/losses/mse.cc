#include "simpleml/losses/mse.h"

#include "simpleml/graph.h"
#include "simpleml/variable.h"
#include "simpleml/operations/operations.h"

namespace SimpleML {
namespace Losses {
VariableNode* MeanSquaredError(VariableNode* labels, VariableNode* predictions, Graph& graph) {
  // MSE = (labels - predictions)^2
}
}
}

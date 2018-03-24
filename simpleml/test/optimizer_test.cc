#include "gtest/gtest.h"

#include "simpleml/optimizer.h"
#include "simpleml/graph.h"
#include "simpleml/operations/operations.h"
#include "simpleml/losses.h"

namespace SimpleML {

using namespace Operations;

class OptimizerTest : public testing::Test {
  public:
    OptimizerTest() {
      // Reset the graph.
      Graph::GetDefaultGraph().Reset();
    }
};

TEST_F(OptimizerTest, TestSimpleLinearSystem) {
  // Create a simple linear system
  // Ax = b
  // And make sure that the system can solve for A.
  auto A = Constant(Tensor {
    {1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0}
  });
  // TODO: Create a Variable operation
  A->SetTrainable(true);
  auto x = Constant(Tensor{1., 2., 3.});
  auto b = Constant(Tensor{4., 5., 6.});
  
  auto Ax = MatMul(A, x);
  auto loss = Losses::MeanSquaredError(b, Ax);
}

}

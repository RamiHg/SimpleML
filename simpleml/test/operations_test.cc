#include "gtest/gtest.h"

#include "simpleml/back_prop.h"
#include "simpleml/forward_prop.h"
#include "simpleml/graph.h"
#include "simpleml/graph_vis.h"
#include "simpleml/operations/operations.h"
#include "simpleml/variable.h"

namespace SimpleML {

using namespace Operations;

class OperationsTest : public testing::Test {
 public:
  OperationsTest() { Graph::GetDefaultGraph().Reset(); }
};

TEST_F(OperationsTest, TestConstant) {
  auto test = Tensor{1., 2., 3.};
  auto var = Constant(test);
  ForwardPropagate(Graph::GetDefaultGraph());
  EXPECT_EQ(var->GetValue(), test);
}

TEST_F(OperationsTest, TestAdd) {
  auto a = Constant(Tensor{1., 2., 3.});
  auto b = Constant(Tensor{4., 5., 6.});
  auto c = Add(a, b);
  auto d = Add(c, c);
  ForwardPropagate(Graph::GetDefaultGraph());
  auto result = Tensor{5., 7., 9.};
  EXPECT_EQ(c->GetValue(), result);
  result = result + result;
  EXPECT_EQ(d->GetValue(), result);
}

TEST_F(OperationsTest, TestAddBackprop) {
  int x;
  printf("It's %d\n", x);
  auto a = Constant(Tensor{1., 2., 3.});
  auto b = Constant(Tensor{4., 5., 6.});
  auto c = Mul(a, b);
  auto d = Mul(c, a);
  auto back_prop_graph = CreateBackpropGraph(Graph::GetDefaultGraph(), d);
  SerializeGraphToDotFile(*back_prop_graph, "/tmp/testbackprop.dot");
  ForwardPropagate(*back_prop_graph);
}

}  // namespace SimpleML

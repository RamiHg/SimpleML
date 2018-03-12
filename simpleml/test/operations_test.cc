#include "gtest/gtest.h"

#include "simpleml/back_prop.h"
#include "simpleml/forward_prop.h"
#include "simpleml/graph.h"
#include "simpleml/graph_vis.h"
#include "simpleml/operations/operations.h"
#include "simpleml/variable.h"

#include "xtensor-blas/xlinalg.hpp"

namespace SimpleML {

using namespace Operations;

class OperationsTest : public testing::Test {
 public:
  OperationsTest() {
    // Reset the graph
    Graph::GetDefaultGraph().Reset();
  }
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
  auto d = Constant(Tensor{3.});
  auto e = Add(a, d);
  ForwardPropagate(Graph::GetDefaultGraph());
  auto result = Tensor{5., 7., 9.};
  EXPECT_EQ(c->GetValue(), result);
  auto result2 = Tensor{4., 5., 6.};
  EXPECT_EQ(e->GetValue(), result2);
}

TEST_F(OperationsTest, TestGte) {
  auto a = Constant({1., 2., 5.});
  auto b = Constant({7., 1., 5.});
  auto c = Gte(a, b);
  auto d = Constant({2.});
  auto e = Gte(a, d);
  ForwardPropagate(Graph::GetDefaultGraph());
  auto result = Tensor{0., 1., 1.};
  EXPECT_EQ(c->GetValue(), result);
  EXPECT_EQ(e->GetValue(), result);
}

TEST_F(OperationsTest, TestWhere) {
  auto cond = Constant({1., 0., 1.});
  auto a = Constant({10., 11., 12.});
  auto b = Constant({20., 21., 22.});
  auto c = Where(cond, a, b);
  ForwardPropagate(Graph::GetDefaultGraph());
  auto result = Tensor{10., 21., 12.};
  EXPECT_EQ(c->GetValue(), result);
}

TEST_F(OperationsTest, TestMul) {
  auto a = Constant({{1., 2.}, {3., 4.}});
  auto b = Constant({{5., 6.}, {7., 8.}});
  auto c = Mul(a, b);
  ForwardPropagate(Graph::GetDefaultGraph());
  auto result = Tensor{{5, 12}, {21, 32}};
  EXPECT_EQ(c->GetValue(), result);
}

TEST_F(OperationsTest, TestMatMul) {
  auto a = Constant({{1., 2.}, {3., 4.}});
  auto b = Constant({{5., 6.}, {7., 8.}});
  auto c = MatMul(a, b);
  ForwardPropagate(Graph::GetDefaultGraph());
  auto result = Tensor{{19, 22}, {43, 50}};
  EXPECT_EQ(c->GetValue(), result);
}

TEST_F(OperationsTest, TestAddBackprop) {
  auto a = Constant(Tensor{1., 2., 3.});
  auto b = Constant(Tensor{4., 5., 6.});
  auto c = Mul(a, b);
  auto d = ReLU(c);  // Mul(c, a);
}

}  // namespace SimpleML

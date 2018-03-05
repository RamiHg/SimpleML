#include "gtest/gtest.h"

#include "simpleml/graph.h"
#include "simpleml/operations/operations.h"
#include "simpleml/variable.h"

namespace SimpleML {

using namespace Operations;

class OperationsTest : public testing::Test {
 public:
  void SetUp() override { Graph::Get().Reset(); }
};

TEST_F(OperationsTest, TestConstant) {
  auto test = Tensor{1., 2., 3.};
  VariableSPtr var = Constant(test);
  Graph::Get().ForwardPropagate();
  EXPECT_EQ(var->GetValue(), test);
}

TEST_F(OperationsTest, TestAdd) {
  VariableSPtr a = Constant(Tensor{1., 2., 3.});
  VariableSPtr b = Constant(Tensor{4., 5., 6.});
  VariableSPtr c = Add(a, b, "my_add");
  Graph::Get().ForwardPropagate();
  auto result = Tensor{5., 7., 9.};
  EXPECT_EQ(c->GetValue(), result);
}

}  // namespace SimpleML
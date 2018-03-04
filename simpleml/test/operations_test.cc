#include "gtest/gtest.h"

#include "simpleml/graph.h"
#include "simpleml/operations/operations.h"
#include "simpleml/variable.h"

namespace SimpleML {

class OperationsTest : public testing::Test {
 public:
  void SetUp() override { Graph::Get().Reset(); }
};

TEST_F(OperationsTest, TestAdd) {}

}  // namespace SimpleML
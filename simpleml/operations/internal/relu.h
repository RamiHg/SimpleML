#pragma once

#include <cassert>
#include <memory>

#include "simpleml/operations/internal/operation.h"
#include "simpleml/operations/internal/where.h"
#include "simpleml/operations/operations.h"
#include "simpleml/variable.h"

namespace SimpleML {
class ReluOperation : public Operation {
 public:
  ReluOperation(const VariableNode* input) : Operation({input}) {}
  virtual const char* GetName() const override { return "ReLU"; }

  virtual Tensor Compute() const override {
    const auto& tensor = GetInputValue(0);
    return xt::fmax(tensor, 0.);
  }
  virtual std::unique_ptr<Operation> GetBackProp(
      Graph& graph, const VariableNode* input,
      const VariableNode* gradient) const override {
    // Return 1 when >= 0, and 0 when x < 0
    // Can be written as
    // where(x >= 0, 1, 0)
    auto x = inputs_[0];
    VariableNode* where_op;
    {
      auto cond = Operations::Gte(x, Operations::Constant({0.}, graph), graph);
      auto a = Operations::Constant({1.}, graph);
      auto b = Operations::Constant({0.}, graph);
      where_op = Operations::Where(cond, a, b, graph);
    }

    return std::make_unique<MulOperation>(where_op, gradient);
  }
};
}  // namespace SimpleML

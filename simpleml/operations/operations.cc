#include "simpleml/operations/operations.h"

#include <memory>

#include "simpleml/graph.h"
#include "simpleml/graph_util.h"
#include "simpleml/operations/internal/add.h"
#include "simpleml/operations/internal/constant.h"
#include "simpleml/operations/internal/gte.h"
#include "simpleml/operations/internal/matmul.h"
#include "simpleml/operations/internal/mul.h"
#include "simpleml/operations/internal/pow.h"
#include "simpleml/operations/internal/relu.h"
#include "simpleml/operations/internal/transpose.h"
#include "simpleml/operations/internal/where.h"
#include "simpleml/variable.h"

namespace SimpleML {
namespace Operations {

VariableNode* Add(const VariableNode* lhs, const VariableNode* rhs,
                  Graph& graph, std::string_view name) {
  const std::string final_name = GetUniqueNodeName(graph, name, "add");
  return graph.CreateVariableNode(final_name,
                                  std::make_unique<AddOperation>(lhs, rhs));
}

VariableNode* Mul(const VariableNode* lhs, const VariableNode* rhs,
                  Graph& graph, std::string_view name) {
  const std::string final_name = GetUniqueNodeName(graph, name, "mul");
  return graph.CreateVariableNode(final_name,
                                  std::make_unique<MulOperation>(lhs, rhs));
}

VariableNode* MatMul(const VariableNode* lhs, const VariableNode* rhs,
                     std::string_view name, Graph& graph) {
  const std::string final_name = GetUniqueNodeName(graph, name, "mul");
  return graph.CreateVariableNode(final_name,
                                  std::make_unique<MatMulOperation>(lhs, rhs));
}

VariableNode* Transpose(const VariableNode* value, std::string_view name,
                        Graph& graph) {
  const std::string final_name = GetUniqueNodeName(graph, name, "transpoes");
  return graph.CreateVariableNode(final_name,
                                  std::make_unique<TransposeOperation>(value));
}

VariableNode* Constant(const Tensor& value, Graph& graph,
                       std::string_view name) {
  const std::string final_name = GetUniqueNodeName(graph, name, "constant");
  VariableNode* variable = graph.CreateVariableNode(final_name,
                                  std::make_unique<ConstantOperation>(value));
             variable->SetTrainable(false);
             return variable;
}

VariableNode* Gte(const VariableNode* lhs, const VariableNode* rhs,
                  Graph& graph, std::string_view name) {
  const std::string final_name = GetUniqueNodeName(graph, name, "gte");
  return graph.CreateVariableNode(final_name,
                                  std::make_unique<GteOperation>(lhs, rhs));
}
VariableNode* Where(const VariableNode* cond, const VariableNode* a,
                    const VariableNode* b, Graph& graph,
                    std::string_view name) {
  const std::string final_name = GetUniqueNodeName(graph, name, "where");
  return graph.CreateVariableNode(final_name,
                                  std::make_unique<WhereOperation>(cond, a, b));
}
VariableNode* ReLU(const VariableNode* value, std::string_view name,
                   Graph& graph) {
  const std::string final_name = GetUniqueNodeName(graph, name, "relu");
  return graph.CreateVariableNode(final_name,
                                  std::make_unique<ReluOperation>(value));
}

VariableNode* Pow(const VariableNode* base, const VariableNode* power,
                  Graph& graph, std::string_view name) {
  const std::string final_name = GetUniqueNodeName(graph, name, "pow");
  return graph.CreateVariableNode(final_name,
                                  std::make_unique<PowOperation>(base, power));
}

}  // namespace Operations
}  // namespace SimpleML

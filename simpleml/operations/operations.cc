#include "simpleml/operations/operations.h"

#include <memory>

#include "simpleml/graph.h"
#include "simpleml/graph_util.h"
#include "simpleml/operations/internal/add.h"
#include "simpleml/operations/internal/constant.h"
#include "simpleml/operations/internal/gte.h"
#include "simpleml/operations/internal/mul.h"
#include "simpleml/operations/internal/relu.h"
#include "simpleml/operations/internal/transpose.h"
#include "simpleml/operations/internal/where.h"
#include "simpleml/variable.h"

namespace SimpleML {
namespace Operations {

VariableNode* Add(const VariableNode* lhs, const VariableNode* rhs,
                  std::string_view name, Graph& graph) {
  const std::string final_name = GetUniqueNodeName(graph, name, "add");
  return graph.CreateVariableNode(final_name,
                                  std::make_unique<AddOperation>(lhs, rhs));
}

VariableNode* Mul(const VariableNode* lhs, const VariableNode* rhs,
                  std::string_view name, Graph& graph) {
  const std::string final_name = GetUniqueNodeName(graph, name, "mul");
  return graph.CreateVariableNode(final_name,
                                  std::make_unique<MulOperation>(lhs, rhs));
}

VariableNode* Transpose(const VariableNode* value, std::string_view name,
                        Graph& graph) {
  const std::string final_name = GetUniqueNodeName(graph, name, "transpoes");
  return graph.CreateVariableNode(final_name,
                                  std::make_unique<TransposeOperation>(value));
}

VariableNode* Constant(const Tensor& value, std::string_view name,
                       Graph& graph) {
  const std::string final_name = GetUniqueNodeName(graph, name, "constant");
  return graph.CreateVariableNode(final_name,
                                  std::make_unique<ConstantOperation>(value));
}

VariableNode* Gte(const VariableNode* lhs, const VariableNode* rhs,
                  std::string_view name, Graph& graph) {
  const std::string final_name = GetUniqueNodeName(graph, name, "gte");
  return graph.CreateVariableNode(final_name,
                                  std::make_unique<GteOperation>(lhs, rhs));
}
VariableNode* Where(const VariableNode* cond, const VariableNode* a,
                    const VariableNode* b, std::string_view name,
                    Graph& graph) {
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

}  // namespace Operations
}  // namespace SimpleML

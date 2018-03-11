#include "simpleml/operations/operations.h"

#include <memory>
#include <sstream>

#include "simpleml/graph.h"
#include "simpleml/operations/internal/add.h"
#include "simpleml/operations/internal/constant.h"
#include "simpleml/operations/internal/mul.h"
#include "simpleml/operations/internal/transpose.h"
#include "simpleml/variable.h"

namespace SimpleML {
namespace Operations {

static std::string NameOpVariable(std::string_view op_name, Graph& graph) {
  std::stringstream name_stream;
  name_stream << op_name << "_" << graph.GetNumNodes();
  return name_stream.str();
}

VariableNode* Add(const VariableNode* lhs, const VariableNode* rhs,
                  std::string_view name, Graph& graph) {
  const std::string final_name =
      !name.empty() ? std::string(name) : NameOpVariable("add", graph);
  return graph.CreateVariableNode(final_name,
                                  std::make_unique<AddOperation>(lhs, rhs));
}

VariableNode* Mul(const VariableNode* lhs, const VariableNode* rhs,
                  std::string_view name, Graph& graph) {
  const std::string final_name =
      !name.empty() ? std::string(name) : NameOpVariable("mul", graph);
  return graph.CreateVariableNode(final_name,
                                  std::make_unique<MulOperation>(lhs, rhs));
}

VariableNode* Transpose(const VariableNode* value, std::string_view name,
                        Graph& graph) {
  const std::string final_name =
      !name.empty() ? std::string(name) : NameOpVariable("transpose", graph);
  return graph.CreateVariableNode(final_name,
                                  std::make_unique<TransposeOperation>(value));
}

VariableNode* Constant(const Tensor& value, std::string_view name,
                       Graph& graph) {
  const std::string final_name =
      !name.empty() ? std::string(name) : NameOpVariable("constant", graph);
  return graph.CreateVariableNode(final_name,
                                  std::make_unique<ConstantOperation>(value));
}

}  // namespace Operations
}  // namespace SimpleML

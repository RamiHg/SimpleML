#include "simpleml/operations/operations.h"

#include <memory>
#include <sstream>

#include "simpleml/graph.h"
#include "simpleml/operations/internal/add.h"
#include "simpleml/operations/internal/mul.h"
#include "simpleml/operations/internal/transpose.h"
#include "simpleml/variable.h"

namespace SimpleML {

static std::string NameOpVariable(std::string_view op_name) {
  std::stringstream name_stream;
  name_stream << op_name << "_" << Graph::Get().GetNumNodes();
  return name_stream.str();
}

auto Add(const VariableSPtr& lhs, const VariableSPtr& rhs,
         std::string_view name = nullptr) {
  const std::string final_name =
      name != nullptr ? std::string(name) : NameOpVariable("add");
  auto variable = std::make_shared<VariableNode>(
      final_name, std::make_unique<AddOperation>(lhs, rhs));
  Graph::Get().AddNode(variable);
  return variable;
}

auto Mul(const VariableSPtr& lhs, const VariableSPtr& rhs,
         std::string_view name = nullptr) {
  const std::string final_name =
      name != nullptr ? std::string(name) : NameOpVariable("mul");
  auto variable = std::make_shared<VariableNode>(
      final_name, std::make_unique<MulOperation>(lhs, rhs));
  Graph::Get().AddNode(variable);
  return variable;
}

VariableSPtr Transpose(const VariableSPtr& value,
                       std::string_view name = nullptr) {
  const std::string final_name =
      name != nullptr ? std::string(name) : NameOpVariable("transpose");
  auto variable = std::make_shared<VariableNode>(
      final_name, std::make_unique<TransposeOperation>(value));
  Graph::Get().AddNode(variable);
  return variable;
}
}  // namespace SimpleML
#pragma once

#include <memory>
#include <string_view>

#include "simpleml/graph.h"
#include "simpleml/operations/internal/operation.h"
#include "simpleml/variable.h"

namespace SimpleML {
namespace Operations {

VariableNode* Add(const VariableNode* lhs, const VariableNode* rhs,
                  std::string_view name = std::string_view(),
                  Graph& graph = Graph::GetDefaultGraph());
VariableNode* Mul(const VariableNode* lhs, const VariableNode* rhs,
                  std::string_view name = std::string_view(),
                  Graph& graph = Graph::GetDefaultGraph());
VariableNode* MatMul(const VariableNode* lhs, const VariableNode* rhs,
                     std::string_view name = std::string_view(),
                     Graph& graph = Graph::GetDefaultGraph());
VariableNode* Transpose(const VariableNode* value,
                        std::string_view name = std::string_view(),
                        Graph& graph = Graph::GetDefaultGraph());
VariableNode* Identity(const VariableNode* value,
                       std::string_view name = std::string_view(),
                       Graph& graph = Graph::GetDefaultGraph());
VariableNode* Variable(const Tensor& value,
                       std::string_view name = std::string_view(),
                       Graph& graph = Graph::GetDefaultGraph());
VariableNode* Constant(const Tensor& value,
                       std::string_view name = std::string_view(),
                       Graph& graph = Graph::GetDefaultGraph());
VariableNode* Gte(const VariableNode* lhs, const VariableNode* rhs,
                  std::string_view name = std::string_view(),
                  Graph& graph = Graph::GetDefaultGraph());
VariableNode* Where(const VariableNode* cond, const VariableNode* a,
                    const VariableNode* b,
                    std::string_view name = std::string_view(),
                    Graph& graph = Graph::GetDefaultGraph());
VariableNode* ReLU(const VariableNode* value,
                   std::string_view name = std::string_view(),
                   Graph& graph = Graph::GetDefaultGraph());
}  // namespace Operations
}  // namespace SimpleML

#pragma once

#include <memory>
#include <string_view>

#include "simpleml/graph.h"
#include "simpleml/math/tensor.h"
#include "simpleml/operations/internal/operation.h"
#include "simpleml/variable.h"

namespace SimpleML {
namespace Operations {

VariableNode* Add(const VariableNode* lhs, const VariableNode* rhs,

                  Graph& graph = Graph::GetDefaultGraph(),
                  std::string_view name = std::string_view());
VariableNode* Mul(const VariableNode* lhs, const VariableNode* rhs,

                  Graph& graph = Graph::GetDefaultGraph(),
                  std::string_view name = std::string_view());
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
                       Graph& graph = Graph::GetDefaultGraph(),
                       std::string_view name = std::string_view());
VariableNode* Gte(const VariableNode* lhs, const VariableNode* rhs,

                  Graph& graph = Graph::GetDefaultGraph(),
                  std::string_view name = std::string_view());
VariableNode* Where(const VariableNode* cond, const VariableNode* a,
                    const VariableNode* b,

                    Graph& graph = Graph::GetDefaultGraph(),
                    std::string_view name = std::string_view());
VariableNode* ReLU(const VariableNode* value,
                   std::string_view name = std::string_view(),
                   Graph& graph = Graph::GetDefaultGraph());
VariableNode* Pow(const VariableNode* base, const VariableNode* power,
                  Graph& graph = Graph::GetDefaultGraph(),
                  std::string_view name = std::string_view());
}  // namespace Operations
}  // namespace SimpleML

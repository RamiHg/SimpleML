#include "simpleml/layers/dense.h"

#include "simpleml/graph_util.h"
#include "simpleml/operations/operations.h"

namespace SimpleML {
namespace Layers {
VariableNode* DenseLayer(VariableNode* input, int width, Graph& graph,
                         std::string_view name) {
  const std::string final_name =
      GetUniqueNodeName(graph, name, "dense_layer_output");

  // ReLU(Wx + b)

  // Get the size of the last dimension of the input layer.
  const Shape& input_shape = input->GetOperation().GetResultShape();
  // TODO: Replace all these asserts with fatal errors.
  assert(input_shape.size() > 0);
  const int input_size = input_shape.back();
  assert(input_size > 0);

  // The weight matrix is of size [width, input_size].
  // TODO: Initialize.
  Tensor::shape_type weight_shape = {(uint32_t)width, (uint32_t)input_size};
  VariableNode* weight_matrix = Operations::Constant(
      Tensor{weight_shape, 1.}, graph, final_name + "_weight");

  // The bias is of size [width, 1]
  Tensor::shape_type bias_shape = {(uint32_t)width};
  VariableNode* bias =
      Operations::Constant(Tensor{bias_shape, 0.}, graph, final_name + "_bias");

  VariableNode* wx =
      Operations::MatMul(weight_matrix, input, final_name + "_matmul", graph);
  VariableNode* wxb = Operations::Add(wx, bias, graph, final_name + "_addbias");
  VariableNode* layer_value =
      Operations::ReLU(wxb, final_name + "_relu", graph);

  // That's it!
  return layer_value;
}

}  // namespace Layers
}  // namespace SimpleML

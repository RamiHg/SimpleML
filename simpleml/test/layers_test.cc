#include "gtest/gtest.h"

#include "simpleml/back_prop.h"
#include "simpleml/forward_prop.h"
#include "simpleml/graph.h"
#include "simpleml/graph_vis.h"
#include "simpleml/layers.h"
#include "simpleml/losses.h"
#include "simpleml/operations/operations.h"
#include "simpleml/variable.h"

namespace SimpleML {

using namespace Operations;

class LayersTest : public testing::Test {
 public:
  LayersTest() {
    // Reset the graph
    Graph::GetDefaultGraph().Reset();
  }
};

TEST_F(LayersTest, TestDenseLayer) {
  auto input_layer = Constant({1., 2., 3., 4.});
  auto dense_layer = Layers::DenseLayer(input_layer, 3);
  auto second_layer = Layers::DenseLayer(dense_layer, 2);
  auto labels = Constant({1., 2.});
  auto loss = Losses::MeanSquaredError(labels, second_layer);
  ForwardPropagate(Graph::GetDefaultGraph());
  std::unordered_map<std::string, VariableNode*> grad_table;
  auto back_prop_graph = CreateBackpropGraph(Graph::GetDefaultGraph(), loss, grad_table);
  SerializeGraphToDotFile(*back_prop_graph, "./testbackprop.dot");
  // SerializeGraphToDotFile(Graph::GetDefaultGraph(), "/tmp/testbackprop.dot");
  ForwardPropagate(*back_prop_graph);
}

}  // namespace SimpleML

#include "gtest/gtest.h"

#include "simpleml/back_prop.h"
#include "simpleml/forward_prop.h"
#include "simpleml/graph.h"
#include "simpleml/graph_vis.h"
#include "simpleml/operations/operations.h"
#include "simpleml/variable.h"
#include "simpleml/layers.h"

namespace SimpleML {

using namespace Operations;

class LayersTest : public testing::Test {
 public:
  LayersTest() {
    // Reset the graph
    Graph::GetDefaultGraph().Reset();
  }
};

#if 0
TEST_F(LayersTest, TestDenseLayer) {
  auto input_layer = Constant({1., 2., 3., 4.});
  auto dense_layer = Layers::DenseLayer(input_layer, 3);
  ForwardPropagate(Graph::GetDefaultGraph());
  auto back_prop_graph = CreateBackpropGraph(Graph::GetDefaultGraph(), dense_layer);
  SerializeGraphToDotFile(*back_prop_graph, "/tmp/testbackprop.dot");
  ForwardPropagate(*back_prop_graph);
}
#endif

}

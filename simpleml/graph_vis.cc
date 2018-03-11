#include "simpleml/graph_vis.h"

#include <fstream>
#include <sstream>
#include <string>

#include "simpleml/operations/internal/operation.h"

namespace SimpleML {
std::string SerializeGraphToDot(const Graph& graph) {
  auto nodes = graph.GetNodes();
  std::stringstream s;
  s << "digraph main_graph {" << std::endl;
  for (const auto& pair : nodes) {
    const auto& node = pair.second;
    s << "\t" << node->GetName() << std::endl;
    const auto& operation_inputs = node->GetOperation().GetInputs();
    for (const auto& input : operation_inputs) {
      s << "\t" << input->GetName() << " -> " << node->GetName()
        << "[label = \"" << node->GetOperation().GetName() << "\"]"
        << std::endl;
    }
  }
  s << "}" << std::endl;
  return s.str();
}

void SerializeGraphToDotFile(const Graph& graph, std::string_view filename) {
  std::ofstream f(std::string(filename), std::ofstream::out);
  assert(f.good());
  f << SerializeGraphToDot(graph);
  assert(f.good());
  f.close();
}
}  // namespace SimpleML

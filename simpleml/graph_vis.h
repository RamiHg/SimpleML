#pragma once

#include <string>
#include <string_view>

#include "simpleml/graph.h"

namespace SimpleML {
std::string SerializeGraphToDot(const Graph& graph);
void SerializeGraphToDotFile(const Graph& graph, std::string_view filename);
}  // namespace SimpleML

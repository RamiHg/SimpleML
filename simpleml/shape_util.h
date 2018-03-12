#pragma once

#include "simpleml/math/tensor.h"

namespace SimpleML {
bool CheckShapesMatch(const Tensor& tensor, const Shape& shape);
}

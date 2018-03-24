#pragma once

#include "xtensor/xarray.hpp"
#include "xtensor/xstrided_view.hpp"
#include "xtensor/xeval.hpp"

namespace SimpleML {

typedef xt::xarray<double> Tensor;
typedef std::vector<int> Shape;

template <typename T, size_t N>
inline bool SVectorsAreEqual(const xt::svector<T, N> &a,
                             const xt::svector<T, N> &b) {
  if (a.size() != b.size()) return false;
  for (auto i0 = a.cbegin(), i1 = b.cbegin(); i0 != a.cend() && i1 != b.cend();
       ++i0, ++i1) {
    if (*i0 != *i1) return false;
  }
  return true;
}

template <typename T>
inline Shape ShapeFromS(const xt::svector<T, 4> &svector) {
  Shape ret;
  ret.reserve(svector.size());
  for (auto val : svector) ret.push_back(val);
  return ret;
}
}  // namespace SimpleML

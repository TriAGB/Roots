//********************************
//        Roots Bisect method
//********************************
// author = "Andrei Poletimov"
// version = "1.0.0"
// license = "MIT"
// email = "pae1@gmx.at"
// status = "Education"
// date = "2018-03-18"
//********************************

#pragma once

#include "findrootresult.hpp"
#include <cmath>
#include <optional>

class Bisect {
public:
  Bisect(float eps, size_t iter_limit) : eps(eps), iter_limit(iter_limit) {}

  template <typename F>
  std::optional<FindRootResult> find_root(F &f, float xl, float xr) const {
    return find_root_internal(f, xl, xr, 0);
  }

private:
  template <typename F>
  std::optional<FindRootResult> find_root_internal(F &f, float xl, float xr,
                                                   size_t stepcount) const {
    const auto x = (xl + xr) / 2;
    const auto y = f(x);
    stepcount++;
    if (stepcount > iter_limit) {
      return {};
    }

    if (std::abs(y) < eps) {
      return FindRootResult{x, stepcount};
    }

    if (f(xl) * y < 0) {
      return find_root_internal(f, xl, x, stepcount);
    } else {
      stepcount++;
      return find_root_internal(f, x, xr, stepcount);
    }
  }

  const float eps;
  const size_t iter_limit;
};

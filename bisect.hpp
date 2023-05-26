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

class Bisect {
public:
  Bisect(float eps) : eps(eps) {}

  template <typename F>
  FindRootResult find_root(F &f, float xl, float xr) const {
    return find_root_internal(f, xl, xr, 0);
  }

private:
  template <typename F>
  FindRootResult find_root_internal(F &f, float xl, float xr,
                                    size_t stepcount) const {
    const auto x = (xl + xr) / 2;
    const auto y = f(x);
    stepcount++;
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
};

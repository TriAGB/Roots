//********************************
//        Roots Tangent method
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

class Tangent {
public:
  Tangent(float eps, size_t iter_limit) : eps(eps), iter_limit(iter_limit) {}

  template <typename F, typename DF>
  std::optional<FindRootResult> find_root(F f, DF df, float xn) const {
    return find_root_internal(f, df, xn, 0);
  }

private:
  template <typename F, typename DF>
  std::optional<FindRootResult> find_root_internal(F f, DF df, float xn,
                                                   size_t stepcount) const {
    float x1 = xn - f(xn) / df(xn);
    float x0 = xn;
    while (std::fabs(x0 - x1) > eps && stepcount < iter_limit) {
      x0 = x1;
      x1 = x1 - f(x1) / df(x1);
      stepcount++;
      if (stepcount > iter_limit) {
        return {};
      }
      return FindRootResult{x1, stepcount};
    };
  };

  const float eps;
  const size_t iter_limit;
};

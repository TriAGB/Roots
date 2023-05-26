//********************************
//        Roots Combine method
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

class Combine {
public:
  Combine(float eps) : eps(eps) {}

  template <typename F>
  FindRootResult find_root(F f, F df, F ddf, float xl, float xr) const {
    return find_root_internal(f, df, ddf, xl, xr, 0);
  }

private:
  template <typename F>
  FindRootResult find_root_internal(F f, F df, F ddf, float xl, float xr,
                                    size_t stepcount) const {
    while (fabs(xl - xr) > 2 * eps) {
      if (f(xl) * ddf(xl) < 0)
        xl = xl - (f(xl) * (xl - xr)) / (f(xl) - f(xr));
      else
        xl = xl - f(xl) / df(xl);
      if (f(xr) * ddf(xr) < 0)
        xr = xr - (f(xr) * (xr - xl)) / (f(xr) - f(xl));
      else
        xr = xr - f(xr) / df(xr);
      stepcount++;
    }
    return FindRootResult{(xl + xr) / 2, stepcount};
  };
  const float eps;
};

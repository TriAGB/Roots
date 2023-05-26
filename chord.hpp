//********************************
// 		Roots Chord method
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

class Chord {
public:
  Chord(float eps) : eps(eps) {}

  template <typename F>
  FindRootResult find_root(F f, float xl, float xr) const {
    return find_root_internal(f, xl, xr, 0);
  }

private:
  template <typename F>
  FindRootResult find_root_internal(F f, float xl, float xr,
                                    size_t stepcount) const {
    while (fabs(xr - xl) > eps) {
      xl = xr - (xr - xl) * f(xr) / (f(xr) - f(xl));
      xr = xl - (xl - xr) * f(xl) / (f(xl) - f(xr));
      stepcount++;
    }
    return FindRootResult{xr, stepcount};
  };
  const float eps;
};

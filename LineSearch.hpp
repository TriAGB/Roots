//********************************
//   Roots LinerSearch  method
//********************************
// author = "Andrei Poletimov"
// version = "1.0.0"
// license = "MIT"
// email = "pae1@gmx.at"
// status = "Education"
// date = "2018-03-18"
//********************************

#ifndef LINESEARCH_HPP
#define LINESEARCH_HPP

#include "findrootresult.hpp"
#include <cmath>

class LineSearch {
public:
  LineSearch(float eps) : eps(eps) {}

  template <typename F>
  FindRootResult find_root(F f, float xl, float xr) const {
    return find_root_internal(f, xl, xr, 0);
  }

private:
  template <typename F>
  FindRootResult find_root_internal(F f, float xl, float xr,
                                    size_t stepcount) const {
    float x;
    float minx = xl;
    const auto nextstep = fabs(xr - xl) / (1 / eps); //
    for (x = xl; x < xr; x += nextstep, stepcount++) {
      if (fabs(f(x)) < fabs(f(minx)))
        minx = x;
    }
    return FindRootResult{minx, stepcount};
  }
  const float eps;
};
#endif // LINESEARCH_HPP

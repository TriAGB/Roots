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

#ifndef BISECT_HPP
#define BISECT_HPP

#include "findrootresult.hpp"
#include <cmath>

class Bisect {
public:
  Bisect(float eps) : eps(eps) {}

  template <typename F> FindRootResult find_root(F f, float a, float b) const {
    return find_root_internal(f, a, b, 0);
  }

private:
  template <typename F>
  FindRootResult find_root_internal(F f, float a, float b,
                                    size_t stepcount) const {
    const auto x = (a + b) / 2;
    const auto y = f(x);
    stepcount++;
    if (std::abs(y) < eps) {
      return FindRootResult{x, stepcount};
    }

    if (f(a) * y < 0) {
      return find_root_internal(f, a, x, stepcount);
    } else {
      stepcount++;
      return find_root_internal(f, x, b, stepcount);
    }
  }

  const float eps;
};
#endif // BISECT_HPP

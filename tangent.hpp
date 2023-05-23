#ifndef TANGENT_HPP
#define TANGENT_HPP
#include "findrootresult.hpp"
#include <cmath>

class Tangent {
public:
  Tangent(float eps) : eps(eps) {}

  template <typename F> FindRootResult find_root(F f, F df, float xn) const {
    return find_root_internal(f, df, xn, 0);
  }

private:
  template <typename F>
  FindRootResult find_root_internal(F f, F df, float xn,
                                    size_t stepcount) const {
    float x1 = xn - f(xn) / df(xn);
    float x0 = xn;
    while (fabs(x0 - x1) > eps) {
      x0 = x1;
      x1 = x1 - f(x1) / df(x1);
      stepcount++;
    }
    return FindRootResult{x1, stepcount};
  };
  const float eps;
};
#endif // TANGENT_HPP

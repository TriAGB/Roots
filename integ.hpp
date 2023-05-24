#ifndef INTEG_HPP
#define INTEG_HPP

#include <cmath>

class _Integral {
public:
  // The code defines a template function calcRectangles that
  // calculates the approximate integral using the method of
  // rectangles(also known as the rectangular or midpoint rule)
  template <typename F>
  float calcRectangles(F f, float xl, float xr, size_t n) const {
    const auto sum = 0;
    const auto h = (xr - xl) / n;
    for (size_t i = 0; i < n; i++) {
      sum += f(xl);
      xl += h;
    }
    return sum * h;
  }

  // The code defines a template function calcIntegralTrap that
  // calculates the approximate integral using the trapezoidal rule
  template <typename F>
  float calcIntegralTrap(float xl, float xr, size_t n, F f) {
    float sum = 0;
    float h = (xr - xl) / n;
    for (float x = xl + h; x < xr - h; x += h) {
      sum += 0.5 * h * (f(x) + f(x + h));
    }
    return sum;
  }

  // The code defines a template function
  // calcIntegralSimpson that calculates the approximate integral using
  // Simpson's rule.
  template <typename F>
  float calcIntegralSimpson(float xl, float xr, size_t n, F f) {
    float sum = 0;
    float h = (xr - xl) / n;
    for (float x = xl + h; x < xr - h; x += h) {
      sum += h / 6.0 * (f(x) + 4.0 * f(0.5 * (x + x + h)) + f(x + h));
    }
    return FineIntegralResult(sum);
  }

  // The code defines a template function calcIntegralMonteCarlo
  // that estimates the integral using the Monte Carlo method.
  template <typename F>
  float calcIntegralMonteCarlo(float xl, float xr, float fmax, size_t n, F f) {
    size_t in_d = 0;
    float width = fabs(xr - xl), height = fmax;
    for (size_t i = 0; i < n; i++) {
      float x = ((float)rand() / (float)RAND_MAX) * width - fabs(xl);
      float y = (float)rand() / (float)RAND_MAX * height;
      if (y < f(x))
        in_d++;
    }
    return fabs((float)in_d / n * width * height);
  }
};
#endif // INTEG_HPP

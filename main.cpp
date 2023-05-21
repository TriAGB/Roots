#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdio.h>

using std::fabs;

float fn1(float x) { return 3 / x; }
float fn2(float x) { return 0.6 * x + 3; }
float fn3(float x) { return ((x - 2) * (x - 2) * (x - 2) - 1); }

class FindRoot {

public:
  int stepcount = 0;
  void message() {
    std::cout << "Find root for %d steps" << stepcount << std::endl;
  }

  void message(float x) { std::cout << "Root is: " << x << std::endl; }

  void input_EPS() {
    std::cout << "Input EPS: " << std::endl;
    std::cin >> eps;
  }

  template <typename F> float Bisect(F f, float a, float b) { // bisect method
    const auto x = (a + b) / 2;
    const auto y = f(x);
    if (std::abs(y) < eps) {
      stepcount++;
      std::cout << "Bisect " << stepcount << " steps" << std::endl
                << "Root =" << x << std::endl
                << std::endl;
      // message(x);
      return x;
    }
    if (f(a) * y < 0) {

      return Bisect(f, a, x);
    } else {
      stepcount++;
      return Bisect(f, x, b);
    }
  }
  template <typename F>
  float LineSearch(F f, float xl, float xr) { // line search method
    float x, minx = xl;
    const auto nextstep = fabs(xr - xl) / (1 / eps); //
    for (x = xl; x < xr; x += nextstep, stepcount++) {
      if (fabs(f(x)) < fabs(f(minx)))
        minx = x;
    }
    std::cout << "Liner " << stepcount << " steps" << std::endl
              << "Root =" << minx << std::endl
              << std::endl;
    return minx;
  }

  template <typename F> float Chord(F f, float xl, float xr) {
    while (fabs(xr - xl) > eps) {
      xl = xr - (xr - xl) * f(xr) / (f(xr) - f(xl));
      xr = xl - (xl - xr) * f(xl) / (f(xl) - f(xr));
      stepcount++;
    }
    std::cout << "Chord " << stepcount << " steps" << std::endl
              << "Root =" << xr << std::endl
              << std::endl;
    return xr;
  }

private:
  float eps = 0.0;
};

int main() {

  FindRoot roots;
  roots.input_EPS();
  roots.message();
  printf("\033[100;92m"
         "\033[0;0H"
         "\033[2J");
  roots.Bisect(fn3, -10, 10);
  roots.LineSearch(fn3, -10, 10);
  roots.Chord(fn3, -10, 10);
  //   printf("\033[0;0m\n");
  //   roots.findRoot(fn1, -10, 10, 0.0001);
  //   roots.findRoot(fn2, -10, 10, 0.0001);
  //   roots.findRoot(fn3, -10, 10, 0.0001);

  return 0;
}

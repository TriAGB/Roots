#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>

#include "LineSearch.hpp"
#include "bisect.hpp"
#include "chord.hpp"
#include "combine.hpp"
#include "function_choice.hpp"
#include "integ.hpp"
#include "readfromfile.hpp"
#include "tangent.hpp"
#include <iterator>
#include <string>

using std::cout;
using std::endl;
using std::fabs;
using std::string;

float xl = -2.0;
float xr = -1.8;
const size_t iter_limit = 100000;

class FindRoot {
private:
  static int stepcount; // step count
public:
  int n = 10000;      // number of steps
  float eps = 0.0001; // accuracy

  struct Method { // method struct
    string bisect = "_BISECT ";
    string linesearch = "_LINE_SEARCH ";
    string chord = "_CHORD ";
    string tangent = "_TANGENT ";
    string combine = "_COMBINE ";
    /*__________________________*/
    string rectangles = "_RECTANGLES ";
    string integralTrap = "_INTEGRAL_TRAP ";
    string integralSimpson = "_INTEGRAL_SIMPSON ";
    string integralMonteCarlo = "_INTEGRAL_MONTE_CARLO ";
  };

  Method methods; // method

  void input_EPS() {
    std::cout << "Input accuracy calculation ROOT EPS (or press Enter to use "
                 "default esp=0.0001): ";
    std::string input;
    std::getline(std::cin, input);
    if (!input.empty()) {
      eps = std::stof(input);
    }
    std::cout << "Using EPS value: " << eps << std::endl;
  }
};

std::ostream &operator<<(std::ostream &os, const FindRoot &root) {
  os << "Find ";
  return os;
}

int main() {
  input_interval();
  FindRoot roots;
  _Integral integral;
  roots.input_EPS();

  FunctionSelector functionSelector;
  std::function<float(float)> selectedFunction = functionSelector.run();

  // Color print
  printf("\033[100;92m"
         "\033[0;0H"
         "\033[2J");

  /*************Root calculation*************/

  std::cout << "*****Searching ROOTS******" << std::endl << std::endl;

  // The function bisection method
  const Bisect bisect(roots.eps, iter_limit);
  const auto result_bisect = bisect.find_root(selectedFunction, xl, xr);
  if (result_bisect.has_value()) {
    std::cout << roots << roots.methods.bisect << result_bisect->result
              << " after " << result_bisect->stepcount << " iterations"
              << std::endl;
  } else {
    std::cout << roots << roots.methods.bisect << " can't find roots after "
              << iter_limit << " iterations" << std::endl;
  }

  // The function line search method
  const LineSearch linesearch(roots.eps, iter_limit);
  const auto result_linesearch = linesearch.find_root(selectedFunction, xl, xr);
  if (result_linesearch.has_value()) {
    std::cout << roots << roots.methods.linesearch << result_linesearch->result
              << " after " << result_linesearch->stepcount << " iterations"
              << std::endl;
  } else {
    std::cout << roots << roots.methods.bisect << " can't find roots after "
              << iter_limit << " iterations" << std::endl;
  }

  // The function chord method
  const Chord chord(roots.eps, iter_limit);
  const auto result_chord = chord.find_root(selectedFunction, xl, xr);
  if (result_chord.has_value()) {
    std::cout << roots << roots.methods.chord << result_chord->result
              << " after " << result_chord->stepcount << " iterations"
              << std::endl;
  } else {
    std::cout << roots << roots.methods.chord << " can't find roots after "
              << iter_limit << " iterations" << std::endl;
  }

  // The function tangent method
  const Tangent tangent(roots.eps, iter_limit);
  const auto result_tangent = tangent.find_root(selectedFunction, df, xl);

  if (result_tangent.has_value()) {
    std::cout << roots << roots.methods.tangent << result_tangent->result
              << " after " << result_tangent->stepcount << " iterations"
              << std::endl;
  } else {
    std::cout << roots << roots.methods.tangent << " can't find roots after "
              << iter_limit << " iterations" << std::endl;
  }

  // The function tangent method
  const Combine combine(roots.eps, iter_limit);
  const auto result_combine =
      combine.find_root(selectedFunction, df, ddf, xl, xr);

  // The function Newton method
  if (result_combine.has_value()) {
    std::cout << roots << roots.methods.combine << result_combine->result
              << " after " << result_combine->stepcount << " iterations"
              << std::endl;
  } else {
    std::cout << roots << roots.methods.combine << " can't find roots after "
              << iter_limit << " iterations" << std::endl
              << std::endl;
    ;
  }

  /************ Integral calculation*************/

  std::cout << "*****Searching INTEGRAL******" << std::endl << std::endl;
  // The code function calcRectangles
  const auto result_calcRectangles =
      integral.calcRectangles(selectedFunction, xl, xr, roots.n);
  std::cout << roots << roots.methods.rectangles
            << result_calcRectangles.result_integral << " [" << xl << ":" << xr
            << "]" << std::endl;

  // The code function calcIntegralTrap
  const auto result_calcIntegralTrap =
      integral.calcIntegralTrap(selectedFunction, xl, xr, roots.n);
  std::cout << roots << roots.methods.integralTrap
            << result_calcIntegralTrap.result_integral << " [" << xl << ":"
            << xr << "]" << std::endl;

  // The code function calcIntegralSimpson
  const auto result_calcIntegralSimpsonp =
      integral.calcIntegralSimpson(selectedFunction, xl, xr, roots.n);
  std::cout << roots << roots.methods.integralSimpson
            << result_calcIntegralSimpsonp.result_integral << " [" << xl << ":"
            << xr << "]" << std::endl;

  // The code function calcIntegralMonteCarlo
  const auto result_calcIntegralMonteCarlo =
      integral.calcIntegralMonteCarlo(selectedFunction, xl, xr, 0, roots.n);
  std::cout << roots << roots.methods.integralMonteCarlo
            << result_calcIntegralMonteCarlo.result_integral << " [" << xl
            << ":" << xr << "]" << std::endl
            << std::endl;
}

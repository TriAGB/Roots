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
#include "command_line_parser.hpp"
#include "function_choice.hpp"
#include "integ.hpp"
#include "readfromfile.hpp"
#include "tangent.hpp"
#include <iterator>

using std::cin;
using std::cout;
using std::endl;
using std::fabs;
using std::string;

const size_t iter_limit = 100000;

// Class to store root finding parameters and methods
class FindRoot {
private:
  static int stepcount; // // Variable to track the step count
public:
  int n = 10000;      // Number of steps for integral calculations
  float eps = 0.0001; // Accuracy for root calculations

  // Struct to store the names of different root finding methods
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

  Method methods; // Object to access the method names

  // Function to input the accuracy (EPS) for root calculations
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

  // Function to input the interval for root calculations
  // void input_interval() {
  //   cout << "Enter the interval for root calculations:" << endl;
  //   cout << "Lower bound (xl): ";
  //   cin >> xl;
  //   cout << "Upper bound (xr): ";
  //   cin >> xr;
  // }
};

// Overloading the stream insertion operator for FindRoot class
std::ostream &operator<<(std::ostream &os, const FindRoot &root) {
  os << "Find ";
  return os;
}

int main(int argc, char *argv[]) {
  const CommandLineParser commandLineParser(argc, argv);
  if (!commandLineParser.is_valid()) {
    commandLineParser.print_help();
    return 1;
  }
  if (commandLineParser.is_help()) {
    commandLineParser.print_help();
    return 0;
  }

  float xl = 0;
  float xr = 0;
  input_interval(xl, xr);
  FindRoot roots;
  _Integral integral;
  roots.input_EPS();

  FunctionSelector functionSelector;
  std::function<float(float)> selectedFunction = functionSelector.run();

  // Formatting for colored output
  printf("\033[100;92m"
         "\033[0;0H"
         "\033[2J");

  /*************Root calculation*************/

  std::cout << "*****Searching ROOTS******" << std::endl << std::endl;

  // Bisection method
  const Bisect bisect(roots.eps, iter_limit);
  const auto result_bisect = bisect.find_root(selectedFunction, xl, xr);
  if (result_bisect.has_value()) {
    if (commandLineParser.print_roots()) {
      std::cout << roots << roots.methods.bisect << result_bisect->result
                << " [" << xl << ":" << xr << "]";
      if (commandLineParser.print_iteration_count()) {
        std::cout << " after " << result_bisect->stepcount << " iterations";
      }
      std::cout << endl;
    }

  } else {
    std::cout << roots << roots.methods.bisect << " can't find roots after "
              << iter_limit << " iterations" << std::endl;
  }

  // Line search method
  const LineSearch linesearch(roots.eps, iter_limit);
  const auto result_linesearch = linesearch.find_root(selectedFunction, xl, xr);
  if (result_linesearch.has_value()) {
    std::cout << roots << roots.methods.linesearch << result_linesearch->result
              << " [" << xl << ":" << xr << "]"
              << " after " << result_linesearch->stepcount << " iterations"
              << std::endl;
  } else {
    std::cout << roots << roots.methods.bisect << " can't find roots after "
              << iter_limit << " iterations" << std::endl;
  }

  // Chord method
  const Chord chord(roots.eps, iter_limit);
  const auto result_chord = chord.find_root(selectedFunction, xl, xr);
  if (result_chord.has_value()) {
    std::cout << roots << roots.methods.chord << result_chord->result << " ["
              << xl << ":" << xr << "]"
              << " after " << result_chord->stepcount << " iterations"
              << std::endl;
  } else {
    std::cout << roots << roots.methods.chord << " can't find roots after "
              << iter_limit << " iterations" << std::endl;
  }

  // Tangent method
  const Tangent tangent(roots.eps, iter_limit);
  const auto result_tangent = tangent.find_root(selectedFunction, df, xl);

  if (result_tangent.has_value()) {
    std::cout << roots << roots.methods.tangent << result_tangent->result
              << " [" << xl << ":" << xr << "]"
              << " after " << result_tangent->stepcount << " iterations"
              << std::endl;
  } else {
    std::cout << roots << roots.methods.tangent << " can't find roots after "
              << iter_limit << " iterations" << std::endl;
  }

  // Combine method (Newton method)
  const Combine combine(roots.eps, iter_limit);
  const auto result_combine =
      combine.find_root(selectedFunction, df, ddf, xl, xr);
  if (result_combine.has_value()) {
    std::cout << roots << roots.methods.combine << result_combine->result
              << " [" << xl << ":" << xr << "]"
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

  // Rectangles method
  const auto result_calcRectangles =
      integral.calcRectangles(selectedFunction, xl, xr, roots.n);
  std::cout << roots << roots.methods.rectangles
            << result_calcRectangles.result_integral << " [" << xl << ":" << xr
            << "]" << std::endl;

  // Integral Trap method
  const auto result_calcIntegralTrap =
      integral.calcIntegralTrap(selectedFunction, xl, xr, roots.n);
  std::cout << roots << roots.methods.integralTrap
            << result_calcIntegralTrap.result_integral << " [" << xl << ":"
            << xr << "]" << std::endl;

  // Integral Simpson method
  const auto result_calcIntegralSimpsonp =
      integral.calcIntegralSimpson(selectedFunction, xl, xr, roots.n);
  std::cout << roots << roots.methods.integralSimpson
            << result_calcIntegralSimpsonp.result_integral << " [" << xl << ":"
            << xr << "]" << std::endl;

  // Integral Monte Carlo method
  const auto result_calcIntegralMonteCarlo =
      integral.calcIntegralMonteCarlo(selectedFunction, xl, xr, 0, roots.n);
  std::cout << roots << roots.methods.integralMonteCarlo
            << result_calcIntegralMonteCarlo.result_integral << " [" << xl
            << ":" << xr << "]" << std::endl
            << std::endl;
}

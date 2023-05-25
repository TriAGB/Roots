#include "main.hpp"
#include <string>

using std::cout;
using std::endl;
using std::fabs;
using std::string;

float fn1(float x) { return 3 / x; }
float fn2(float x) { return 0.6 * x + 3; }
float fn3(float x) { return ((x - 2) * (x - 2) * (x - 2) - 1); }
float fn4(float x) { return (x * x * x - 2 * x * x + 3 * x - 1); }
float_t fn5(float_t x) {
  return (8 * x * x * x * x + 32 * x * x * x + 40 * x * x + 16 * x + 1);
}
float fn6(float x) { // прямая и кривая 3-го порядка
  return ((0.6 * x + 3) - ((x - 2) * (x - 2) * (x - 2) - 1));
}
float fn7(float x) { // прямая и гипербола
  return (((x - 2) * (x - 2) * (x - 2) - 1) - (3 / x));
}

float df(float x) { return 32 * x * x * x + 96 * x * x + 80 * x + 16; }

float ddf(float x) { return 96 * x * x + 192 * x + 80; }

class FindRoot {

private:
  char str[30]; // string

  static int stepcount; // step count

  ;

public:
  int n = 10000;      // number of steps
  float eps = 0.0001; // accuracy
  float xl = -5.854;
  float xr = -0.244;

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

  FindRoot() { // FindRoot() = default;
    for (int i = 0; i <= 30; i++)
      str[i] = '\0';
  }

  friend std::ostream &operator<<(std::ostream &os, const FindRoot &root) {
    os << "Find ";
    return os;
  }

  void getStr() { // get string
    std::cout << str << std::endl << std::endl;
  }

  void message() {               // message
    std::string messageStr(str); // convert char* to string
    std::cout << messageStr << this->stepcount << " steps" << std::endl;
  }

  void message(float x) {
    std::cout << "Root is: " << x << std::endl << std::endl;
  }

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

  // The code defines a template function calcRectangles that
  // calculates the approximate integral using the method of
  // rectangles(also known as the rectangular or midpoint rule)
  template <typename F>
  float calcRectangles(F f, float xl, float xr, size_t n) const {
    float sum = 0;
    float h = (xr - xl) / n;
    for (size_t i = 0; i < n; i++) {
      sum += f(xl);
      xl += h;
    }
    return (sum * h);
  }

  // The code defines a template function calcIntegralTrap that
  // calculates the approximate integral using the trapezoidal rule
  template <typename F>
  float calcIntegralTrap(F f, float xl, float xr, size_t n) {
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
  float calcIntegralSimpson(F f, float xl, float xr, size_t n) {
    float sum = 0;
    float h = (xr - xl) / n;
    for (float x = xl + h; x < xr - h; x += h) {
      sum += h / 6.0 * (f(x) + 4.0 * f(0.5 * (x + x + h)) + f(x + h));
    }
    return sum;
  }

  // The code defines a template function calcIntegralMonteCarlo
  // that estimates the integral using the Monte Carlo method.
  template <typename F>
  float calcIntegralMonteCarlo(F f, float xl, float xr, float fmax, size_t n) {
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

int FindRoot::stepcount = 0;

int main() {

  FindRoot roots;
  roots.input_EPS();

  // Color print
  printf("\033[100;92m"
         "\033[0;0H"
         "\033[2J");

  /*************Root calculation*************/

  std::cout << "*****Searching ROOTS******" << std::endl;

  // The function bisection method
  const Bisect bisect(roots.eps);
  const auto result_bisect = bisect.find_root(fn7, -1, 0);
  std::cout << roots << roots.methods.bisect << result_bisect.result
            << " after " << result_bisect.stepcount << " iterations"
            << std::endl;

  // The function line search method
  const LineSearch linesearch(roots.eps);
  const auto result_linesearch = linesearch.find_root(fn7, -1, 0);
  std::cout << roots << roots.methods.linesearch << result_linesearch.result
            << " after " << result_linesearch.stepcount << " iterations"
            << std::endl;

  // The function chord method
  const Chord chord(roots.eps);
  const auto result_chord = chord.find_root(fn7, -1, 0);
  std::cout << roots << roots.methods.chord << result_chord.result << " after "
            << result_chord.stepcount << " iterations" << std::endl;

  // The function tangent method
  const Tangent tangent(roots.eps);
  const auto result_tangent = tangent.find_root(fn7, df, -1);
  std::cout << roots << roots.methods.tangent << result_tangent.result
            << " after " << result_tangent.stepcount << " iterations"
            << std::endl;

  // The function Newton method
  const Combine combine(roots.eps);
  const auto result_combine = combine.find_root(fn7, df, ddf, -1, 0);
  std::cout << roots << roots.methods.combine << result_combine.result
            << " after " << result_combine.stepcount << " iterations"
            << std::endl
            << std::endl;

  /************ Integral calculation*************/

  std::cout << "*****Searching INTEGRAL******" << std::endl;
  // The code function calcRectangles
  const auto result_calcRectangles =
      roots.calcRectangles(fn1, roots.xl, roots.xr, roots.n);
  std::cout << roots << roots.methods.rectangles << result_calcRectangles
            << " [" << roots.xl << ":" << roots.xr << "]" << std::endl;

  // The code function calcIntegralTrap
  const auto result_calcIntegralTrap =
      roots.calcIntegralTrap(fn1, roots.xl, roots.xr, roots.n);
  std::cout << roots << roots.methods.integralTrap << result_calcIntegralTrap
            << " [" << roots.xl << ":" << roots.xr << "]" << std::endl;

  // The code function calcIntegralSimpson
  const auto result_calcIntegralSimpsonp =
      roots.calcIntegralSimpson(fn1, roots.xl, roots.xr, roots.n);
  std::cout << roots << roots.methods.integralSimpson
            << result_calcIntegralSimpsonp << " [" << roots.xl << ":"
            << roots.xr << "]" << std::endl;

  // The code function calcIntegralMonteCarlo
  const auto result_calcIntegralMonteCarlo =
      roots.calcIntegralMonteCarlo(fn1, roots.xl, roots.xr, 0, roots.n);
  std::cout << roots << roots.methods.integralMonteCarlo
            << result_calcIntegralMonteCarlo << " [" << roots.xl << ":"
            << roots.xr << "]" << std::endl;
}

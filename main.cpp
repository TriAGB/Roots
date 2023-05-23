#include "main.hpp"

using std::cout;
using std::endl;
using std::fabs;
using std::string;

float fn1(float x) { return 3 / x; }
float fn2(float x) { return 0.6 * x + 3; }
float fn3(float x) { return ((x - 2) * (x - 2) * (x - 2) - 10); }
float fn4(float x) { return (x * x * x - 2 * x * x + 3 * x - 1); }
float_t fn5(float_t x) {
  return (8 * x * x * x * x + 32 * x * x * x + 40 * x * x + 16 * x + 1);
}

float df(float x) { return 32 * x * x * x + 96 * x * x + 80 * x + 16; }

float ddf(float x) { return 96 * x * x + 192 * x + 80; }

class FindRoot {

private:
  char str[30]; // string
  float eps = 0.001;
  static int stepcount; // step count

  typedef struct { // method struct
    string b = "_Bisect";
    string l = "_LineSearch";
    string C = "_Chord";
    string t = "_Tangent";
    string c = "_Combine";
  } Method;

public:
  Method methods; // method

  FindRoot() { // FindRoot() = default;
    for (int i = 0; i <= 30; i++)
      str[i] = '\0';
  }
  void operator+(const std::string &method) {
    if (method.empty())
      return;

    const char *methodStr = nullptr;

    switch (method[0]) {
    case 'b':
      methodStr = methods.b.c_str();
      break;
    case 'l':
      methodStr = methods.l.c_str();
      break;
    case 'C':
      methodStr = methods.c.c_str();
      break;
    case 't':
      methodStr = methods.t.c_str();
      break;
    case 'c':
      methodStr = methods.c.c_str();
      break;
    }

    if (methodStr != nullptr)
      strcat_s(str, methodStr);
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
    std::cout << "Input EPS: " << std::endl;
    std::cin >> eps;
  }
};

int FindRoot::stepcount = 0;

int main() {

  FindRoot roots;
  // roots.input_EPS();

  printf("\033[100;92m"
         "\033[0;0H"
         "\033[2J");

  const Bisect bisect(0.0000001);
  const auto result_bisect = bisect.find_root(fn3, -10, 10);
  std::cout << "BISECT: " << result_bisect.result << " after "
            << result_bisect.stepcount << " iterations" << std::endl;
  const LineSearch linesearch(0.0000001);
  const auto result_linesearch = linesearch.find_root(fn3, -10, 10);
  std::cout << "LINESEARCH: " << result_linesearch.result << " after "
            << result_linesearch.stepcount << " iterations" << std::endl;
  const Chord chord(0.00001);
  const auto result_chord = chord.find_root(fn3, -10, 10);
  std::cout << "CHORD: " << result_chord.result << " after "
            << result_chord.stepcount << " iterations" << std::endl;
  const Tangent tangent(0.0000001);
  const auto result_tangent = tangent.find_root(fn3, df, 10);
  std::cout << "TANGENT: " << result_tangent.result << " after "
            << result_tangent.stepcount << " iterations" << std::endl;
  const Combine combine(0.0000001);
  const auto result_combine = combine.find_root(fn3, df, ddf, -10, 10);
  std::cout << "COMBINE: " << result_combine.result << " after "
            << result_combine.stepcount << " iterations" << std::endl;
}

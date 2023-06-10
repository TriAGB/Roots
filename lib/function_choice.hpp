//**************************************
//   Function choice
//**************************************
// author = "Andrei Poletimov"
// version = "1.0.0"
// license = "MIT"
// email = "pae1@gmx.at"
// status = "Education"
// date = "2018-03-18"
//*************************************

#pragma once
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

inline float df(float x) { return 32 * x * x * x + 96 * x * x + 80 * x + 16; }
inline float ddf(float x) { return 96 * x * x + 192 * x + 80; }

class FunctionSelector {
public:
  std::string selectedFunctionKey;
  FunctionSelector() {
    // Add functions to the selection list here
    functions_["fn1"] = [](float x) { return 3 / x; };
    functions_["fn2"] = [](float x) { return 0.6 * x + 3; };
    functions_["fn3"] = [](float x) { return std::pow((x - 2), 3) - 1; };
    functions_["fn4"] = [](float x) {
      return std::pow(x, 3) - 2 * std::pow(x, 2) + 3 * x - 1;
    };
    functions_["fn5"] = [](float x) {
      return 8 * std::pow(x, 4) + 32 * std::pow(x, 3) + 40 * std::pow(x, 2) +
             16 * x + 1;
    };
    functions_["fn6"] = [](float x) { return (0.6 * x + 3) - (3 / x); };
    functions_["fn7"] = [](float x) {
      return (std::pow((x - 2), 3) - 1) - (3 / x);
    };
  }

  std::function<float(float)> getFnuction(const std::string &key) {
    std::cout << "Return function by key='" << key << "'" << std::endl;
    auto it = functions_.find(key);
    if (it != functions_.end()) {
      return it->second;
    }
    // Return an empty function if the key is not found
    return nullptr;
  }

  void displayMenu() const {
    std::cout << std::endl;
    std::cout << "************Available functions:***************" << std::endl;
    std::cout << "fn1 = 3/x" << std::endl;
    std::cout << "fn2 = 0.6 * x + 3" << std::endl;
    std::cout << "fn3 = (x - 2)^ 3 - 1" << std::endl;
    std::cout << "fn4 = x^3-2x^2+3x-1" << std::endl;
    std::cout << "fn5 = 8x^4+32x^3+40x^2+16x+1" << std::endl;
    std::cout << "fn6 = 0.6x+3-3/x" << std::endl;
    std::cout << "fn7 = (x-2)^3-3/x-1" << std::endl;
    std::cout << std::endl;
  }

  std::function<float(float)> run() {
    displayMenu();

    std::cout << "Select a function (enter the corresponding key fn1-fn7):"
              << std::endl;
    std::cin >> selectedFunctionKey;

    // Get the selected function
    std::function<float(float)> selectedFunction =
        getFunction(selectedFunctionKey);
    if (selectedFunction) {
      return selectedFunction;
    } else {
      // Return an empty function if the selected function is not found
      return nullptr;
    }
  }

private:
  std::map<std::string, std::function<float(float)>> functions_;
};

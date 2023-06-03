//*****************************************
//        Input DATA from file or STDIN
//*****************************************
// author = "Andrei Poletimov"
// version = "1.0.0"
// license = "MIT"
// email = "pae1@gmx.at"
// status = "Education"
// date = "2018-03-18"
//****************************************
#pragma once

#include <fstream>
#include <iostream>
#include <istream>
#include <ostream>
#include <vector>

class NumberReader {
public:
  NumberReader(std::istream &stream) : stream(stream) {}

  void readNumbers(std::vector<float> &numbers) {
    float num;
    while (stream >> num) {
      numbers.push_back(num);

      if (!(stream >> std::ws))
        break;
    }
  }

private:
  std::istream &stream;
};

inline void input_interval(float &xl, float &xr) {
  const std::string input_file =
      "input_interval.txt"; // Specify the file name here
  std::vector<float> numbers;

  auto stream = std::fstream(input_file);
  auto reader = NumberReader(stream);
  reader.readNumbers(numbers);

  // Print the read numbers
  std::cout << std::endl
            << "***********Read interval from file************" << std::endl
            << "Read numbers: " << std::endl;
  for (const auto &number : numbers) {
    std::cout << number << " ";
  }
  std::cout << std::endl;

  if (numbers.size() != 2) {
    std::cout << "Error: input file must contain 2 numbers" << std::endl;
    exit(1);
  }
  xl = numbers[0];
  xr = numbers[1];
}

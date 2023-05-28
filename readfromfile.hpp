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
#include <vector>

class NumberReader {
public:
  NumberReader(const NumberReader &) = default;
  NumberReader(NumberReader &&) = default;
  NumberReader &operator=(const NumberReader &) = delete;
  NumberReader &operator=(NumberReader &&) = delete;
  NumberReader(std::istream &stream) : stream(stream) {}

  bool readNumbers(std::vector<int> &numbers) {
    int num;
    while (stream >> num) {
      numbers.push_back(num);
    }
    return true;
  }

private:
  std::istream &stream;
};

inline void input_interval() {
  const std::string input_file =
      "input_interval.txt"; // Specify the file name here
  std::vector<int> numbers;

  auto stream = std::fstream(input_file);
  if (!stream || stream.peek() == std::ifstream::traits_type::eof()) {
    // If the file fails to open or is empty, fall back to standard input
    std::cout << "Enter numbers: ";
    auto reader = NumberReader(std::cin);
    reader.readNumbers(numbers);
  } else {
    auto reader = NumberReader(stream);
    reader.readNumbers(numbers);
  }

  // Print the read numbers
  std::cout << "Read numbers: ";
  for (const auto &number : numbers) {
    std::cout << number << " ";
  }
  std::cout << std::endl;
}

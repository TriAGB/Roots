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
  NumberReader(std::istream &stream) : stream(stream) {}

  bool readNumbers(std::vector<int> &numbers) {
    // std::ifstream inputFile(filename);
    // if (!stream) {
    //   std::cerr << "Failed to open the file." << std::endl;
    //   return false;
    // }

    int num;
    while (stream >> num) {
      numbers.push_back(num);
    }

    // inputFile.close();
    return true;
  }

private:
  std::istream &stream;
};

// void foo() {
//   const std::string input_file = get_from_cli_args();
//   std::vector<int> numbers;

//   if (input_file.empty()) {
//     std::cout << "Enter numbers: ";
//     auto reader = NumberReader(std::cin);
//     reader.readNumbers(numbers);
//   } else {
//     auto stream = std::fstream("a.txt");
//     if (!stream) {
//       // error
//     }

//     auto reader = NumberReader(stream);
//     reader.readNumbers(numbers);
//   }

// }

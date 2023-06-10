#pragma once

#include <string>
#include <vector>

class CommandLineParser {
public:
  explicit CommandLineParser(int argc, char *argv[]);

  bool is_valid() const;

  bool is_help() const;
  void print_help() const;

  bool print_roots() const;
  bool print_iteration_count() const;

private:
  const std::vector<std::string> args;
};

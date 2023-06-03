#pragma once

class CommandLineParser {
public:
  CommandLineParser(int argc, char *argv[]);

  bool is_valid() const;

  bool is_help() const;
  void print_help() const;

  bool print_roots() const;
  bool print_iteration_count() const;
};

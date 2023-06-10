#include "./command_line_parser.hpp"

#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <ostream>
#include <ranges>

constexpr auto HELP_PARAM = "--help";
constexpr auto PRINT_ROOTS_PARAM = "--print-roots";
constexpr auto PRINT_ITERATIONS_PARAM = "--print-iterations";
constexpr auto ALLOWED_PARAMS = {HELP_PARAM, PRINT_ROOTS_PARAM,
                                 PRINT_ITERATIONS_PARAM};

CommandLineParser::CommandLineParser(int argc, char *argv[])
    : args(argv, argv + argc) {}

bool CommandLineParser::is_valid() const {
  if (args.empty()) {
    return false;
  }

  const std::ranges::subrange args_without_app(args.begin() + 1, args.end());
  for (const auto &arg : args_without_app) {
    if (std::ranges::find(ALLOWED_PARAMS, arg) ==
        std::ranges::end(ALLOWED_PARAMS)) {
      return false;
    }
  }

  if (is_help() && (print_roots() || print_iteration_count())) {
    return false;
  }

  if (!print_roots() && print_iteration_count()) {
    return false;
  }

  return true;
}

bool CommandLineParser::is_help() const {
  return std::ranges::find(args, HELP_PARAM) != std::ranges::end(args);
}

void CommandLineParser::print_help() const {
  std::cout << "Usage: " << std::endl
            << args[0] << " [" << HELP_PARAM << "] [" << PRINT_ROOTS_PARAM
            << " [" << PRINT_ITERATIONS_PARAM << "]]" << std::endl
            << std::endl
            << HELP_PARAM << ":\t Prings this help page" << std::endl
            << PRINT_ROOTS_PARAM << ":\t Prints found roots" << std::endl
            << PRINT_ITERATIONS_PARAM << ":\t Prints amount of iterations"
            << std::endl;
}

bool CommandLineParser::print_roots() const {
  return std::ranges::find(args, PRINT_ROOTS_PARAM) != std::ranges::end(args);
}

bool CommandLineParser::print_iteration_count() const {
  return std::ranges::find(args, PRINT_ITERATIONS_PARAM) !=
         std::ranges::end(args);
}

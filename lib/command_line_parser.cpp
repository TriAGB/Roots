#include "./command_line_parser.hpp"

#include <iostream>

CommandLineParser::CommandLineParser(int argc, char *argv[]) {}

bool CommandLineParser::is_valid() const { return true; }

bool CommandLineParser::is_help() const { return true; }
void CommandLineParser::print_help() const {
  std::cout << "Usage: " << std::endl;
}

bool CommandLineParser::print_roots() const { return false; }
bool CommandLineParser::print_iteration_count() const { return false; }

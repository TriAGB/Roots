#include "command_line_parser.hpp"
#include <gtest/gtest.h>

TEST(CommandLineParserTest, IsHelp) {
  char *argv[] = {"./test", "--help"};
  const CommandLineParser sut(2, argv);
  EXPECT_TRUE(sut.is_valid());
  EXPECT_TRUE(sut.is_help());
  EXPECT_FALSE(sut.print_roots());
  EXPECT_FALSE(sut.print_iteration_count());
};

#include "command_line_parser.hpp"
#include <algorithm>

#include <gtest/gtest.h>
#include <sstream>

struct TestParam {
  std::vector<std::string> args;
  bool is_valid;
  bool is_help;
  bool print_roots;
  bool print_iteration_count;
};

void PrintTo(const TestParam &param, std::ostream *out) {
  for (const auto &arg : param.args) {
    *out << arg << ' ';
  }
}

struct CommandLineParserTestFixture : ::testing::TestWithParam<TestParam> {};

TEST_P(CommandLineParserTestFixture, ParamsTests) {
  auto param = GetParam();
  param.args.insert(param.args.begin(), "./test.exe");
  std::vector<const char *> cargs(param.args.size());
  std::transform(param.args.begin(), param.args.end(), cargs.begin(),
                 [](const auto &v) { return v.c_str(); });

  const CommandLineParser sut(param.args.size(),
                              const_cast<char **>(cargs.data()));
  EXPECT_EQ(sut.is_valid(), param.is_valid);
  EXPECT_EQ(sut.is_help(), param.is_help);
  EXPECT_EQ(sut.print_roots(), param.print_roots);
  EXPECT_EQ(sut.print_iteration_count(), param.print_iteration_count);
}

INSTANTIATE_TEST_SUITE_P(
    ParamsTests, CommandLineParserTestFixture,
    ::testing::Values(
        TestParam{{}, true, false, false, false},
        TestParam{{"--help"}, true, true, false, false},
        TestParam{{"--print-roots"}, true, false, true, false},
        TestParam{{"--print-iterations"}, false, false, false, true},
        TestParam{
            {"--print-roots", "--print-iterations"}, true, false, true, true},
        TestParam{{"--print-roots", "--help"}, false, true, true, false},
        TestParam{{"--print-roots", "--help", "--print-iterations"},
                  false,
                  true,
                  true,
                  true},
        TestParam{{"--invalid-arg"}, false, false, false, false}));

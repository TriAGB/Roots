#include "chord.hpp"
#include <gtest/gtest.h>
#include <vcruntime.h>

TEST(ChordTest, FindRootLiniarFn) {
  const float eps = 0.0001;
  const Chord sut(eps, 1000);
  const auto fn = [](float x) { return 2 * x; };
  const auto result = sut.find_root(fn, 0.5f, 1.5f);
  EXPECT_TRUE(result.has_value());
  EXPECT_NEAR(result->result, 0.0f, eps);
}

TEST(ChordTest, FindRootSquareFn) {
  const float eps = 0.0001;
  const Chord sut(eps, 1000);
  const auto fn = [](float x) { return -2 * x * x + 2; };
  const auto result = sut.find_root(fn, -1.1f, 0.f);
  EXPECT_TRUE(result.has_value());
  EXPECT_NEAR(result->result, -1.0f, eps);
}
TEST(ChordTest, FindRootCubeFn) {
  const float eps = 0.001;
  const Chord sut(eps, 100000);
  const auto fn = [](float x) { return x * x * x - 2 * x * x + 2; };
  const auto result = sut.find_root(fn, -1.f, 0.0f);
  EXPECT_TRUE(result.has_value());
  EXPECT_NEAR(result->result, -0.839f, eps);
}

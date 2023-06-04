#include "tangent.hpp"
#include <gtest/gtest.h>
#include <vcruntime.h>

TEST(TangentTest, FindRootLiniarFn) {
  const float eps = 0.0001;
  const Tangent sut(eps, 1000);
  const auto fn = [](float x) { return 2 * x; };
  const auto df = [](float x) { return 2.0f; };
  const auto result = sut.find_root(fn, df, 0.5f);
  EXPECT_TRUE(result.has_value());
  EXPECT_NEAR(result->result, 0.0f, eps);
}
TEST(TangentTest, FindRootSquareFn) {
  const float eps = 0.0001;
  const Tangent sut(eps, 1000);
  const auto fn = [](float x) { return -2 * x * x + 2; };
  const auto df = [](float x) { return -4 * x; };
  const auto result = sut.find_root(fn, df, -1.1f);
  EXPECT_TRUE(result.has_value());
  EXPECT_NEAR(result->result, -1.0f, eps);
}

TEST(TangentTest, FindRootCubeFn) {
  const float eps = 0.001;
  const Tangent sut(eps, 100000);
  const auto fn = [](float x) { return x * x * x - 2 * x * x + 2; };
  const auto df = [](float x) { return 3 * x * x - 4 * x; };
  const auto result = sut.find_root(fn, df, -1.0f);
  EXPECT_TRUE(result.has_value());
  EXPECT_NEAR(result->result, -0.839f, eps);
}

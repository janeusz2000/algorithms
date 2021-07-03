#include "codeWars/evaluateMathematicalExpression.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(CodeWarsTest, basicTest) {
  ASSERT_FLOAT_EQ(solve("12 + 4 * 2 / 4 + 3 * 8 / 3"), 22);

  ASSERT_FLOAT_EQ(solve("12.001 + 4 * 2 / 4 + 3 * 8 / 3"), 22.001);
  ASSERT_FLOAT_EQ(solve("1e-2 * 100 + 40 * 2 + 20"), 101);
}
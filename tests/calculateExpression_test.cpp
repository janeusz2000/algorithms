#include "codeWars/evaluateMathematicalExpression.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(CodeWarsTest, basicTest) {
  ASSERT_FLOAT_EQ(calc("12 + 4 * 2 / 4 + 3 * 8 / 3"), 22);
  ASSERT_FLOAT_EQ(calc("-1 * 8 + 3 * -5 / 3"), -13);
  ASSERT_FLOAT_EQ(calc("12.001 + 4 * 2 / 4 + 3 * 8 / 3"), 22.001);
  ASSERT_FLOAT_EQ(calc("1e-2*100+40*2+20"), 101);
  ASSERT_FLOAT_EQ(calc("2 * (1 + 3 * 5) / 16 + 5 * 4 * (2 + 1)"), 62);
  ASSERT_FLOAT_EQ(calc("(((((-1)))))"), -1);
}

// -1 *

#include "codeWars/evaluateMathematicalExpression.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(CodeWarsTest, basicTest) {
  ASSERT_FLOAT_EQ(calc("1 + 1 + 1"), 3);
  ASSERT_FLOAT_EQ(calc("1 + 1"), 2);
  ASSERT_FLOAT_EQ(calc("8/16"), 0.5);
  // ASSERT_FLOAT_EQ(calc("3 -(-1)"), 4);
  // ASSERT_FLOAT_EQ(calc("2 + -2"), 0);
  // ASSERT_FLOAT_EQ(calc("10- 2- -5"), 13);
  // ASSERT_FLOAT_EQ(calc("(((10)))"), 10);
  // ASSERT_FLOAT_EQ(calc("3 * 5"), 15);
  // ASSERT_FLOAT_EQ(calc("-7 * -(6 / 3)"), 14);
  FAIL();
}
#include "codeWars/pyramid.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::ElementsAreArray;

TEST(Pyramid, Stars) {
  Kata kata;
  ASSERT_EQ(kata.starsLevel(0), "*");
  ASSERT_EQ(kata.starsLevel(1), "***");
  ASSERT_EQ(kata.starsLevel(2), "*****");
}

TEST(Pyramid, Spaces) {
  Kata kata;
  ASSERT_EQ(kata.space(3), "   ");
  ASSERT_EQ(kata.space(2), "  ");
  ASSERT_EQ(kata.space(1), " ");
  ASSERT_EQ(kata.space(0), "");
}

TEST(Pyramid, CodeWarsGivenTests) {

  Kata kata;
  std::vector<std::string> expected_one = {"*"};
  ASSERT_THAT(kata.towerBuilder(1), ElementsAreArray(expected_one));

  std::vector<std::string> expected_two = {" * ", "***"};
  ASSERT_THAT(kata.towerBuilder(2), ElementsAreArray(expected_two));

  std::vector<std::string> expected_three = {"  *  ", " *** ", "*****"};
  ASSERT_THAT(kata.towerBuilder(3), ElementsAreArray(expected_three));
};
#include "codeWars/Beermid.hpp"
#include "gtest/gtest.h"

TEST(BeerMid, Utils) {
  ASSERT_EQ(amountOfBeerToCreateLevel(1), 1);
  ASSERT_EQ(amountOfBeerToCreateLevel(2), 5);
  ASSERT_EQ(amountOfBeerToCreateLevel(3), 14);
}

TEST(BeerMid, CodeWarsBaisc) {
  ASSERT_EQ(beeramid(9, 2), 1);
  ASSERT_EQ(beeramid(10, 2), 2);
  ASSERT_EQ(beeramid(11, 2), 2);
  ASSERT_EQ(beeramid(21, 1.5), 3);
  ASSERT_EQ(beeramid(454, 5), 5);
  ASSERT_EQ(beeramid(455, 5), 6);
  ASSERT_EQ(beeramid(4, 4), 1);
  ASSERT_EQ(beeramid(3, 4), 0);
  ASSERT_EQ(beeramid(0, 4), 0);
  ASSERT_EQ(beeramid(-1, 4), 0);
}
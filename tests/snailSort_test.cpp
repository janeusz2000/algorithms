#include "codeWars/SnailSort.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <vector>

using ::testing::ElementsAreArray;
using CoordinateSequence = std::vector<std::pair<int, int>>;

TEST(SnailSort, sequenceTest) {
  CoordinateSequence obtainedSequence = createSequence(3, 3);
  CoordinateSequence expectedSequence = {{0, 0}, {1, 0}, {2, 0}, {2, 1}, {2, 2},
                                         {1, 2}, {0, 2}, {0, 1}, {1, 1}};
  ASSERT_THAT(obtainedSequence, ElementsAreArray(expectedSequence));
}

TEST(SnailSort, CataTest) {

  std::vector<std::vector<int>> v;
  std::vector<int> expected;

  v = {{}};
  expected = {};
  ASSERT_THAT(snail(v), ElementsAreArray(expected));

  v = {{1}};
  expected = {1};
  ASSERT_THAT(snail(v), ElementsAreArray(expected));

  v = {{1, 2}, {4, 3}};
  expected = {1, 2, 3, 4};
  ASSERT_THAT(snail(v), ElementsAreArray(expected));

  v = {{1, 2, 3}, {8, 9, 4}, {7, 6, 5}};
  expected = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  ASSERT_THAT(snail(v), ElementsAreArray(expected));

  v = {{1, 2, 3, 4}, {12, 13, 14, 5}, {11, 16, 15, 6}, {10, 9, 8, 7}};
  expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  ASSERT_THAT(snail(v), ElementsAreArray(expected));
}

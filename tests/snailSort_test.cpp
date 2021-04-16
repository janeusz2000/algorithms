#include "codeWars/SnailSort.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <vector>

using ::testing::ElementsAreArray;
using Sequence = std::vector<int>;
TEST(SnailSort, XSequenceTest) {
  const Sequence obtainedXSequence0 = createXSequence(0);
  const Sequence expectedXSequence0 = {};
  ASSERT_THAT(obtainedXSequence0, ElementsAreArray(expectedXSequence0));

  const Sequence obtainedXSequence1 = createXSequence(1);
  const Sequence expectedXSequence1 = {0};
  ASSERT_THAT(obtainedXSequence1, ElementsAreArray(expectedXSequence1));

  const Sequence obtainedXSequence2 = createXSequence(2);
  const Sequence expectedXSequence2 = {0, 1, 1, 0};
  ASSERT_THAT(obtainedXSequence2, ElementsAreArray(expectedXSequence2));

  const Sequence obtainedXSequence3 = createXSequence(3);
  const Sequence expectedXSequence3 = {0, 1, 2, 2, 2, 1, 0, 0, 1};
  ASSERT_THAT(obtainedXSequence3, ElementsAreArray(expectedXSequence3));
  const Sequence obtainedXSequence4 = createXSequence(4);
  const Sequence expectedXSequence4 = {0, 1, 2, 3, 3, 3, 3, 2,
                                       1, 0, 0, 0, 1, 2, 2, 1};
  ASSERT_THAT(obtainedXSequence4, ElementsAreArray(expectedXSequence4));

  const Sequence obtainedXSequence5 = createXSequence(5);
  const Sequence expectedXSequence5 = {0, 1, 2, 3, 4, 4, 4, 4, 4, 3, 2, 1, 0,
                                       0, 0, 0, 1, 2, 3, 3, 3, 2, 1, 1, 2};
  ASSERT_THAT(obtainedXSequence5, ElementsAreArray(expectedXSequence5));
}

TEST(SnailSort, YSequenceTest) {

  const Sequence obtainedYSequence0 = createYSequence(0);
  const Sequence expectedYSequence0 = {};
  ASSERT_THAT(obtainedYSequence0, ElementsAreArray(expectedYSequence0));

  const Sequence obtainedYSequence1 = createYSequence(1);
  const Sequence expectedYSequence1 = {0};
  ASSERT_THAT(obtainedYSequence1, ElementsAreArray(expectedYSequence1));

  const Sequence obtainedYSequence2 = createYSequence(2);
  const Sequence expectedYSequence2 = {0, 0, 1, 1};
  ASSERT_THAT(obtainedYSequence2, ElementsAreArray(expectedYSequence2));

  const Sequence obtainedYSequence3 = createYSequence(3);
  const Sequence expectedYSequence3 = {0, 0, 0, 1, 2, 2, 2, 1, 1};
  ASSERT_THAT(obtainedYSequence3, ElementsAreArray(expectedYSequence3))
      << "Expected: { 0, 0, 0, 1, 2, 2, 2, 1, 1}";

  const Sequence obtainedYSequence4 = createYSequence(4);
  const Sequence expectedYSequence4 = {0, 0, 0, 0, 1, 2, 3, 3,
                                       3, 3, 2, 1, 1, 1, 2, 2};
  ASSERT_THAT(obtainedYSequence4, ElementsAreArray(expectedYSequence4))
      << "Expected: [ 0, 0, 0, 0, 1, 2, 3, 3, 3, 3, 2, 1, 1, 1, 2, 2";

  const Sequence obtainedYSequence5 = createYSequence(5);
  const Sequence expectedYSequence5 = {0, 0, 0, 0, 0, 1, 2, 3, 4, 4, 4, 4, 4,
                                       3, 2, 1, 1, 1, 1, 2, 3, 3, 3, 2, 2};
  ASSERT_THAT(obtainedYSequence5, ElementsAreArray(expectedYSequence5));
}

TEST(SnailSort, CataTest) {

  std::vector<std::vector<int>> v;
  std::vector<int> expected;

  v = {{}};
  expected = {};
  std::cout << "first size: " << v.size() << std::endl;
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

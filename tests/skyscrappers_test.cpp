#include "codeWars/skyscrappers.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <numeric>
#include <vector>

TEST(SkyScrappers, CodeWarsTest) {

  /*   using ::testing::ElementsAreArray; */
  /*   const std::vector<int> firstClues = {3, 2, 2, 3, 2, 1, 1, 2, 3, 3, 2, 2,
   */
  /*                                        5, 1, 2, 2, 4, 3, 3, 2, 1, 2, 2, 4};
   */
  /*   /1* FIRST CLUES */
  /*    3 2 2 3 2 1 */
  /*   4           1 */
  /*   2           2 */
  /*   2           3 */
  /*   1           3 */
  /*   2           2 */
  /*   3           2 */
  /*    3 4 2 2 1 5 */
  /*   *1/ */

  /*   const std::vector<std::vector<int>> firstSolution = { */
  /*       {2, 1, 4, 3, 5, 6}, {1, 6, 3, 2, 4, 5}, {4, 3, 6, 5, 1, 2}, */
  /*       {6, 5, 2, 1, 3, 4}, {5, 4, 1, 6, 2, 3}, {3, 2, 5, 4, 6, 1}}; */
  /*   ASSERT_THAT(SolvePuzzle(firstClues), ElementsAreArray(firstSolution)); */

  /*   const std::vector<int> secondClues = {0, 0, 0, 2, 2, 0, 0, 0, 0, 6, 3, 0,
   */
  /*                                         0, 4, 0, 0, 0, 0, 4, 4, 0, 3, 0,
   * 0}; */

  /*   const std::vector<std::vector<int>> secondSolution = { */
  /*       {5, 6, 1, 4, 3, 2}, {4, 1, 3, 2, 6, 5}, {2, 3, 6, 1, 5, 4}, */
  /*       {6, 5, 4, 3, 2, 1}, {1, 2, 5, 6, 4, 3}, {3, 4, 2, 5, 1, 6}}; */
  /*   ASSERT_THAT(SolvePuzzle(secondClues), ElementsAreArray(secondSolution));
   */

  /*   const std::vector<int> thirdClues = {0, 3, 0, 5, 3, 4, 0, 0, 0, 0, 0, 1,
   */
  /*                                        0, 3, 0, 3, 2, 3, 3, 2, 0, 3, 1, 0};
   */
  /*   const std::vector<std::vector<int>> thirdSolution = { */
  /*       {5, 2, 6, 1, 4, 3}, {6, 4, 3, 2, 5, 1}, {3, 1, 5, 4, 6, 2}, */
  /*       {2, 6, 1, 5, 3, 4}, {4, 3, 2, 6, 1, 5}, {1, 5, 4, 3, 2, 6}}; */
  /*   ASSERT_THAT(SolvePuzzle(thirdClues), ElementsAreArray(thirdSolution)); */
}

TEST(EdgeFactory, basicEdgeFactoryTest) {
  int size = 3;
  EdgeFactory edgeFactory(size);
}

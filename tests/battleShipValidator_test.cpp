#include "codeWars/battleShipValidator.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <iostream>
#include <vector>

using Point = std::pair<int, int>;

#define ASSERT_VECTOR_HAS_PAIR_NOT_ORDERED(EXPECTED_ARRAY, ACTUAL_ARRAY)       \
  ASSERT_EQ(EXPECTED_ARRAY.size(), ACTUAL_ARRAY.size());                       \
  for (const auto &OBJECT : EXPECTED_ARRAY) {                                  \
    if (std::find(std::cbegin(ACTUAL_ARRAY), std::cend(ACTUAL_ARRAY),          \
                  OBJECT) == std::cend(ACTUAL_ARRAY)) {                        \
      FAIL() << "Object: "                                                     \
             << "x: " << OBJECT.first << ", y: " << OBJECT.second              \
             << ", wasn't found in: " << #ACTUAL_ARRAY << std::endl;           \
    }                                                                          \
  }                                                                            \
  SUCCEED();

void printTerritory(const Ship &ship) {
  auto territory = ship.getTerritory();
  for (const Point &point : territory) {
    std::cout << "x: " << point.first << ", y: " << point.second << "\n";
  }
  std::cout << std::flush;
}

TEST(BattleshipTest, ShipsPointsAndTerritory) {
  auto zero = std::make_pair(0, 0);
  Ship zeroShip(zero);

  std::vector<Point> expectedZeroShip = {zero};
  ASSERT_VECTOR_HAS_PAIR_NOT_ORDERED(expectedZeroShip, zeroShip.getShip());

  std::vector<Point> expectedZeroTerritory = {{0, 0},  {0, 1},  {1, 0},
                                              {1, 0},  {-1, 0}, {0, -1},
                                              {-1, 1}, {1, -1}, {-1, -1}};
  ASSERT_VECTOR_HAS_PAIR_NOT_ORDERED(expectedZeroTerritory,
                                     zeroShip.getTerritory());

  auto end = std::make_pair(9, 9);
  Ship endShip(end);

  std::vector<Point> expectedEndShip = {end};
  ASSERT_VECTOR_HAS_PAIR_NOT_ORDERED(expectedEndShip, endShip.getShip());

  std::vector<Point> expectedEndTerritory = {
      {8, 8},  {8, 9},  {8, 10}, {9, 8},   {9, 9},
      {9, 10}, {10, 8}, {10, 9}, {10, 10},
  };
  ASSERT_VECTOR_HAS_PAIR_NOT_ORDERED(expectedEndTerritory,
                                     endShip.getTerritory());

  auto point1 = std::make_pair(5, 5);
  Ship ship1(point1);
  auto point2 = std::make_pair(5, 6);
  ship1.addShipNewPoint(point2);
  std::vector<Point> expectedShip1Point = {point1, point2};
  ASSERT_VECTOR_HAS_PAIR_NOT_ORDERED(expectedShip1Point, ship1.getShip());

  std::vector<Point> expectedShip1Territory = {{4, 4}, {5, 4}, {6, 4}, {4, 5},
                                               {5, 5}, {6, 5}, {4, 6}, {5, 6},
                                               {6, 6}, {4, 7}, {5, 7}, {6, 7}};
  ASSERT_VECTOR_HAS_PAIR_NOT_ORDERED(expectedShip1Territory,
                                     ship1.getTerritory());
}

TEST(BattleShipTest, nonValidShips) {
  auto point1 = std::make_pair(0, 0);
  Ship validShip(point1);
  ASSERT_TRUE(validShip.isShipValid());

  Ship nonValidShip(point1);
  auto point2 = std::make_pair(1, 1);
  nonValidShip.addShipNewPoint(point2);
  ASSERT_FALSE(nonValidShip.isShipValid());

  Ship validShipHorizontal(point1);
  auto point3 = std::make_pair(1, 0);
  validShipHorizontal.addShipNewPoint(point3);
  ASSERT_TRUE(validShipHorizontal.isShipValid());

  Ship validShipVertical(point1);
  auto point4 = std::make_pair(0, 1);
  validShipVertical.addShipNewPoint(point4);
  ASSERT_TRUE(validShipVertical.isShipValid());

  Ship nonValidSquareShip(point1);
  nonValidSquareShip.addShipNewPoint(point2);
  nonValidSquareShip.addShipNewPoint(point3);
  nonValidSquareShip.addShipNewPoint(point4);
  ASSERT_FALSE(nonValidSquareShip.isShipValid());
};

TEST(BattleShipTest, pointInShipTerritory) {
  auto point1 = std::make_pair(5, 5);
  Ship ship1(point1);
  ASSERT_TRUE(ship1.isPointInShipTerritory(point1));

  auto pointInTerritory = std::make_pair(4, 4);
  ASSERT_TRUE(ship1.isPointInShipTerritory(pointInTerritory));

  auto pointNotInTerritory = std::make_pair(4, 3);
  ASSERT_FALSE(ship1.isPointInShipTerritory(pointNotInTerritory));

  auto outerPoint = std::make_pair(6, 7);
  ASSERT_FALSE(ship1.isPointInShipTerritory(outerPoint));

  auto point2 = std::make_pair(5, 6);
  ship1.addShipNewPoint(point2);
  ASSERT_TRUE(ship1.isPointInShipTerritory(point1));
  ASSERT_TRUE(ship1.isPointInShipTerritory(point2));
  ASSERT_TRUE(ship1.isPointInShipTerritory(pointInTerritory));
  ASSERT_FALSE(ship1.isPointInShipTerritory(pointNotInTerritory));
  ASSERT_TRUE(ship1.isPointInShipTerritory(outerPoint));
}

TEST(BattleShipTest, MyTest) {

  std::vector<std::vector<int>> wrongNumberOfShips = {
      {1, 0, 0, 0, 0, 1, 1, 0, 0, 0}, {1, 0, 1, 0, 0, 0, 0, 0, 0, 0},
      {1, 0, 1, 0, 1, 1, 1, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, {0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  /*
  wrongNumberOfShips:
  □ _ _ _ _ □ □ _ _ _
  □ _ □ _ _ _ _ _ _ _
  □ _ □ _ □ □ □ _ _ _
  □ _ _ _ _ _ _ _ _ _
  _ _ _ _ _ _ _ _ □ _
  _ _ _ _ □ □ □ _ _ _
  _ _ _ _ _ _ _ _ □ _
  _ _ _ □ _ _ _ _ _ _
  _ _ _ _ _ _ _ □ _ _
  _ _ _ _ _ _ _ _ _ _
  */
  ASSERT_FALSE(validate_battlefield(wrongNumberOfShips));

  std::vector<std::vector<int>> wrongShape = {
      {1, 0, 0, 0, 0, 1, 1, 0, 0, 0}, {1, 0, 1, 0, 0, 0, 0, 0, 1, 0},
      {1, 0, 1, 0, 1, 1, 1, 0, 1, 0}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, {0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 1, 0, 0, 1, 0}, {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  /*
  wrongShape:
  □ _ _ _ _ □ □ _ _ _
  □ _ □ _ _ _ _ _ □ _
  □ _ □ _ □ □ □ _ □ _
  □ _ _ _ _ _ _ _ _ _
  _ _ _ _ _ _ _ _ □ _
  _ _ _ _ □ □ _ _ _ _
  _ _ _ _ _ □ _ _ □ _
  _ _ _ □ _ _ _ _ _ _
  _ _ _ _ _ _ _ □ _ _
  _ _ _ _ _ _ _ _ _ _
  */
  ASSERT_FALSE(validate_battlefield(wrongShape));

  std::vector<std::vector<int>> wrongSpacing = {
      {1, 0, 0, 0, 0, 1, 1, 0, 0, 0}, {1, 0, 1, 0, 0, 0, 0, 0, 1, 0},
      {1, 0, 1, 1, 1, 1, 0, 0, 1, 0}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, {0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  /*
 wrongSpacing:
 □ _ _ _ _ □ □ _ _ _
 □ _ □ _ _ _ _ _ □ _
 □ _ □ □ □ □ _ _ □ _
 □ _ _ _ _ _ _ _ _ _
 _ _ _ _ _ _ _ _ □ _
 _ _ _ _ □ □ □ _ _ _
 _ _ _ _ _ _ _ _ □ _
 _ _ _ □ _ _ _ _ _ _
 _ _ _ _ _ _ _ _ _ _
 */
  ASSERT_FALSE(validate_battlefield(wrongSpacing));

  std::vector<std::vector<int>> wrongAxis = {
      {1, 0, 0, 0, 0, 1, 1, 0, 0, 0}, {1, 0, 1, 0, 0, 0, 0, 0, 1, 0},
      {1, 0, 1, 0, 1, 1, 1, 0, 1, 0}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 1, 0, 0, 0, 1, 0}, {0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

  /*
wrong Axis:
□ _ _ _ _ □ □ _ _ _
□ _ □ _ _ _ _ _ □ _
□ _ □ _ □ □ □ _ □ _
□ _ _ _ _ _ _ _ _ _
_ _ _ _ □ _ _ _ □ _
_ _ _ _ _ □ □ _ _ _
_ _ _ _ _ _ _ _ □ _
_ _ _ □ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
*/
  ASSERT_FALSE(validate_battlefield(wrongAxis));
}

TEST(BattleShipTest, CodeWarsTest) {
  std::vector<std::vector<int>> validSolution = {
      {1, 0, 0, 0, 0, 1, 1, 0, 0, 0}, {1, 0, 1, 0, 0, 0, 0, 0, 1, 0},
      {1, 0, 1, 0, 1, 1, 1, 0, 1, 0}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, {0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  /*
validSolution:
□ _ _ _ _ □ □ _ _ _
□ _ □ _ _ _ _ _ □ _
□ _ □ _ □ □ □ _ □ _
□ _ _ _ _ _ _ _ _ _
_ _ _ _ _ _ _ _ □ _
_ _ _ _ □ □ □ _ _ _
_ _ _ _ _ _ _ _ □ _
_ _ _ □ _ _ _ _ _ _
_ _ _ _ _ _ _ _ _ _
*/
  ASSERT_TRUE(validate_battlefield(validSolution));
};
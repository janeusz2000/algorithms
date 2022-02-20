// https://www.codewars.com/kata/585894545a8a07255e0002f1/train/cpp
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <stdexcept>

struct Coordinate {
  float x;
  float y;
};

bool operator==(const Coordinate &one, const Coordinate &two) {
  return one.x == two.x && one.y == two.y;
}

bool operator!=(const Coordinate &one, const Coordinate &two) {
  return !(one == two);
}

Coordinate operator+(const Coordinate &one, const Coordinate &two) {
  return Coordinate{one.x + two.x, one.y + two.y};
}

Coordinate operator-(const Coordinate &one, const Coordinate &two) {
  return Coordinate{one.x - two.x, one.y - two.y};
}

Coordinate operator/(const Coordinate &one, int divider) {
  if (divider == 0) {
    throw std::logic_error("division by zero");
  }
  return Coordinate{one.x / divider, one.y / divider};
}

const std::map<char, Coordinate> lettersConvertionMap = {
    {'A', Coordinate{0, 0}}, {'B', Coordinate{1, 0}}, {'C', Coordinate{2, 0}},
    {'D', Coordinate{0, 1}}, {'E', Coordinate{1, 1}}, {'F', Coordinate{2, 1}},
    {'G', Coordinate{0, 2}}, {'H', Coordinate{1, 2}}, {'I', Coordinate{2, 2}}};

const std::map<char, std::vector<char>> getAllEdges() {
  std::map<char, std::vector<char>> output;
  for (const auto &coord : lettersConvertionMap) {
    std::vector<char> possibleDestinations;

    for (const auto &tempCoord : lettersConvertionMap) {
      if (tempCoord.first == coord.first) {
        continue;
      }

      Coordinate possibleCoordinate =
          coord.second + (tempCoord.second - coord.second) / 2;

      if (std::all_of(lettersConvertionMap.begin(), lettersConvertionMap.end(),
                      [&](const std::pair<char, Coordinate> &transitionCoord) {
                        if (transitionCoord.first == tempCoord.first ||
                            transitionCoord.first == coord.first) {
                          return true;
                        }
                        return transitionCoord.second != possibleCoordinate;
                      })) {
        possibleDestinations.push_back(tempCoord.first);
      }
    }
    std::cout << "Key: " << coord.first << " destinations: [";
    for (const auto &key : possibleDestinations) {
      std::cout << key << ", ";
    }
    std::cout << std::endl;
    output.insert(std::make_pair(coord.first, possibleDestinations));
  }
  return output;
}

unsigned int countPatternsFrom(char firstDot, unsigned short length) {
  const auto allDestinations = getAllEdges();
  std::set<char> visitedDestinations;
  visitedDesinations.insert(firstDot);
  unsigned int count = 0;
  for (unsigned short iteration = 0; iteration < length; iteration++) {
  }
  return 0;
}

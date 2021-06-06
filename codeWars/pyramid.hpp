// https://www.codewars.com/kata/576757b1df89ecf5bd00073b

#ifndef PYRAMID_HPP
#define PYRAMID_HPP

#include <iostream>
#include <string>
#include <vector>

class Kata {
public:
  std::vector<std::string> towerBuilder(size_t nFloors);
  std::string space(size_t n);
  std::string starsLevel(size_t n);
};

std::vector<std::string> Kata::towerBuilder(size_t nFloors) {
  std::vector<std::string> outputPyramid;
  for (size_t index = 0; index < nFloors; index++) {
    std::string floor;
    std::string side = space(nFloors - index - 1);
    std::string stars = starsLevel(index);
    floor += side;
    floor += stars;
    floor += side;
    outputPyramid.push_back(floor);
  }
  return outputPyramid;
}

std::string Kata::space(size_t n) {
  std::string output;
  output.reserve(n);
  for (size_t index = 0; index < n; index++) {
    output += ' ';
  }
  return output;
}

std::string Kata::starsLevel(size_t n) {
  std::string output;
  output.reserve(n);
  for (size_t index = 0; index < 2 * n + 1; index++) {
    output += '*';
  }
  return output;
}

#endif
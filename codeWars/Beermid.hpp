
// https://www.codewars.com/kata/51e04f6b544cf3f6550000c1

#ifndef BEERMID_H
#define BEERMID_H

#include <cmath>
#include <iostream>

int amountOfBeerToCreateLevel(int level) {
  int totalNumberOfBeers = 0;
  for (; level > 0; --level) {
    totalNumberOfBeers += std::pow(level, 2);
  }
  return totalNumberOfBeers;
}

int beeramid(int bonus, double price) {
  const int howManyBeers = std::floor(bonus / price);
  if (howManyBeers <= 0) {
    return 0;
  }

  for (int level = 1; true; ++level)
    if (amountOfBeerToCreateLevel(level + 1) > howManyBeers) {
      return level;
    }
}

#endif
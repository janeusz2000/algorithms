// https://www.codewars.com/kata/521c2db8ddc89b9b7a0000c1/train

#ifndef SNAIL_SORT_H
#define SNAIL_SORT_H

#include <cmath>
#include <iostream>
#include <vector>

std::vector<int> createRange(size_t size) {
  std::vector<int> outputSequence;
  outputSequence.reserve(size);
  for (size_t index = 0; index < size; ++index) {
    outputSequence.push_back(index);
  }
  return outputSequence;
}

void printVec(const std::vector<int> &v) {
  std::cout << "[";
  for (const int number : v) {
    std::cout << number << ", ";
  }
  std::cout << std::endl;
}

std::vector<int> createXSequence(size_t size) {
  const std::vector<int> range = createRange(size);

  std::vector<int> xSequence;
  xSequence.reserve(std::pow(size, 2));

  int currentSize = size;
  auto xStart = range.cbegin();
  auto xStop = range.cend();

  auto xRStart = range.crbegin();
  auto xRStop = range.crend();

  while (true) {

    for (auto it = xStart; it != xStop; ++it) {
      xSequence.push_back(*it);
    }

    if (xSequence.size() >= std::pow(size, 2)) {
      break;
    }

    for (int temp = 0; temp < currentSize - 2; ++temp) {
      xSequence.push_back(*xRStart);
    }

    for (auto it = xRStart; it != xRStop; ++it) {
      xSequence.push_back(*it);
    }

    for (int temp = 0; temp < currentSize - 2; ++temp) {
      xSequence.push_back(*xStart);
    }

    currentSize -= 2;
    --xStop;
    --xRStop;
    ++xStart;
    ++xRStart;
  }
  return xSequence;
}

std::vector<int> createYSequence(size_t size) {
  std::vector<int> ySequence;

  ySequence.reserve(std::pow(size, 2));

  int yStart = 0;
  int yStop = size;

  int yRStart = size;
  int yRStop = 0;

  for (int currentElements = 0; true;) {

    for (int index = yStart; index < yStop; ++index) {
      ySequence.push_back(yStart);
      currentElements++;
    }

    for (int index = yStart + 1; index < yStop; ++index) {
      ySequence.push_back(index);
      currentElements++;
    }

    for (int index = yRStart - 1; index > yRStop + 1; --index) {
      ySequence.push_back(yStop - 1);
      currentElements++;
    }

    if (currentElements >= std::pow(size, 2)) {
      break;
    }

    for (int index = yRStart - 1; index > yRStop; --index) {
      ySequence.push_back(index);
      currentElements++;
    }

    ++yStart;
    ++yRStop;
    --yRStart;
    --yStop;
  }
  return ySequence;
}

std::vector<int> snail(std::vector<std::vector<int>> &snail_map) {
  std::vector<int> output;
  if (snail_map[0].size() != 0) {
    output.reserve(std::pow(snail_map.size(), 2));

    std::vector<int> xSequence = createXSequence(snail_map[0].size());
    std::vector<int> ySequence = createYSequence(snail_map[0].size());
    printVec(xSequence);
    printVec(ySequence);

    for (size_t index = 0; index < xSequence.size(); ++index) {
      int y = xSequence[index];
      int x = ySequence[index];
      output.push_back(snail_map[x][y]);
    }
  }
  return output;
}

#endif
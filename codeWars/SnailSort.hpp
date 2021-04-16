// https://www.codewars.com/kata/521c2db8ddc89b9b7a0000c1/train

#ifndef SNAIL_SORT_H
#define SNAIL_SORT_H

#include <cmath>
#include <vector>

std::vector<int> createRange(int size) {
  std::vector<int> outputSequence;
  outputSequence.reserve(size);
  for (size_t index = 0; index < size; ++index) {
    outputSequence.push_back(index);
  }
  return outputSequence;
}

std::vector<std::pair<int, int>> createSequence(int size) {
  const std::vector<int> range = createRange(size);
  return {};
}

std::vector<int> snail(std::vector<std::vector<int>> &snail_map) { return {}; }

#endif
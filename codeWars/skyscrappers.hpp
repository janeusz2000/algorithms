// https://www.codewars.com/kata/5679d5a3f2272011d700000d/train/cpp

#ifndef SKYSCRAPPERS_HPP
#define SKYSCRAPPERS_HPP

#include <iostream>
#include <unordered_map>
#include <vector>

std::vector<std::vector<int>> SolvePuzzle(const std::vector<int> &clues);

struct EdgeFactory {
  explicit EdgeFactory(int size);

  std::vector<std::vector<int>> getEdges(int key);

private:
  std::unordered_map<int, std::vector<std::vector<int>>> edgeAllPossibleKeys_;
  int size_;
}

EdgeFactory::EdgeFactory(int size)
    : size_(size) {

  // TODO: calculate all possible edges for keys from 1 to size
}

std::vector<std::vector<int>> EdgeFactory::getEdges(int key) {
  return edgeAllPossibleKeys_.at(key);
}

std::vector<std::vector<int>> SolvePuzzle(const std::vector<int> &clues) {
  EdgeFactory edges(/*size=*/6);
}

#endif

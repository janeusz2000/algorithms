#ifndef BINARY_TREES_HPP
#define BINARY_TREES_HPP

#include <exception>
#include <iostream>
#include <vector>

template <typename T> void printBinaryTree(const std::vector<T> &array) {

  if (array.empty()) {
    std::cerr << "Warning! Given array to  the printBinaryTree() is empty!";
    return;
  }

  int numberOfElementsPerLevel = 1;
  int currentNumberOfElemetsPerLevel = 0;
  for (auto it = std::cbegin(array); it != std::cend(array); ++it) {
    std::cout << *it;
    if (++currentNumberOfElemetsPerLevel >= numberOfElementsPerLevel) {
      std::cout << std::endl;
      numberOfElementsPerLevel *= 2;
      currentNumberOfElemetsPerLevel = 0;
    } else {
      std::cout << " ";
    }
  }
};

#endif

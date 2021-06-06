// https://www.codewars.com/kata/54521e9ec8e60bc4de000d6c/

#ifndef MAXIMUM_SUBARRAY_SUM_HPP
#define MAXIMUM_SUBARRAY_SUM_HPP

#include <vector>

int maxSequence(const std::vector<int> &arr) {
  int maxSum = 0;
  for (size_t begin = 0; begin < arr.size(); begin++) {
    int temporarySum = 0;
    for (size_t temp = begin; temp < arr.size(); temp++) {
      temporarySum += arr[temp];
      maxSum = std::max(temporarySum, maxSum);
    }
  }
  return maxSum;
}

#endif
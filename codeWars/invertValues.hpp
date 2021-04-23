// https://www.codewars.com/kata/5899dc03bc95b1bf1b0000ad

#include <algorithm>
#include <vector>

std::vector<int> invert(std::vector<int> values) {
  std::transform(values.begin(), values.end(), values.begin(),
                 [](int value) { return -value; });
  return values;
}
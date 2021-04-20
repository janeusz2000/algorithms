// https://www.codewars.com/kata/576bb71bbbcf0951d5000044/
#include <numeric>
#include <vector>

std::vector<int> countPositivesSumNegatives(std::vector<int> input) {
  int positive =
      std::count_if(input.begin(), input.end(), [](int i) { return i > 0; });
  int negativeSum =
      std::accumulate(input.begin(), input.end(), 0, [&](int acc, int cur) {
        return cur > 0 ? acc : acc + cur;
      });
  return {positive, negativeSum};
}
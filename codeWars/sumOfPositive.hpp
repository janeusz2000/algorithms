#include <numeric>
#include <vector>

int positive_sum(const std::vector<int> &arr) {
  return std::accumulate(arr.begin(), arr.end(), 0, [](int acc, int cur) {
    return cur > 0 ? acc + cur : acc;
  });
}
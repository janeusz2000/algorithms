// https://www.codewars.com/kata/5679aa472b8f57fb8c000047

#include <numeric>
#include <vector>

int find_even_index(const std::vector<int> &numbers) {
  for (size_t index = 0; index < numbers.size(); ++index) {

    int sumLeft = std::accumulate(numbers.begin(), numbers.begin() + index, 0);
    int sumRight =
        std::accumulate(numbers.begin() + index + 1, numbers.end(), 0);

    if (sumLeft == sumRight) {
      return index;
    }
  }

  return -1;
}

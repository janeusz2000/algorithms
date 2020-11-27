#include "chapter/2.1/sort.h"

namespace algorithms {
void insertionSort(std::vector<float> &container) {
  float key;
  for (int index = 1; index < container.size(); ++index) {
    key = container[index];
    float current = index - 1;
    while (current >= 0 && container[current] > key) {
      container[current + 1] = container[current];
      --current;
    }
    container[++current] = key;
  }
}

void selectionSort(std::vector<float> &container) {
  for (int index = 0; index < container.size(); ++index) {
    float minimum = container[index];
    int replacementIndex = index;
    for (int current = index + 1; current < container.size(); ++current) {
      if (container[current] < minimum) {
        minimum = container[current];
        replacementIndex = current;
      }
    }
    container[replacementIndex] = container[index];
    container[index] = minimum;
  }
}

void mergeSorted(std::vector<float> &container) {

  // TODO: finish this. This implementation is wrong because this will be
  // recursive ;)

  int cuttingBorder = container.size() / 2;
  std::vector<float> left(cuttingBorder);
  std::vector<float> right(container.size() - cuttingBorder);

  for (int index = 0; index < cuttingBorder; ++index) {
    left[index] = container[index];
    right[index] = container[index + cuttingBorder];
  }

  left.push_back(std::numeric_limits<float>::max());
  right.push_back(std::numeric_limits<float>::max());

  for (int index = 0; index < container.size(); ++index) {
    continue;
  }
}

} // namespace algorithms
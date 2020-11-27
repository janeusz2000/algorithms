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
} // namespace algorithms
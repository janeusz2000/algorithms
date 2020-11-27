#include "main/2.1/page17.h"

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
} // namespace algorithms
#include "chapter/6.0/binaryTrees.hpp"

#include <vector>

int main() {

  std::vector<int> array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  printBinaryTree<int>(array);

  return 0;
}
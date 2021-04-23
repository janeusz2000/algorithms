// https://www.codewars.com/kata/56a5d994ac971f1ac500003e

#include <string>
#include <unordered_set>
#include <vector>

namespace LongestConsec {

std::string longestConsec(std::vector<std::string> &strarr, int k) {
  if (strarr.size() == 0 || k < 0 || k > strarr.size()) {
    return "";
  }
  std::unordered_set<std::string> used;
  std::vector<std::string> unique;
  for (std::string &word : strarr) {
    if (used.find(word) == used.end()) {
      unique.push_back(word);
      used.insert(word);
    }
  }

  std::vector<std::string> combinations;
  for (size_t index = 0; index < unique.size(); index++) {
    std::string combination = "";
    for (size_t tempIndex = 0; tempIndex < k; tempIndex++) {
      if (index + tempIndex < unique.size()) {
        combination += unique[index + tempIndex];
      }
    }
    combinations.push_back(combination);
  }

  int maxIndex = 0;

  for (size_t index = 1; index < combinations.size(); index++) {
    if (combinations[index].length() > combinations[maxIndex].length()) {
      maxIndex = index;
    }
  }
  return combinations[maxIndex];
}
}; // namespace LongestConsec

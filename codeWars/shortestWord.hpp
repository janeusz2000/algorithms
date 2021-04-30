
// https://www.codewars.com/kata/57cebe1dc6fdc20c57000ac9
#include <limits>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

int find_short(std::string str) {
  std::stringstream ss(str);
  size_t minSize = std::numeric_limits<size_t>::max();
  std::string temp;
  while (ss >> temp) {
    if (temp.size() < minSize) {
      minSize = temp.size();
    }
  }
  return minSize;
}
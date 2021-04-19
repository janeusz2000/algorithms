// https://www.codewars.com/kata/5656b6906de340bd1b0000ac

#include <set>

namespace TwoToOne {

std::string longest(std::string_view s1, std::string_view s2) {
  std::set<char> used(s1.begin(), s1.end());
  used.insert(s2.begin(), s2.end());
  return std::string(used.begin(), used.end());
}

}; // namespace TwoToOne
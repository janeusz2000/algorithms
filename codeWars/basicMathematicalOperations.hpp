// https://www.codewars.com/kata/57356c55867b9b7a60000bd7

#include <functional>
#include <unordered_map>

int basicOp(char op, int val1, int val2) {
  return std::unordered_map<char, std::function<int(int, int)>>{
      {'+', std::plus<>()},
      {'-', std::minus<>()},
      {'*', std::multiplies<>()},
      {'/', std::divides<>()}}
      .at(op)(val1, val2);
}
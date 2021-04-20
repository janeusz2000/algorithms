// https://www.codewars.com/kata/54ff3102c1bad923760001f3

#include <string>

std::string_view vowels = "aeiouAEIOU";

int getCount(std::string_view inputString) {
  return std::count_if(inputString.begin(), inputString.end(), [&](char i) {
    return std::find(vowels.cbegin(), vowels.cend(), i) != vowels.cend();
  });
}
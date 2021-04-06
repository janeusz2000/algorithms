// https://www.codewars.com/kata/55911ef14065454c75000062

#include <cmath>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <string_view>


int charToInt(char letter) { return letter - '0'; }

std::vector<std::string> performMultiplication(std::string_view a,
                                               std::string_view b) {
  size_t index = 0;
  std::vector<std::string> numbers;
  while (index < std::max(a.size(), b.size())) {

    auto itA = a.rbegin();
    for (size_t tempAIndex = 0; tempAIndex < index && itA != a.rend();
         ++tempAIndex) {
      ++itA;
    }

    std::string tempNumber;
    for (size_t temp = 0; temp < index; ++temp) {
      tempNumber += '0';
    }

    int reminder = 0;
    auto itB = b.rbegin();
    while (itB != b.rend() || reminder > 0) {

      int numA = (itA != a.rend()) ? charToInt(*itA) : 0;
      int numB = (itB != b.rend()) ? charToInt(*itB) : 0;
      int number = numA * numB + reminder;

      if (number < 10) {
        reminder = 0;
        tempNumber += std::to_string(number);
      } else {
        tempNumber += std::to_string(number % 10);
        reminder = (number - (number % 10)) / 10;
      }
      if (itB != b.rend()) {
        ++itB;
      }
    }

    numbers.push_back(tempNumber);
    ++index;
  }
  return numbers;
}

std::string
addNumbersAfterMultiplication(const std::vector<std::string> &numbers) {
  std::string output = "";
  for (const auto &number : numbers) {
    std::string temp;
    int reminder = 0;
    for (size_t index = 0;
         index < std::max(number.size(), output.size()) || reminder > 0;
         ++index) {

      int numA = index < output.size() ? charToInt(output[index]) : 0;
      int numB = index < number.size() ? charToInt(number[index]) : 0;
      int number = numA + numB + reminder;

      if (number < 10) {
        reminder = 0;
        temp += std::to_string(number);

      } else {
        temp += std::to_string(number % 10);
        reminder = (number - (number % 10)) / 10;
      }
    }
    output = temp;
  }
  return std::string(output.rbegin(), output.rend());
}

std::string removeZerosFromBeggining(std::string_view number) {
  bool first = true;
  auto stringRetentionRules = [&](std::string acc, char cur) {
    if (first && cur == '0') {
      acc = "0";
      return acc;
    } else {
      first = false;
      return acc == "0" ? std::to_string(charToInt(cur)) : acc + cur;
    }
  };

  return std::accumulate(number.begin(), number.end(), std::string(),
                         stringRetentionRules);
}

std::string multiply(std::string_view a, std::string_view b) {

  std::vector<std::string> numbers = performMultiplication(a, b);
  std::string output = addNumbersAfterMultiplication(numbers);
  return removeZerosFromBeggining(output);
}

#include <iostream>
#include <string>

int charToInt(char number) { return number - '0'; }

std::string add(std::string_view a, std::string_view b) {
  auto itA = a.rbegin();
  auto itB = b.rbegin();
  int reminder = 0;
  std::string output = "";
  while (itA != a.rend() || itB != b.rend() || reminder > 0) {
    int numA = itA != a.rend() ? charToInt(*itA) : 0;
    int numB = itB != a.rend() ? charToInt(*itB) : 0;
    int number = numA + numB + reminder;

    if (number < 10) {
      reminder = 0;
      output += std::to_string(number);
    } else {
      reminder = (number - (number % 10)) / 10;
      output += std::to_string(number % 10);
    }
  }
  return std::string(output.rbegin(), output.rend());
}

std::string multiply(std::string_view a, std::string_view b) {

  if (a == "0" && b == "0") {
    return "0";
  }

  std::string output = "";
  int reminder = 0;

  auto reversedNumberIt = b.rbegin();
  int numA = charToInt(*a.rbegin());
  while (reversedNumberIt != b.rend() || reminder > 0) {

    int numB = reversedNumberIt != b.rend() ? charToInt(*reversedNumberIt) : 0;
    int number = numA * numB + reminder;

    if (number < 10) {
      reminder = 0;
      output += std::to_string(number);
    } else {
      reminder = (number - (number % 10)) / 10;
      output += std::to_string(number % 10);
    }

    if (reversedNumberIt != b.rend()) {
      ++reversedNumberIt;
    }
  }

  std::string temp = std::string(a.substr(0, a.length() - 2)) + "0";
  return add(std::string(output.rbegin(), output.rend()), multiply(temp, b));
}
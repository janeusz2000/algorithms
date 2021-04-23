// https://www.codewars.com/kata/57eadb7ecd143f4c9c0000a3

#include <sstream>

std::string abbrevName(std::string name) {
  std::stringstream ss(name);
  std::string output;
  std::string temp;
  while (ss >> temp) {
    output += std::toupper(temp[0]);
    output += '.';
  }
  return output.substr(0, 3);
}
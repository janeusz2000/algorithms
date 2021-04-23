// https : // www.codewars.com/kata/54b42f9314d9229fd6000d9c

#include <string>

std::string duplicate_encoder(std::string str) {
  std::transform(str.begin(), str.end(), str.begin(),
                 [](unsigned char c) { return std::tolower(c); });

  std::string output;
  output.reserve(str.length());
  for (char letter : str) {
    output += std::count(str.begin(), str.end(), letter) > 1 ? ')' : '(';
  }
  return output;
}
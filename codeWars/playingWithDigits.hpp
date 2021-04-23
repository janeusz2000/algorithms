// https://www.codewars.com/kata/5552101f47fc5178b1000050

#include <cmath>
#include <numeric>
#include <string>

namespace DigPow {

int digPow(int n, int p) {

  std::string number = std::to_string(n);
  int result =
      std::accumulate(number.begin(), number.end(), 0, [&](int acc, char cur) {
        return acc + std::pow(cur - '0', p++);
      });
  return result % n == 0 ? result / n : -1;
}
} // namespace DigPow
// https://www.codewars.com/kata/57b06f90e298a7b53d000a86

#include <unordered_map>

long queueTime(std::vector<int> customers, int n) {

  std::vector<int> timePerCheckoutTills(n, 0);

  for (int time : customers) {
    *std::min_element(timePerCheckoutTills.begin(),
                      timePerCheckoutTills.end()) += time;
  }
  return *std::max_element(timePerCheckoutTills.begin(),
                           timePerCheckoutTills.end());
}
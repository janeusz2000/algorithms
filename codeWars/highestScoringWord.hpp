// https://www.codewars.com/kata/57eb8fcdf670e99d9b000272

#include <numeric>
#include <string>
#include <unordered_map>

struct maxScore {
  bool operator()(const std::pair<std::string, int> &val1,
                  const std::pair<std::string, int> &val2) {
    return val1.second == val2.second
               ? val1.first.length() < val2.first.length()
               : val1.second < val2.second;
  }
};

std::string highestScoringWord(std::string_view str) {
  std::stringstream ss(str.data());
  std::string temp;
  std::unordered_map<std::string, int> scores;
  while (ss >> temp) {
    int score =
        std::accumulate(temp.begin(), temp.end(), 0,
                        [](int acc, char cur) { return acc + cur - 'a' + 1; });
    scores.insert(std::make_pair(temp, score));
  }
  return std::max_element(scores.begin(), scores.end(), maxScore())->first;
}

class Kata {
public:
  std::vector<int> sortArray(std::vector<int> array) {

    std::vector<int> odd;
    std::copy_if(array.begin(), array.end(), std::back_inserter(odd),
                 [](int num) { return num % 2 != 0; });

    std::sort(odd.begin(), odd.end());
    std::vector<int> output;
    output.reserve(array.size());

    auto it = odd.begin();
    for (const int num : array) {
      output.push_back(num % 2 == 0 ? num : *(it++));
    }
    return output;
  }
};
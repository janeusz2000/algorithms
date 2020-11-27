#include "chapter/2.1/page17.h"
#include "gtest/gtest.h"

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
using algorithms::insertionSort;

class SortingFixtureTest : public ::testing::Test {
protected:
  std::vector<float> testVector;

  void SetUp() {
    testVector = {30.124, 23.23, 124,  3456, 1.34, 35.1, 34.3, 2,
                  32.25,  2356,  9.23, 8.34, 7.56, 6.23, 51.1, 4,
                  125.1,  -346,  124,  235,  235,  346,  23.1, 8};
  }

  std::string streamVector(const std::vector<float> &vec) {
    std::stringstream ss;
    ss << "\n[";
    for (const auto &num : vec) {
      std::cout << num << ", ";
    }
    return ss.str();
  }
};

TEST_F(SortingFixtureTest, InsertionSort) {
  std::vector<float> referenceVector = testVector;
  std::sort(referenceVector.begin(), referenceVector.end());
  std::vector<float> testedVector = testVector;
  insertionSort(testedVector);
  ASSERT_EQ(streamVector(testedVector), streamVector(referenceVector));
}
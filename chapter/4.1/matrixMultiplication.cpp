
#include <array>
#include <iostream>
#include <sstream>
#include <vector>

using Matrix = std::vector<std::vector<int>>;

void checkIfMatrixAreValid(const Matrix &alpha, const Matrix &beta) {
  std::stringstream errorStream;

  for (const auto &column : alpha) {
    if (alpha.size() != column.size()) {
      errorStream << "all dimensions in Alpha must be square!\n";
      break;
    }
  }

  for (const auto &column : beta) {
    if (beta.size() != column.size()) {
      errorStream << "Both axis in Beta must be square\n";
      break;
    }
  }

  if (alpha.size() != beta.size()) {
    errorStream << "Matrix have differrent n dimensions! \n"
                << "alpha: " << alpha.size() << ", beta: " << beta.size();
  }

  if ((errorStream >> std::ws).peek() != std::char_traits<char>::eof()) {
    std::stringstream errorMessage;
    errorMessage << "Error occurred in matrixMultiplication():\n"
                 << errorStream.rdbuf();
    throw std::invalid_argument(errorMessage.str());
  }
}

Matrix initializeMatrix(int size) {
  Matrix output;
  output.resize(size);
  for (auto &column : output) {
    column.resize(size);
  }
  return output;
}

Matrix matrixMultiplication(const Matrix &alpha, const Matrix &beta) {

  checkIfMatrixAreValid(alpha, beta);
  Matrix output = initializeMatrix(alpha.size());

  for (size_t i = 0; i < alpha.size(); ++i) {
    for (size_t j = 0; j < alpha.size(); ++j) {
      int tempSum = 0;
      for (size_t k = 0; k < alpha.size(); ++k) {
        tempSum += alpha[i][k] * beta[k][j];
      }
      output[i][j] = tempSum;
    }
  }

  return output;
}

Matrix matrixAddition(const Matrix &alpha, const Matrix &beta) {
  Matrix output = initializeMatrix(alpha.size());
  for (size_t x = 0; x < alpha.size(); ++x) {
    for (size_t y = 0; y < alpha.size(); ++y) {
      output[x][y] = alpha[x][y] + beta[x][y];
    }
  }
  return output;
}

void printMatrix(const Matrix &matrix) {
  for (const auto &column : matrix) {
    for (const auto &elem : column) {
      std::cout << elem << ", ";
    }
    std::cout << "\n";
  }
  std::cout << "===============" << std::endl;
}

int main() {

  Matrix alpha = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  Matrix beta = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

  Matrix result = matrixMultiplication(alpha, beta);

  printMatrix(alpha);
  printMatrix(beta);
  printMatrix(result);

  std::cout << "Program ended!";
}

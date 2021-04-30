#include <cmath>

std::string bmi(double w, double h) {
  double bmi = w / std::pow(h, 2);
  std::cout << bmi << std::endl;
  return bmi <= 18.5   ? "Underweight"
         : bmi <= 25.0 ? "Normal"
         : bmi > 30    ? "Obese"
                       : "Overweight";
}
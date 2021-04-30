// https://www.codewars.com/kata/52a78825cdfc2cfc87000005

#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>

const std::unordered_map<char, std::function<double(double, double)>>
    operations({{'+', std::plus<>()},
                {'-', std::minus<>()},
                {'*', std::multiplies<>()},
                {'/', std::divides<>()}});

char shortenOperation(char previousOperation, char nextOperation) {
  return previousOperation == ' '                           ? nextOperation
         : previousOperation == '-' && nextOperation == '-' ? '+'
         : previousOperation == '+' && nextOperation == '-' ? '-'
                                                            : nextOperation;
}

bool stringHasDigit(std::string_view str) {
  return std::find_if(str.begin(), str.end(), ::isdigit) != str.end();
}

std::string performCalculations(char op, std::string_view number1,
                                std::string_view number2) {
  if (op == ' ') {
    op = '+';
  }
  double num1 = stringHasDigit(number1) ? std::stod(number1.data()) : 0;
  double num2 = stringHasDigit(number2) ? std::stod(number2.data()) : 0;
  double output = operations.at(op)(num1, num2);
  std::cout << num1 << " " << op << " " << num2 << " = " << output << std::endl;
  return std::to_string(output);
}

std::string addTwoString(std::string_view number1, std::string_view number2) {
  double num1 = stringHasDigit(number1) ? std::stod(number1.data()) : 0;
  double num2 = stringHasDigit(number2) ? std::stod(number2.data()) : 0;
  double output = num1 + num2;
  std::cout << num1 << " + " << num2 << " = " << output << std::endl;

  return std::to_string(output);
}

double calc(std::string_view expression) {
  std::string num1, num2;
  char op = ' ';
  for (size_t index = 0; index < expression.size(); ++index) {
    if ((expression[index] == ' ' ||
         operations.find(expression[index]) != operations.end()) &&
        stringHasDigit(num1) && stringHasDigit(num2)) {

      num1 = performCalculations(op, num1, num2);
      op = operations.find(expression[index]) != operations.end()
               ? expression[index]
               : ' ';
      num2 = "";
    } else if (operations.find(expression[index]) != operations.end()) {
      op = shortenOperation(op, expression[index]);
    } else if (op == ' ') {
      num1 += expression[index];
    } else {
      num2 += expression[index];
    }
  }
  return std::stod(performCalculations(op, num1, num2));
}
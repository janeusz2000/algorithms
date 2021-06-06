// https://www.codewars.com/kata/5  2a78825cdfc2cfc87000005

#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>

// HEADER FILE
char shortenOperation(char previousOperation, char nextOperation);
bool stringHasDigit(std::string_view str);
double convertStringToDouble(std::string_view number);
char transformOperationIfEmpty(char op);
std::string performperformCalculations(char op, std::string_view number1,
                                       std::string_view number2);
std::string addTwoString(std::string_view number1, std::string_view number2);
bool parsingNumbersIsFinished(char op, char newCharacter, std::string_view num1,
                              std::string_view num2);
bool characterIsAnOperation(char newCharacter);
void parseNumbers(char op, char newDigit, std::string *num1, std::string *num2);
bool areOperatorsCombined(char previousOperator, char newOperator);
std::string_view getSubExpression(size_t currentIndex,
                                  std::string_view expression);
std::string_view performCalcAsString(std::string_view expression);
double performCalc(std::string_view expression);
bool expressionStartsWithMinusOperator(char character, std::string *num1,
                                       std::string *num2);
double calc(std::string_view expression);
std::vector<std::string_view> parseExpression(std::string_view expression);
void printExpressions(const std::vector<std::string_view> expressions);
std::vector<size_t> expressionEdgePositions(std::string_view expression);

// CPP FILE
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

double convertStringToDouble(std::string_view number) {
  return stringHasDigit(number) ? std::stod(number.data()) : 0;
}

char transformOperationIfEmpty(char op) { return op == ' ' ? '+' : op; }

std::string performperformCalculations(char op, std::string_view number1,
                                       std::string_view number2) {
  op = transformOperationIfEmpty(op);
  double num1 = convertStringToDouble(number1);
  double num2 = convertStringToDouble(number2);
  double output = operations.at(op)(num1, num2);
  std::cout << num1 << " " << op << " " << num2 << " = " << output << std::endl;
  return std::to_string(output);
}

std::string addTwoString(std::string_view number1, std::string_view number2) {
  double num1 = convertStringToDouble(number1);
  double num2 = convertStringToDouble(number2);
  double output = num1 + num2;
  std::cout << num1 << " + " << num2 << " = " << output << std::endl;

  return std::to_string(output);
}

bool parsingNumbersIsFinished(char op, char newCharacter, std::string_view num1,
                              std::string_view num2) {
  return (newCharacter == ' ' ||
          operations.find(newCharacter) != operations.end()) &&
         stringHasDigit(num1) && stringHasDigit(num2);
}

bool characterIsAnOperation(char newCharacter) {
  return operations.find(newCharacter) != operations.end();
}

void parseNumbers(char op, char newDigit, std::string *num1,
                  std::string *num2) {
  if (op == ' ') {
    *num1 += newDigit;
    return;
  }
  *num2 += newDigit;
}

bool areOperatorsCombined(char previousOperator, char newOperator) {
  return (previousOperator == '*' || previousOperator == '/') &&
         newOperator == '-';
}

std::string_view getSubExpression(size_t currentIndex,
                                  std::string_view expression) {
  return expression.substr(currentIndex + 1,
                           expression.find(')') - (currentIndex + 1));
}

std::string_view performCalcAsString(std::string_view expression) {
  double output = performCalc(expression);
  return std::to_string(output);
}

bool expressionStartsWithMinusOperator(char character, std::string *num1,
                                       std::string *num2) {
  return !stringHasDigit(*num1) && !stringHasDigit(*num2) && character == '-';
}

double performCalc(std::string_view expression) {
  std::cout << "INPUT: " << expression << std::endl;
  std::string num1, num2;
  char op = ' ';
  for (size_t index = 0; index < expression.size(); ++index) {
    if (parsingNumbersIsFinished(op, expression[index], num1, num2)) {
      num1 = performperformCalculations(op, num1, num2);
      num2.clear();
      op = characterIsAnOperation(expression[index]) ? expression[index] : ' ';
    } else if (expressionStartsWithMinusOperator(expression[index], &num1,
                                                 &num2)) {
      num1 += expression[index];
    }

    else if (characterIsAnOperation(expression[index])) {

      if (areOperatorsCombined(op, expression[index])) {
        num2 = '-';
      } else {
        op = shortenOperation(op, expression[index]);
      }
    } else if (expression[index] == '(') {
      std::string_view subExpression = getSubExpression(index, expression);
      double temp = num2[0] == '-' ? -1 * performCalc(subExpression)
                                   : performCalc(subExpression);
      num2 = std::to_string(temp);
      num1 = performperformCalculations(op, num1, num2);
      num2.clear();
      index += subExpression.size();
      op = ' ';
    } else {
      parseNumbers(op, expression[index], &num1, &num2);
    }
  }
  double result = std::stod(performperformCalculations(op, num1, num2));
  return result;
}

std::vector<std::string_view> parseExpression(std::string_view expression) {
  std::vector<std::string_view> outputExpressions;
  outputExpressions.push_back(expression);
  printExpressions(outputExpressions);
  return outputExpressions;
}

void printExpressions(const std::vector<std::string_view> expressions) {
  std::cout << "PRINTING EXPRESSIONS:\n";
  for (const auto &expression : expressions) {
    std::cout << "\t" << expression << "\n";
  }
  std::cout << std::endl;
}

double calc(std::string_view expression) {
  std::vector<std::string_view> expressions = parseExpression(expression);
  return std::accumulate(expressions.begin(), expressions.end(), 0.0,
                         [&](double acc, std::string_view curExpression) {
                           return acc + performCalc(curExpression);
                         });
}

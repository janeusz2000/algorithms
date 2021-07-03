// https://www.codewars.com/kata/52a78825cdfc2cfc87000005

#ifndef EVALUATE_MATHEMATICAL_EXPRESSION
#define EVALUATE_MATHEMATICAL_EXPRESSION

#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

enum class TokenType {
  NUMBER = 0,
  PLUS,
  MINUS,
  MULTIPLIES,
  DIVIDES,
  UNARY_OPERATOR
};

class TokenFactory;
class Token {
public:
  explicit Token(TokenType tokenType, double value, const TokenFactory &factory)
      : tokenType_(tokenType), value_(value), factory_(factory){};

  TokenType getType() const;
  double value() const;
  int getPrecedence() const;

  Token &operator=(const Token &other) {
    tokenType_ = other.tokenType_;
    value_ = other.value_;
    return *this;
  }

private:
  TokenType tokenType_;
  double value_;
  const TokenFactory &factory_;
};

TokenType Token::getType() const { return tokenType_; }
double Token::value() const { return value_; }

const std::unordered_map<TokenType, std::function<double(double, double)>>
    operationFunctions{{TokenType::PLUS, std::plus<>()},
                       {TokenType::MINUS, std::minus<>()},
                       {TokenType::MULTIPLIES, std::multiplies<>()},
                       {TokenType::DIVIDES, std::divides<>()}};
class TokenFactory {
public:
  explicit TokenFactory()
      : operations_{{'+', TokenType::PLUS},
                    {'-', TokenType::MINUS},
                    {'/', TokenType::DIVIDES},
                    {'*', TokenType::MULTIPLIES}},
        precedences_{{TokenType::NUMBER, 0},
                     {TokenType::PLUS, 1},
                     {TokenType::MINUS, 1},
                     {TokenType::DIVIDES, 2},
                     {TokenType::MULTIPLIES, 2}} {};

  Token createOperationToken(char operation) const {
    return Token(operations_.at(operation), 0, *this);
  }

  Token createNumberToken(double value) const {
    return Token(TokenType::NUMBER, value, *this);
  }

  int getPrecedence(TokenType tokenType) const {
    return precedences_.at(tokenType);
  }

  const std::unordered_map<char, TokenType> getOperations() const {
    return operations_;
  }

private:
  std::unordered_map<char, TokenType> operations_;
  std::unordered_map<TokenType, int> precedences_;
};

int Token::getPrecedence() const { return factory_.getPrecedence(tokenType_); }

std::vector<Token> parseExpression(std::string_view expression,
                                   TokenFactory *tokenFactory) {
  std::vector<Token> output;
  std::vector<Token> operatorStack;

  for (size_t index = 0; index < expression.length(); index++) {
    if (tokenFactory->getOperations().find(expression[index]) !=
        tokenFactory->getOperations().end()) {
      Token operationToken =
          tokenFactory->createOperationToken(expression[index]);

      if (operatorStack.empty() ||
          (!operatorStack.empty() &&
           operatorStack[operatorStack.size() - 1].getPrecedence() <=
               operationToken.getPrecedence())) {
        operatorStack.push_back(operationToken);
      } else {
        output.insert(output.end(), operatorStack.rbegin(),
                      operatorStack.rend());

        operatorStack.clear();
        operatorStack.push_back(operationToken);
      }

    } else if (isdigit(expression[index])) {
      char *endPoint;
      double value = std::strtod(expression.data() + index, &endPoint);
      index += endPoint - (expression.data() + index) - 1;
      output.push_back(tokenFactory->createNumberToken(value));
    }
  }

  if (!operatorStack.empty()) {
    output.insert(output.end(), operatorStack.rbegin(), operatorStack.rend());
  }

  return output;
}

double performOperation(Token operation, Token number1, Token number2) {
  return operationFunctions.at(operation.getType())(number1.value(),
                                                    number2.value());
}

double solve(std::string_view expression) {
  TokenFactory tokenFactory;
  std::vector<Token> parsedExpression =
      parseExpression(expression, &tokenFactory);
  while (parsedExpression.size() != 1) {
    auto operationToken = std::find_if(
        parsedExpression.begin(), parsedExpression.end(), [&](Token token) {
          return operationFunctions.find(token.getType()) !=
                 operationFunctions.end();
        });

    Token operation = *operationToken;
    Token number2 = *(operationToken - 1);
    Token number1 = *(operationToken - 2);

    double result = performOperation(operation, number1, number2);
    parsedExpression.erase(operationToken);
    parsedExpression.erase(operationToken - 1);
    *(operationToken - 2) = tokenFactory.createNumberToken(result);
  }
  return parsedExpression[0].value();
}
#endif
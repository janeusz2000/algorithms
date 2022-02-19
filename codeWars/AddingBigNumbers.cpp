#include <string>
#include <string_view>

int charToInt(char number) { return number - 48; }

std::string finalizeOutput(std::string *reversedOutput,
                           std::string_view reversedRemainingNumber,
                           int currentReminder) {

  for (const char number : reversedRemainingNumber) {
    unsigned temp = charToInt(number) + currentReminder;
    currentReminder = temp / 10;
    reversedOutput->append(std::to_string(temp % 10));
  }

  while (currentReminder > 0) {
    reversedOutput->append(std::to_string(currentReminder % 10));
    currentReminder /= 10;
  }

  return std::string(reversedOutput->rbegin(), reversedOutput->rend());
}

std::string add(std::string_view numA, std::string_view numB) {

  unsigned currentReminder = 0;
  std::string reversedOutput;

  auto itA = numA.rbegin();
  auto itB = numB.rbegin();

  while (itA != numA.rend() && itB != numB.rend()) {

    unsigned temp = charToInt(*itA) + charToInt(*itB) + currentReminder;
    unsigned currentNum = temp >= 10 ? temp % 10 : temp;
    currentReminder = temp / 10;

    reversedOutput.append(std::to_string(currentNum));

    itA++;
    itB++;
  }

  return finalizeOutput(&reversedOutput,
                        itA != numA.rend()   ? std::string(itA, numA.rend())
                        : itB != numB.rend() ? std::string(itB, numB.rend())
                                             : "",
                        currentReminder);
}

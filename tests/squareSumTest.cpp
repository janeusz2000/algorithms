#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <list>
#include <map>
#include <optional>
#include <set>
#include <sstream>
#include <vector>

using testing::ElementsAre;
using testing::Throws;

class PotentialSolution {
public:
  explicit PotentialSolution(const std::vector<int> &mainFrame,
                             const std::vector<int> &additionalFrame,
                             const std::vector<int> &previousSolutionPosition)
      : mainFrame(mainFrame), additionalFrame(additionalFrame),
        previousSolutionPosition(previousSolutionPosition) {}

  explicit PotentialSolution(std::vector<int> &&mainFrame,
                             std::vector<int> &&additionalFrame,
                             std::vector<int> &&previousSolutionPosition)
      : mainFrame(mainFrame), additionalFrame(additionalFrame) {}

  std::vector<int> mainFrame;

  // TODO: This should be std::vector<std::vector<int>>.
  // There will be manny addional frames here constructed.
  std::vector<int> additionalFrame;

  // positions < 0 indicates that the number is in additional Frame.
  std::vector<int> previousSolutionPosition;
};

void printArray(const std::vector<int> &array, bool current = true) {
  if (current) {
    std::cout << "current: ";
  } else {
    std::cout << "prev   : ";
  }
  std::cout << '[';
  for (const int number : array) {
    if (number > 9) {
      if (static_cast<size_t>(number) == array.size()) {
        // print this number as orange
        std::cout << "\033[1;33m" << number << "\033[0m"
                  << ", ";
      } else {
        std::cout << number << ", ";
      }
    } else {
      std::cout << number << " , ";
    }
  }
  std::cout << std::endl;
}

bool isSumASquare(int a, int b) {
  int temp = std::floor(std::sqrt(a + b));
  return temp * temp == a + b;
}

void printPosition(const std::vector<int> &positionVector) {
  std::cout << "positions:" << std::endl;
  for (size_t i = 1; i < positionVector.size(); i++) {
    if (positionVector[i] != -1) {
      std::cout << i << '\t' << positionVector[i] << std::endl;
    }
  }
}

std::vector<int> revertArray(const std::vector<int> &array) {
  return std::vector<int>(array.rbegin(), array.rend());
}

void offsetArray(int offset, std::vector<int> *array) {

  offset = offset % static_cast<int>(array->size());

  if (offset == 0) {
    return;
  }

  std::vector<int> output;
  output.reserve(array->size());

  if (offset > 0) {

    for (size_t i = offset + 1; i < array->size(); i++) {
      output.push_back((*array)[i]);
    }

    for (int i = 0; i <= offset; i++) {
      output.push_back((*array)[i]);
    }

  } else {

    for (int i = static_cast<int>(array->size()) - 1 + offset;
         i < static_cast<int>(array->size()); i++) {
      output.push_back((*array)[i]);
    }

    for (int i = 0; i < static_cast<int>(array->size()) - 1 + offset; i++) {
      output.push_back((*array)[i]);
    }
  }

  *array = std::move(output);
}

void replaceRange(int indexA, int indexB, const std::vector<int> &replacement,
                  std::vector<int> *replacementDestination,
                  std::vector<int> *remainsOfTheReplacement) {
  if (indexA == indexB) {
    std::stringstream ss;
    ss << "indexA: " << indexA << ", cannot be the same as indexB";
    throw std::invalid_argument(ss.str());
  }

  if (indexA < 0 ||
      static_cast<size_t>(indexA) > replacementDestination->size() - 1 ||
      indexB < 0 ||
      static_cast<size_t>(indexB) > replacementDestination->size() - 1) {
    std::stringstream ss;
    ss << "index A: " << indexA << ", and indexB: " << indexB
       << " out of bounds of the replacement from: " << 0
       << " to: " << replacementDestination->size() - 1;
    throw std::invalid_argument(ss.str());
  }

  if (!remainsOfTheReplacement->empty()) {
    std::stringstream ss;
    ss << "remains of the replacement not empty! remains of the replacement: [";
    for (const auto n : *remainsOfTheReplacement) {
      ss << n << ", ";
    }
    throw std::invalid_argument(ss.str());
  }

  size_t replacementStart =
      static_cast<size_t>(indexA < indexB ? indexA : indexB);
  size_t replacementEnd =
      static_cast<size_t>(indexB > indexA ? indexB : indexA);

  remainsOfTheReplacement->reserve(replacementEnd - replacementStart);

  std::vector<int> output;
  output.reserve(replacement.size() + replacementStart +
                 replacementDestination->size() - replacementEnd);

  for (size_t i = 0; i < replacementStart; i++) {
    output.push_back((*replacementDestination)[i]);
  }

  for (size_t i = 0; i < replacement.size(); i++) {
    output.push_back(replacement[i]);
  }

  for (size_t i = replacementEnd + 1; i < replacementDestination->size(); i++) {
    output.push_back((*replacementDestination)[i]);
  }

  for (size_t i = replacementStart; i <= replacementEnd; i++) {
    remainsOfTheReplacement->push_back((*replacementDestination)[i]);
  }

  *replacementDestination = std::move(output);
}

int findNumberInArray(const std::vector<int> &vec, int target) {
  for (size_t i = 0; i < vec.size(); i++) {

    if (vec[i] == target) {
      return i;
    }
  }
  return -1;
}

void flipTheArray(int indexA, int indexB, std::vector<int> *array) {
  if (static_cast<size_t>(indexA) >= array->size() ||
      static_cast<size_t>(indexB) >= array->size() || indexA < 0 ||
      indexB < 0) {
    std::stringstream ss;
    ss << "Argument1: " << indexA << " or argument2: " << indexB
       << " out of bounds of array, which size is: " << array->size();
    throw std::invalid_argument(ss.str());
  }

  if (indexA == indexB) {
    return;
  }

  std::vector<int> flipTemp;
  flipTemp.reserve(std::abs(indexA - indexB));

  int flipStart = indexA > indexB ? indexB : indexA;
  int flipEnd = indexA > indexB ? indexA : indexB;

  for (int i = flipStart; i <= flipEnd; i++) {
    flipTemp.push_back((*array)[i]);
  }

  std::vector<int> remainLeft;
  remainLeft.reserve(flipStart);

  std::vector<int> remainRight;
  remainRight.reserve(flipEnd);

  for (int i = 0; i < flipStart; i++) {
    remainLeft.push_back((*array)[i]);
  }

  for (int i = flipEnd + 1; static_cast<size_t>(i) < array->size(); i++) {
    remainRight.push_back((*array)[i]);
  }

  std::vector<int> output;
  output.reserve(array->size());
  output.insert(output.end(), remainLeft.begin(), remainLeft.end());
  output.insert(output.end(), flipTemp.rbegin(), flipTemp.rend());
  output.insert(output.end(), remainRight.begin(), remainRight.end());
  *array = output;
}

void printRedText(const std::string &text) {
  // ANSI escape code for red text
  std::cout << "\033[1;31m" << text << "\033[0m" << std::endl;
}

void printGreenText(const std::string &text) {
  // ANSI escape code for green text
  std::cout << "\033[1;32m" << text << "\033[0m" << std::endl;
}

void printBlueText(const std::string &text) {
  // ANSI escape code for blue text
  std::cout << "\033[1;34m" << text << "\033[0m" << std::endl;
}

void printPotentialSolution(const PotentialSolution &solution) {
  printGreenText("Potential Solution: ");
  std::cout << "main frame: [";
  for (const auto number : solution.mainFrame) {
    if (number > 9) {
      if (static_cast<size_t>(number) == solution.mainFrame.size()) {
        std::cout << "\033[1;33m" << number << "\033[0m"
                  << ", ";
      } else {
        std::cout << number << ", ";
      }
    } else {
      std::cout << number << " , ";
    }
  }
  std::cout << "\n";

  std::cout << "additional frame: [";
  for (const auto number : solution.additionalFrame) {
    if (number > 9) {
      std::cout << number << ", ";
    } else {
      std::cout << number << " , ";
    }
  }
  std::cout << "\n";

  std::cout << "previous pos: [";
  for (const auto number : solution.previousSolutionPosition) {
    if (number > 9) {
      std::cout << number << ", ";
    } else {
      std::cout << number << " , ";
    }
  }
  std::cout << "\n";

  // printPosition(solution.previousSolutionPosition);
}

void printQueue(const std::vector<std::vector<int>> &queue) {
  std::cout << "QUEUE:\n";
  for (const auto &edges : queue) {
    std::cout << "edge: [";
    for (const int number : edges) {
      std::cout << number << ", ";
    }
    std::cout << std::endl;
  }
}

void printGraphElements(const std::map<int, std::set<int>> &graph) {
  for (const auto &[value, possibleDestinations] : graph) {
    std::cout << value << " : [";
    for (const int number : possibleDestinations) {
      std::cout << number << ", ";
    }
    std::cout << std::endl;
  }
}

void updategraph(std::map<int, std::set<int>> *graph, int n) {

  std::stringstream ss;
  ss << "current graph for n: " << n;
  printBlueText(ss.str());

  // preInitializeElements
  int end = graph->size() + 1;
  for (int i = end; i <= n; i++) {
    graph->insert(graph->end(), std::make_pair(i, std::set<int>()));
  }

  for (int i = end; i <= n; i++) {
    for (auto &[number, _] : *graph) {
      int potentialSquare = std::sqrt(number + i);

      if (number != i && potentialSquare * potentialSquare == number + i) {
        (*graph)[i].insert(number);
        (*graph)[number].insert(i);
      }
    }
  }
}

void printVisited(const std::vector<bool> &visited) {
  std::cout << "VISITED" << std::endl;
  for (size_t i = 1; i < visited.size(); i++) {
    std::cout << i << " -> " << std::boolalpha << visited[i] << ", "
              << std::endl;
  }
}

std::vector<int> getEdgesToVisit(const std::map<int, std::set<int>> &graph,
                                 int currentNode,
                                 const std::vector<bool> &visited, int target,
                                 bool pretendNoneWasVisited = false) {

  std::vector<int> edgesToVisit;

  for (const int neighboor : graph.at(currentNode)) {
    if (neighboor != currentNode && neighboor <= target &&
        (visited[neighboor] == false || pretendNoneWasVisited)) {
      edgesToVisit.push_back(neighboor);
    }
  }

  return edgesToVisit;
}

std::optional<size_t> getIndexOfElementInArray(const std::vector<int> &array,
                                               int element) {
  for (size_t i = 0; i < array.size(); i++) {
    if (array[i] == element) {
      return i;
    }
  }

  return std::nullopt;
}

void launchEndingAction(std::vector<int> &&current,
                        std::vector<int> *previousSolution) {
  /*
  printArray(*previousSolution, false);
  */
  *previousSolution = current;
}

bool traverseGraph(std::vector<int> *current, std::vector<bool> *visited,
                   std::vector<std::vector<int>> *queue,
                   const std::map<int, std::set<int>> &graph, int targetSize,
                   std::vector<int> *position) {

  int lastElement = current->back();

  while (!queue->empty()) {
    size_t queueSize = queue->size();
    auto &currentEdges = queue->back();
    if (!currentEdges.empty()) {

      int currentElement = currentEdges.back();
      currentEdges.pop_back();
      current->push_back(currentElement);
      (*position)[currentElement] = static_cast<int>(current->size()) - 1;

      (*visited)[currentElement] = true;
      queue->push_back(
          getEdgesToVisit(graph, currentElement, *visited, targetSize));
    }

    if (current->size() == static_cast<size_t>(targetSize)) {
      return true;
    }

    // There is new element in the path
    if (queue->size() > queueSize) {
      continue;
    }

    while (!queue->empty()) {
      queue->pop_back();

      if (!current->empty()) {
        int notValidVisited = current->back();
        if (lastElement == notValidVisited) {
          return false;
        }
        (*visited)[notValidVisited] = false;
        (*position)[current->back()] = -1;
        current->pop_back();
      }

      if (!queue->empty()) {
        auto &edge = queue->back();
        // if there are still elements to visit in this permutation of path
        // We need to halt cleaning process and proceed to traverse a path
        if (!edge.empty()) {
          break;
        }
      }
    }
  }
  return false;
}

std::pair<int, int>
findTheBestNeighboors(const std::vector<int> &targetNeighboors,
                      const std::vector<int> & /*previousSolutionPosition*/) {
  // TODO: We should calculate the smallest distance between the
  // targetNeighboors.
  return std::make_pair(targetNeighboors[0], targetNeighboors[1]);
}

std::set<std::pair<int, int>>
getUniquePairOfNumbersFromArray(const std::vector<int> &array) {
  std::set<std::pair<int, int>> uniquePairs;

  for (size_t i = 0; i < array.size() - 1; i++) {
    for (size_t j = i + 1; j < array.size(); j++) {
      uniquePairs.insert(std::make_pair(std::min(array[i], array[j]),
                                        std::max(array[i], array[j])));
    }
  }

  return uniquePairs;
}

bool insertSolution(int target, const std::map<int, std::set<int>> &graph,
                    std::vector<int> *previousSolution,
                    std::vector<int> *previousSolutionPosition) {

  if (previousSolution->empty() || previousSolutionPosition->empty()) {
    return false;
  }

  // #1 We take care of the first case where always the number we want to insert
  // will be in addional frame.
  previousSolutionPosition->push_back(-1);
  std::list<PotentialSolution> solutionQueue = {PotentialSolution(
      *previousSolution, std::vector<int>{target}, *previousSolutionPosition)};

  // #2 We calculate every other insertion point in the middle of the solution
  // that is possible.
  const auto targetNeighboors =
      getEdgesToVisit(graph, target,
                      /*getAllValuesThatCanBeNextToTarget*/
                      std::vector<bool>(target + 1, false), target, true);

  // We got two insertion points -> those two will be a neighboor of the target
  auto uniquePairsOfTargetNeighboors =
      getUniquePairOfNumbersFromArray(targetNeighboors);

  for (const auto &pair : uniquePairsOfTargetNeighboors) {
    // We need to copy the previous solution position and previous solution,
    // because we will modify it.
    auto tempPositions = *previousSolutionPosition;
    auto tempSolution = *previousSolution;

    // We need to find what range we need to replace.
    int indexA = tempPositions[pair.first];
    int indexB = tempPositions[pair.second];

    int replacementStartIndex = indexA < indexB ? indexA : indexB;
    int replacementEndIndex = indexA < indexB ? indexB : indexA;

    // We can check here if indexA or indexB happes to be
    // the end of the previous solution, because in this case we
    // found the solution right away.
    if (replacementStartIndex == 0) { // we can insert target in the beggining.

      // Regenerate the solution on tempSolution.
      tempSolution.clear();
      tempSolution.push_back(target);
      tempSolution.insert(tempSolution.end(), previousSolution->begin(),
                          previousSolution->end());

      // We need to shift all the positions by one except 0
      for (size_t i = 1; i < previousSolutionPosition->size(); i++) {
        (*previousSolutionPosition)[i] += 1;
      }

      // We inserted the target in the beggining of the array.
      (*previousSolutionPosition)[target] = 0;

      // Save the solution
      *previousSolution = std::move(tempSolution);
      printRedText("BEGGINING INSERTED AT THE BEGGINING");
      return true;
    }

    // We insert the solution at the end.
    if (static_cast<size_t>(replacementEndIndex) ==
        previousSolution->size() - 1) {
      // We just add the number to the end and update the position of the
      // target.
      tempSolution.push_back(target);
      (*previousSolutionPosition)[target] = tempSolution.size() - 1;

      // Save the solution
      *previousSolution = std::move(tempSolution);
      printRedText("BEGGINING INSERTED AT THE END");
      return true;
    }

    // We insert target in the middle of the solution.
    if (replacementEndIndex - replacementStartIndex == 1) {
      tempSolution.clear();
      for (int i = 0; i <= replacementStartIndex; i++) {
        tempSolution.push_back((*previousSolution)[i]);
      }

      tempSolution.push_back(target);
      for (size_t i = replacementEndIndex; i < previousSolution->size(); i++) {
        tempSolution.push_back((*previousSolution)[i]);
      }

      // We need to recalulate all the positions.
      for (size_t i = 0; i < tempSolution.size(); i++) {
        tempPositions[tempSolution[i]] = i;
      }

      *previousSolutionPosition = std::move(tempPositions);
      *previousSolution = std::move(tempSolution);
      printRedText("BEGGINING INSERTED IN THE MIDDLE");
      return true;
    }

    // If We reach here, that means none of the indexes are ends of the array,
    // and miminum distance between start and end range is 2, so we can replace
    // the range between replacementStartIndex+1 and replacementEndIndex-1
    // (offset are here because we do not want to include those numbers in the
    // replacement).
    replacementStartIndex += 1;
    replacementEndIndex -= 1;

    // This is the vector that we will need to find a place for later on in the
    // solution.
    std::vector<int> remainsOfTheReplacement;
    std::vector<int> replacement = {
        target}; // in this case we insert single solution in the range.
    replaceRange(replacementStartIndex, replacementEndIndex, replacement,
                 &tempSolution, &remainsOfTheReplacement);

    // Now we need to find the positions of the numbers after the replacement.
    // Instead of the calculating the offset we will just traverse through the
    // new arrays;
    for (int i = 0; i < static_cast<int>(remainsOfTheReplacement.size()); i++) {

      // We mark remains as the positions < 0. We need to remember that this
      // works only for elements != 0. for the 0 index we need to always check
      // the begginings of the array.
      tempPositions[remainsOfTheReplacement[i]] = i * -1;
    }

    for (size_t i = 0; i < tempSolution.size(); i++) {
      tempPositions[tempSolution[i]] = i;
    }

    // Now we will add this elements to the queue.
    solutionQueue.emplace_back(tempSolution, remainsOfTheReplacement,
                               tempPositions);

    // TODO: We should also check if its possible to cut the mainFrame to the
    // certain point, insert the number then.
  }

  int solutionCount = 1;

  while (!solutionQueue.empty()) {
    std::stringstream ss;
    ss << "solution count: " << solutionCount++;
    printGreenText(ss.str());

    PotentialSolution potentialSolution = std::move(solutionQueue.front());
    solutionQueue.pop_front();
    printPotentialSolution(potentialSolution);

    if (potentialSolution.additionalFrame.size() == 1) {

      int current = potentialSolution.additionalFrame[0];
      // We need to get potential neighbors where this number could be.
      const auto neighboors =
          getEdgesToVisit(graph, current,
                          /*getAllValuesThatCanBeNextToTarget*/
                          std::vector<bool>(target + 1, false), target, true);

      // This will be used later for flipping the array if neccesary.
      int mainFrameBeggining = potentialSolution.mainFrame.front();
      int mainFrameEnd = potentialSolution.mainFrame.back();

      // Calculate all possible left flips
      const auto leftFlipNeighboors =
          getEdgesToVisit(graph, mainFrameBeggining,
                          /*getAllValuesThatCanBeNextToTarget*/
                          std::vector<bool>(target + 1, false), target, true);

      std::vector<int> leftEndsCreatedWithAFlip;
      leftEndsCreatedWithAFlip.reserve(leftFlipNeighboors.size());
      for (const int x : leftFlipNeighboors) {
        int position = potentialSolution.previousSolutionPosition[x];
        if (position > 1) {
          leftEndsCreatedWithAFlip.push_back(
              potentialSolution.mainFrame[position - 1]);
        }
      }

      // calculate All possible right flips.
      const auto rightFlipNeighboors =
          getEdgesToVisit(graph, mainFrameEnd,
                          /*getAllValuesThatCanBeNextToTarget*/
                          std::vector<bool>(target + 1, false), target, true);

      std::vector<int> rightEndsCreatedWithAFlip;
      rightEndsCreatedWithAFlip.reserve(rightFlipNeighboors.size());

      for (const int x : rightFlipNeighboors) {
        int position = potentialSolution.previousSolutionPosition[x];
        if (position < target - 1) {
          rightEndsCreatedWithAFlip.push_back(
              potentialSolution.mainFrame[position + 1]);
        }
      }

      for (int number : neighboors) {

        // Check if we can insert at the beggining
        if (potentialSolution.previousSolutionPosition[number] == 0) {
          std::vector<int> output;
          output.reserve(target);

          output.push_back(target);
          output.insert(output.end(), potentialSolution.mainFrame.begin(),
                        potentialSolution.mainFrame.end());

          // Fix the positions in the potentnial Solution
          for (size_t i = 1;
               i < potentialSolution.previousSolutionPosition.size(); i++) {
            potentialSolution.previousSolutionPosition[i] += 1;

            assert(potentialSolution.previousSolutionPosition.size() == target);

            potentialSolution.previousSolutionPosition.push_back(0);
          }

          *previousSolution = std::move(output);
          *previousSolutionPosition =
              std::move(potentialSolution.previousSolutionPosition);

          printRedText("INSERTION POTENTIAL SOLUTION IN THE BEGGINING");
          return true;
        }

        // Check if we can insert the number at the end
        if (static_cast<size_t>(
                potentialSolution.previousSolutionPosition[number]) ==
            potentialSolution.mainFrame.size() - 1) {
          potentialSolution.mainFrame.push_back(target);
          potentialSolution.previousSolutionPosition.push_back(
              potentialSolution.mainFrame.size() - 1);

          *previousSolution = std::move(potentialSolution.mainFrame);
          *previousSolutionPosition =
              std::move(potentialSolution.previousSolutionPosition);

          printRedText("INSERTION POTENTIAL SOLUTION IN THE END");
          return true;
        }

        // Check if left flip creates the solution.
        if (std::find(leftEndsCreatedWithAFlip.begin(),
                      leftEndsCreatedWithAFlip.end(), number) !=
            leftEndsCreatedWithAFlip.end()) { // left flip creates the solution

          int flipEndIndex = potentialSolution.previousSolutionPosition[number];
          flipTheArray(0, flipEndIndex, &potentialSolution.mainFrame);

          std::vector<int> output;
          output.reserve(target);
          output.push_back(target);
          output.insert(output.end(), potentialSolution.mainFrame.begin(),
                        potentialSolution.mainFrame.end());

          *previousSolution = std::move(output);
          *previousSolutionPosition = std::vector<int>(target + 1, -1);
          for (size_t i = 0; i < previousSolution->size(); i++) {
            (*previousSolutionPosition)[(*previousSolution)[i]] = i;
          }

          printRedText("LEFT FLIP SINGLE INSERTION SOLUTION");
          return true;
        }

        // Check if left flip creates the solution.
        if (std::find(rightEndsCreatedWithAFlip.begin(),
                      rightEndsCreatedWithAFlip.end(), number) !=
            rightEndsCreatedWithAFlip.end()) { // left flip creates the solution

          int flipStartIndex =
              potentialSolution.previousSolutionPosition[number];
          flipTheArray(flipStartIndex, potentialSolution.mainFrame.size() - 1,
                       &potentialSolution.mainFrame);

          potentialSolution.mainFrame.push_back(target);
          *previousSolution = std::move(potentialSolution.mainFrame);
          *previousSolutionPosition = std::vector<int>(target + 1, -1);
          for (size_t i = 0; i < previousSolution->size(); i++) {
            (*previousSolutionPosition)[(*previousSolution)[i]] = i;
          }

          printRedText("RIGHT FLIP SINGLE INSERTION SOLUTION");
          return true;
        }

        // Check if we can flip the array to the number we wan.
        if (isSumASquare(potentialSolution.mainFrame.front(),
                         potentialSolution.mainFrame.back())) {
          int neighboorPosition =
              potentialSolution.previousSolutionPosition[number];
          int flipOffset = neighboorPosition;
          offsetArray(flipOffset, &potentialSolution.mainFrame);

          potentialSolution.mainFrame.push_back(target);

          for (size_t i = 0; i < potentialSolution.mainFrame.size(); i++) {
            potentialSolution
                .previousSolutionPosition[potentialSolution.mainFrame[i]] = i;
          }

          *previousSolution = std::move(potentialSolution.mainFrame);
          *previousSolutionPosition =
              std::move(potentialSolution.previousSolutionPosition);
          return true;
        }
      }

      // If we didn't succeed in any of those steps we should insert the number
      // and add more potential solutions to the queue.
      auto uniquePairsOfTargetNeighboors =
          getUniquePairOfNumbersFromArray(targetNeighboors);

      for (const auto &pair : uniquePairsOfTargetNeighboors) {
        // We need to copy the previous solution position and previous solution,
        // because we will modify it.
        auto tempPositions = *previousSolutionPosition;
        auto tempSolution = *previousSolution;

        // We need to find what range we need to replace.
        int indexA = tempPositions[pair.first];
        int indexB = tempPositions[pair.second];

        int replacementStartIndex = indexA < indexB ? indexA : indexB;
        int replacementEndIndex = indexA < indexB ? indexB : indexA;

        // We already check the edges so we can offset the replacementIndex
        replacementStartIndex += 1;
        replacementEndIndex -= 1;

        // This is the vector that we will need to find a place for later on in
        // the solution.
        std::vector<int> remainsOfTheReplacement;
        std::vector<int> replacement = {
            target}; // in this case we insert single solution in the range.
        replaceRange(replacementStartIndex, replacementEndIndex, replacement,
                     &tempSolution, &remainsOfTheReplacement);

        // Now we need to find the positions of the numbers after the
        // replacement. Instead of the calculating the offset we will just
        // traverse through the new arrays;
        for (int i = 0; i < static_cast<int>(remainsOfTheReplacement.size());
             i++) {

          // We mark remains as the positions < 0. We need to remember that this
          // works only for elements != 0. for the 0 index we need to always
          // check the begginings of the array.
          tempPositions[remainsOfTheReplacement[i]] = i * -1;
        }

        for (size_t i = 0; i < tempSolution.size(); i++) {
          tempPositions[tempSolution[i]] = i;
        }

        // Now we will add this elements to the queue.
        solutionQueue.emplace_back(tempSolution, remainsOfTheReplacement,
                                   tempPositions);
      }
    } else if (potentialSolution.additionalFrame.size() > 1) {

      auto &additionalFrame = potentialSolution.additionalFrame;
      auto &mainFrame = potentialSolution.mainFrame;

      // check if we can insert to the left side of the main frame
      auto potentialStartNeighboors =
          getEdgesToVisit(graph, additionalFrame.front(),
                          /*getAllValuesThatCanBeNextToTarget*/
                          std::vector<bool>(target + 1, false), target, true);
      auto potentialEndNeighboors =
          getEdgesToVisit(graph, additionalFrame.back(),
                          /*getAllValuesThatCanBeNextToTarget*/
                          std::vector<bool>(target + 1, false), target, true);

      std::vector<std::pair<int, int>> possibleInsertions;
      for (const int x : potentialStartNeighboors) {
        for (const int y : potentialEndNeighboors) {
          if (x != y) { //
            possibleInsertions.push_back(std::make_pair(x, y));
          }
        }
      }

      for (const auto &neighboorPair : possibleInsertions) {
        int positionA =
            potentialSolution.previousSolutionPosition[neighboorPair.first];
        int positionB =
            potentialSolution.previousSolutionPosition[neighboorPair.second];

        // We don't want to caclulate possible insertions when the numbers are
        // in the additional frame;
        if (positionA < 0 || positionB < 0) {
          continue;
        }

        int insertionBeggining = std::min(positionA, positionB);
        int insertionEnd = std::max(positionA, positionB);

        // Check if we can insert at the beggining:
        if (insertionBeggining == 0) {
          // Now We need to determine which of the end from the additionalFrame
          // can be connected to the mainFrame.
          if (isSumASquare(additionalFrame.front(), mainFrame.front())) {
            // We need to mirror flip additional Frame
            auto reversedAdditionalFrame = revertArray(additionalFrame);
            std::vector<int> output;
            output.reserve(target);

            output.insert(output.end(), reversedAdditionalFrame.begin(),
                          reversedAdditionalFrame.end());
            output.insert(output.end(), mainFrame.begin(), mainFrame.end());

            *previousSolutionPosition = std::vector<int>(target + 1, -1);

            for (size_t i = 0; i < output.size(); i++) {
              (*previousSolutionPosition)[output[i]] = i;
            }
            *previousSolution = std::move(output);
            printRedText(
                "ARRRAY INSERTION TO THE BEGGIING (ADDITIONAL FRAME BEGIN)");
            return true;
          } else if (isSumASquare(additionalFrame.back(), mainFrame.front())) {
            std::vector<int> output;
            output.reserve(target);

            output.insert(output.end(), additionalFrame.begin(),
                          additionalFrame.end());
            output.insert(output.end(), mainFrame.begin(), mainFrame.end());

            *previousSolutionPosition = std::vector<int>(target + 1, -1);

            for (size_t i = 0; i < output.size(); i++) {
              (*previousSolutionPosition)[output[i]] = i;
            }
            *previousSolution = std::move(output);
            printRedText(
                "ARRRAY INSERTION TO THE BEGGIING (ADDITIONAL FRAME END)");
            return true;
          }
        }

        // Check if we can insert at the end
        if (static_cast<size_t>(insertionEnd) ==
            potentialSolution.mainFrame.size() - 1) {
          // Now We need to determine which of the end from the additionalFrame
          // can be connected to the mainFrame.
          if (isSumASquare(additionalFrame.front(), mainFrame.back())) {
            std::vector<int> output;
            output.reserve(target);

            output.insert(output.end(), mainFrame.begin(), mainFrame.end());
            output.insert(output.end(), additionalFrame.begin(),
                          additionalFrame.end());
            *previousSolution = std::move(output);

            for (size_t i = 0; i < previousSolution->size(); i++) {
              (*previousSolutionPosition)[(*previousSolution)[i]] = i;
            }

            printRedText("ARRAY INSERTION TO THE END (ADIITIONAL FRAME BEGIN)");
            return true;
          } else if (isSumASquare(additionalFrame.back(), mainFrame.back())) {
            std::vector<int> output;
            output.reserve(target);

            output.insert(output.end(), mainFrame.begin(), mainFrame.end());
            output.insert(output.end(), additionalFrame.rbegin(),
                          additionalFrame.rend());
            *previousSolution = std::move(output);

            for (size_t i = 0; i < previousSolution->size(); i++) {
              (*previousSolutionPosition)[(*previousSolution)[i]] = i;
            }
            printRedText("ARRAY INSERTION TO THE END (ADDITIONAL FRAME END)");
          }
        }

        // Check if we can insert in the middle of the main frame:
        if (insertionEnd - insertionBeggining == 1) {
          std::cout << "insertionBeggining: " << insertionBeggining << ", insertionEnd: " << insertionEnd << std::endl;
          std::vector<int> output;
          output.reserve(target);
          for (size_t i = 0; i <= static_cast<size_t>(insertionBeggining);
               i++) {
            output.push_back(mainFrame[i]);
          }

          bool valid = false; // This is probably the case where additional
                              // frame position can be 0 which is also valid
                              // position for main frame;
          if (isSumASquare(mainFrame.back(), additionalFrame.front())) {
            output.insert(output.end(), additionalFrame.begin(),
                          additionalFrame.end());
            valid = true;
          } else if (isSumASquare(mainFrame.back(), additionalFrame.back())) {
            output.insert(output.end(), additionalFrame.rbegin(),
                          additionalFrame.rend());
            valid = true;
          }

          if (valid) {
            for (size_t i = insertionEnd; i < mainFrame.size(); i++) {
              output.push_back(mainFrame[i]);
            }

            *previousSolution = std::move(output);

            for (size_t i = 0; i < previousSolution->size(); i++) {
              (*previousSolutionPosition)[(*previousSolution)[i]] = i;
            }

            printRedText("ARRAY INSERTION IN THE MIDDLE");
            return true;
          }
        }
      }
    }

    // TODO: We should check if its possible to insert at the ends.
    // TODO: We should check if its possible to insert in the middle.
    //
    // TODO: We should check if we can flip right end to insert at the right end
    // (there could be possible many flips).
    //
    // TODO: After flip we should check if its possible to insert at the middle.
    // TODO: We should check if we can flip left end to insert at the right end
    // (there could be possible many flips).
    //
    // TODO: After flop we should check if its possible to insert at the middle.
    // TODO: Check if in anny of these steps we create an array loop that allows
    // us to flip the array to the right element to insert target.

    // DISCLAIMER: HERE THERE IS NO WAY WE CAN CHECK THIS VERY EASLY - WE SHOULD
    // JUST INSERT THE ARRAY.
    // TODO: We should insert the target and do the same procedure for the new
    // array.
    //
    // TODO: If this procedure fails we should insert tried edge to the
    // different range than it was, and continue this procedure.

    // TODO: If we run out of options we should proceed to bruteforce this array
    // -> this will make sure that the solution is valid.
  }
  return false;
}

bool bruteForceSolution(int target, const std::map<int, std::set<int>> &graph,
                        std::vector<int> *previousSolution,
                        std::vector<int> *previousSolutionPosition) {

  std::vector<int> current;
  current.reserve(target);

  *previousSolutionPosition = std::vector<int>(target + 1, -1);

  std::vector<std::vector<int>> queue;
  queue.reserve(target);
  std::vector<bool> visited(target + 1, false);

  // Calculate solution from scratch;
  for (const auto &[startingPoint, _] : graph) {

    if (startingPoint <= target) {
      queue.push_back(std::vector({startingPoint}));
      visited[startingPoint] = true;
    }

    if (traverseGraph(&current, &visited, &queue, graph, target,
                      previousSolutionPosition)) {
      launchEndingAction(std::move(current), previousSolution);
      printRedText("BRUTE FORCE");
      return true;
    }

    visited[startingPoint] = false;
  }

  return false;
}

std::vector<int> square_sums_row(int target) {
  printGreenText(std::string(50, '='));
  static std::map<int, std::set<int>> graph = {{1, {}}};
  if (graph.size() < static_cast<size_t>(target)) {
    updategraph(&graph, target);
  }

  static std::vector<int> previousSolution = {};
  static std::vector<int> previousSolutionPosition = {};

  if (!previousSolution.empty()) {
    printArray(previousSolution, false);
  }

  // Check if we can add new element to the end or beggining
  // TODO: We will need to replace this
  if (target - previousSolution.size() == 1) {
    if (insertSolution(target, graph, &previousSolution,
                       &previousSolutionPosition)) {
      printArray(previousSolution);
      return previousSolution;
    }
  }

  if (bruteForceSolution(target, graph, &previousSolution,
                         &previousSolutionPosition)) {
    printArray(previousSolution);
    return previousSolution;
  }

  return std::vector<int>();
}

class SolutionCheckTest : public testing::Test {
protected:
  void check(int number) {
    if (!squaresInitialized) {
      for (int i = 1; i < 45; i++) {
        squares[i * i] = true;
      }
      squaresInitialized = true;
    }

    std::vector<int> &&solution = square_sums_row(number);
    std::vector<bool> used(number + 1, false);

    std::string message = "Testing " + std::to_string(number) + " : ";
  }

  void perform(int n) {
    static bool squares[2001] = {false};
    static bool squares_initialized = false;
    if (!squares_initialized) {
      for (int i = 1; i < 45; i++)
        squares[i * i] = true;
      squares_initialized = true;
    }

    std::vector<int> &&solution = square_sums_row(n);
    std::vector<bool> used(n + 1, false);

    std::string message = "Testing " + std::to_string(n) + " : ";
    bool passed = (static_cast<size_t>(n) == solution.size());
    if (!passed) {
      message += "Not the right solution size";
    }

    for (size_t i = 0; passed && i < solution.size(); i++) {
      if (solution[i] <= 0 || solution[i] > n) {
        passed = false;
        message += "Number out of range [|0;n|]";
      } else if (used[solution[i]]) {
        passed = false;
        message += "Number present more than once";
      } else if (i < solution.size() - 1 &&
                 !squares[solution[i] + solution[i + 1]]) {
        passed = false;
        message += "Sum of two consecutive numbers not equal to square";
      } else {
        used[solution[i]] = true;
      }

      ASSERT_TRUE(passed) << message;
    }
  }

private:
  bool squares[2001] = {false};
  bool squaresInitialized = false;
};

TEST(UtilitiesTest, verifyLeftFlip) {
  std::vector<int> leftFlip{1, 2, 3, 4, 5, 6, 7};
  flipTheArray(0, 4, &leftFlip);
  ASSERT_THAT(leftFlip, ElementsAre(5, 4, 3, 2, 1, 6, 7));
}

TEST(UtilitiesTest, veriyRightFlip) {
  std::vector<int> rightFlip{1, 2, 3, 4, 5, 6, 7};
  flipTheArray(4, 6, &rightFlip);
  ASSERT_THAT(rightFlip, ElementsAre(1, 2, 3, 4, 7, 6, 5));
}

TEST(UtilitiesTest, verifyMiddleFlip) {
  std::vector<int> middleFlip{1, 2, 3, 4, 5, 6, 7};
  flipTheArray(2, 3, &middleFlip);
  ASSERT_THAT(middleFlip, ElementsAre(1, 2, 4, 3, 5, 6, 7));
}

TEST(UtilitiesTest, verifyLeftFlipInverted) {
  std::vector<int> leftFlip{1, 2, 3, 4, 5, 6, 7};
  flipTheArray(4, 0, &leftFlip);
  ASSERT_THAT(leftFlip, ElementsAre(5, 4, 3, 2, 1, 6, 7));
}

TEST(UtilitiesTest, veriyRightFlipInverted) {
  std::vector<int> rightFlip{1, 2, 3, 4, 5, 6, 7};
  flipTheArray(6, 4, &rightFlip);
  ASSERT_THAT(rightFlip, ElementsAre(1, 2, 3, 4, 7, 6, 5));
}

TEST(UtilitiesTest, verifyMiddleFlipInverted) {
  std::vector<int> middleFlip{1, 2, 3, 4, 5, 6, 7};
  flipTheArray(3, 2, &middleFlip);
  ASSERT_THAT(middleFlip, ElementsAre(1, 2, 4, 3, 5, 6, 7));
}

TEST(UtilitiesTest, verifyArgumentIndexValueLessThenZero) {
  std::vector<int> array{1, 2, 3};
  ASSERT_THROW(flipTheArray(-1, 1, &array), std::invalid_argument);
}

TEST(UtilitiesTest, verifyArgumentIndexValueMoreThenArraySize) {
  std::vector<int> array{1, 2, 3};
  ASSERT_THROW(flipTheArray(6, 1, &array), std::invalid_argument);
}

TEST(UtilitiesTest, ReplaceRangeInTheBegginning) {
  std::vector<int> array{1, 2, 3, 4, 5};
  std::vector<int> replacement{6, 7, 8, 9};

  std::vector<int> replacementRemains;
  replaceRange(0, 1, replacement, &array, &replacementRemains);

  ASSERT_THAT(array, ElementsAre(6, 7, 8, 9, 3, 4, 5));
  ASSERT_THAT(replacementRemains, ElementsAre(1, 2));
}

TEST(UtilitiesTest, ReplaceRangeInTheMiddle) {
  std::vector<int> array{1, 2, 3, 4, 5};
  std::vector<int> replacement{6, 7, 8, 9};

  std::vector<int> replacementRemains;
  replaceRange(1, 2, replacement, &array, &replacementRemains);

  ASSERT_THAT(array, ElementsAre(1, 6, 7, 8, 9, 4, 5));
  ASSERT_THAT(replacementRemains, ElementsAre(2, 3));
}

TEST(UtilitiesTest, ReplaceRangeInTheEnd) {
  std::vector<int> array{1, 2, 3, 4, 5};
  std::vector<int> replacement{6, 7, 8, 9};

  std::vector<int> replacementRemains;
  replaceRange(3, 4, replacement, &array, &replacementRemains);

  ASSERT_THAT(array, ElementsAre(1, 2, 3, 6, 7, 8, 9));
  ASSERT_THAT(replacementRemains, ElementsAre(4, 5));
}

TEST(UtilitiesTest, ReplaceRangeInvertedInTheBegginning) {
  std::vector<int> array{1, 2, 3, 4, 5};
  std::vector<int> replacement{6, 7, 8, 9};

  std::vector<int> replacementRemains;
  replaceRange(1, 0, replacement, &array, &replacementRemains);

  ASSERT_THAT(array, ElementsAre(6, 7, 8, 9, 3, 4, 5));
  ASSERT_THAT(replacementRemains, ElementsAre(1, 2));
}

TEST(UtilitiesTest, ReplaceRangeInvertedInTheMiddle) {
  std::vector<int> array{1, 2, 3, 4, 5};
  std::vector<int> replacement{6, 7, 8, 9};

  std::vector<int> replacementRemains;
  replaceRange(2, 1, replacement, &array, &replacementRemains);

  ASSERT_THAT(array, ElementsAre(1, 6, 7, 8, 9, 4, 5));
  ASSERT_THAT(replacementRemains, ElementsAre(2, 3));
}

TEST(UtilitiesTest, ReplaceRangeInvertedInTheEnd) {
  std::vector<int> array{1, 2, 3, 4, 5};
  std::vector<int> replacement{6, 7, 8, 9};

  std::vector<int> replacementRemains;
  replaceRange(4, 3, replacement, &array, &replacementRemains);

  ASSERT_THAT(array, ElementsAre(1, 2, 3, 6, 7, 8, 9));
  ASSERT_THAT(replacementRemains, ElementsAre(4, 5));
}

TEST(UtilitiesTest, ReplaceRangeIndexOutOfBounds) {
  std::vector<int> array{1, 2, 3, 4, 5};
  std::vector<int> replacement{6, 7, 8, 9};

  std::vector<int> replacementRemains;

  // Normal Range
  ASSERT_THROW(replaceRange(-1, 4, replacement, &array, &replacementRemains),
               std::invalid_argument);
  ASSERT_THROW(replaceRange(0, 5, replacement, &array, &replacementRemains),
               std::invalid_argument);

  // Inverted
  ASSERT_THROW(replaceRange(4, -1, replacement, &array, &replacementRemains),
               std::invalid_argument);
  ASSERT_THROW(replaceRange(5, 0, replacement, &array, &replacementRemains),
               std::invalid_argument);
}

TEST(UtilitiesTest, ReplaceRangeReplacementRemainsNotEmpty) {
  std::vector<int> array{1, 2, 3, 4, 5};
  std::vector<int> replacement{6, 7, 8, 9};

  std::vector<int> replacementRemains = {1};

  ASSERT_THROW(replaceRange(0, 4, replacement, &array, &replacementRemains),
               std::invalid_argument);
}

TEST(UtilitiesTest, OffsetArrayRight) {
  std::vector<int> array{1, 2, 3, 4, 5};
  offsetArray(2, &array);
  ASSERT_THAT(array, ElementsAre(4, 5, 1, 2, 3));
}

TEST(UtilitiesTest, OffsetArrayLeft) {
  std::vector<int> array{1, 2, 3, 4, 5};
  offsetArray(-2, &array);
  ASSERT_THAT(array, ElementsAre(3, 4, 5, 1, 2));
}

/* TEST(SumSquareUtils, verifyIncrementSequenceIncrementation) { */
/*   std::vector<int> sequence{0, 0, 0, 5, 0, 0, 0}; */
/*   reshapeSumSquare(3, &sequence); */
/*   ASSERT_THAT(sequence, ElementsAre(-1, 1, -1, 6, -1, 1, -1)); */
/* } */

/* TEST(SumSquareUtils, verifyIncrementSequenceDecrementation) { */
/*   std::vector<int> sequence{0, 0, 0, 5, 0, 0, 0}; */
/*   reshapeSumSquare(3, &sequence, false); */
/*   ASSERT_THAT(sequence, ElementsAre(1, -1, 1, 4, 1, -1, 1)); */
/* } */

TEST_F(SolutionCheckTest, VerifySequences) {
  // check single combinations
  /* check(26); */

  for (int i = 25; i <= 150; i++)
    perform(i);


  /* ASSERT_EQ(square_sums_row(14).size(), 0); */
  /* ASSERT_EQ(square_sums_row(2).size(), 0); */

  // for extra challenge uncomment this (780 is NOT tested in final tests)
  // check(780);
}

/* bool incrementedSolution(int target, const std::map<int, std::set<int>>
 * &graph, */
/*                          std::vector<int> *previousSolution) { */
/*   // Step #1: find target-1 element. */
/*   int targetPosition = findNumberInArray(*previousSolution, target - 1); */

/*   // Step #2: create copy of the previous Solution. */
/*   std::vector<int> incrementSolution = *previousSolution; */

/*   reshapeSumSquare(targetPosition, &incrementSolution); */

/*   // TODO: #3 I want to take as much as possible from the maximum */
/*   // incrementation. */

/*   // TODO: #4 brute force the rest - for now (there might be a possibility
 * that */
/*   // decrementation of the maximum element gives us all missing parts) */
/*   printArray(incrementSolution); */

/*   return false; */
/* } */

/* [[depracated]] bool additionSolution(int target, const std::map<int,
 * std::set<int>>& graph, std::vector<int>* previousSolution) { */

/*   // THIS DOES NOT WORK */

/*   // This condition must not be fullfield to solve this solution via addition
 */
/*   if (!previousSolution || previousSolution->empty()) { */
/*     return false; */
/*   } */

/*   auto tempSolutionBigger = *previousSolution; // we want to work on copy */
/*   auto tempSolutionSmaller = *previousSolution; // we want to work on copy */

/*   // #1 step one: find current max position */
/*   int currentIndex = findNumberInArray(*previousSolution, target-1); */
/*   tempSolutionBigger[currentIndex] += 1; */
/*   tempSolutionSmaller[currentIndex] -= 1; */

/*   bool addOrSubtract = false; */
/*   for (size_t i = currentIndex + 1; i < tempSolutionBigger.size(); i++) { */
/*     tempSolutionBigger[i] += addOrSubtract ? 1 : -1; */
/*     tempSolutionSmaller[i] += addOrSubtract ? -1 : 1; */
/*     addOrSubtract = !addOrSubtract; */
/*   } */

/*   addOrSubtract = false; */
/*   for (int i = currentIndex - 1; i >= 0; i--) { */
/*     tempSolutionBigger[i] += addOrSubtract ? 1 : -1; */
/*     tempSolutionSmaller[i] += addOrSubtract ? -1 : 1; */
/*     addOrSubtract = !addOrSubtract; */
/*   } */

/*   printArray(*previousSolution); */
/*   printArray(tempSolutionBigger); */
/*   printArray(tempSolutionSmaller); */

/*   return false; */

/* } */

/* void reshapeSumSquare(int position, std::vector<int> *array, */
/*                       bool incrementTarget = true) { */
/*   auto &referenceArray = *array; */
/*   referenceArray[position] += incrementTarget ? 1 : -1; */

/*   int leftNeighboorIndex = position, rightNeighboorIndex = position; */
/*   bool reachedRightEnd = false; */
/*   bool reachedLeftEnd = false; */

/*   // We will swith this flag to increment or decrement neighboors. If we */
/*   // increment target, setting this to true will start with decrementing */
/*   // neighboors of the target. */
/*   bool decrement = incrementTarget; */
/*   while (leftNeighboorIndex != 0 || static_cast<size_t>(rightNeighboorIndex)
 * != */
/*                                         referenceArray.size() - 1) { */

/*     // travers next index */
/*     leftNeighboorIndex = std::max(0, leftNeighboorIndex - 1); */
/*     rightNeighboorIndex = std::min(static_cast<int>(referenceArray.size() -
 * 1), */
/*                                    rightNeighboorIndex + 1); */

/*     int value = decrement ? -1 : 1; */
/*     decrement = !decrement; */

/*     if (!reachedLeftEnd) { */
/*       referenceArray[leftNeighboorIndex] += value; */
/*     } */

/*     if (!reachedRightEnd) { */
/*       referenceArray[rightNeighboorIndex] += value; */
/*     } */

/*     // We need to stop incrementing when we reach right end: */
/*     if (static_cast<size_t>(rightNeighboorIndex) == referenceArray.size() -
 * 1) { */
/*       reachedRightEnd = true; */
/*     } */

/*     // We need to stop incrementing when we reach left end: */
/*     if (leftNeighboorIndex == 0) { */
/*       reachedLeftEnd = true; */
/*     } */
/*   } */
/* } */

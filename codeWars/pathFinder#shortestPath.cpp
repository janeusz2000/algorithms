// https://www.codewars.com/kata/57658bfa28ed87ecfa00058a/train/cpp

#include <cmath>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>

const std::unordered_map<char, std::pair<int, int>> kDirections = {
    {'N', {0, -1}}, {'S', {0, 1}}, {'E', {-1, 0}}, {'W', {1, 0}}};

std::pair<int, int> getCurrentPosition(const std::vector<char> &directions) {
  int x = 0, y = 0;

  for (const char dir : directions) {
    auto obtainedDirection = kDirections.at(dir);
    x += obtainedDirection.first;
    y += obtainedDirection.second;
  }
  return std::make_pair<int, int>(std::move(x), std::move(y));
}

class Maze {
public:
  explicit Maze(std::string_view mazePlan);

  char getMazeElement(int x, int y) const;
  std::vector<char> getAllPossibleDirectionsFromPoint(int x, int y) const;
  int getMazeDimention() const { return mazeDimention_; }
  void print() const;

private:
  std::string parseMazePlan(std::string_view mazePlan) const;
  int getDesiredMazeDimention(std::string_view ParsedMazePlan) const;
  bool isCoordinateValid(size_t x, size_t y) const;
  void reserveMemoryForMaze(size_t mazeSize);
  void populateMaze(std::string_view parsedMazePlan, size_t mazeDimention);

  std::vector<std::vector<char>> maze_;
  int mazeDimention_;
};

Maze::Maze(std::string_view mazePlan) {

  std::string parsedMazePlan = parseMazePlan(mazePlan);
  mazeDimention_ = getDesiredMazeDimention(parsedMazePlan);
  reserveMemoryForMaze(mazeDimention_);
  populateMaze(parsedMazePlan, mazeDimention_);
}

std::vector<char> Maze::getAllPossibleDirectionsFromPoint(int x, int y) const {

  std::vector<char> availableDestinations;
  if (isCoordinateValid(x, y)) {
    for (auto it = kDirections.cbegin(); it != kDirections.cend(); ++it) {
      int testedX = x + it->second.first;
      int testedY = y + it->second.second;

      if (isCoordinateValid(testedY, testedX) and
          getMazeElement(testedY, testedX) == '.') {
        availableDestinations.push_back(it->first);
      }
    }
  }
  return availableDestinations;
}

std::string Maze::parseMazePlan(std::string_view mazePlan) const {
  std::string parsedPlan = "";
  parsedPlan.reserve(mazePlan.size());
  for (char element : mazePlan) {
    if (element != '\n') {
      parsedPlan += element;
    }
  }
  return parsedPlan;
}

void Maze::print() const {
  for (auto &column : maze_) {
    for (const char &element : column) {
      std::cout << element;
    }
    std::cout << std::endl;
  }
}

bool Maze::isCoordinateValid(size_t x, size_t y) const {
  return (x < maze_.size() && y < maze_[y].size());
}

void Maze::reserveMemoryForMaze(size_t size) {
  maze_.resize(size);
  for (size_t index = 0; index < size; ++index) {
    maze_[index].resize(size, 'W');
  }
}

void Maze::populateMaze(std::string_view parsedMazePlan, size_t mazeDimention) {
  for (size_t index = 0; index < parsedMazePlan.size(); ++index) {
    maze_[index / mazeDimention][index % mazeDimention] = parsedMazePlan[index];
  }
}

char Maze::getMazeElement(int x, int y) const {
  if (isCoordinateValid(x, y)) {
    return maze_[x][y];
  }
  return 'W';
}

int Maze::getDesiredMazeDimention(std::string_view parsedMazePlan) const {
  return std::sqrt(parsedMazePlan.size());
}

int path_finder(std::string_view mazePlan) {

  if (mazePlan == ".") {
    return 0;
  }

  std::cout << std::endl;
  Maze maze(mazePlan);
  maze.print();

  std::vector<std::pair<int, int>> archivedPositions = {
      std::make_pair<int, int>(0, 0)};
  std::vector<std::pair<int, int>> previousPositions;

  for (size_t index = 1; index <= std::pow(maze.getMazeDimention(), 2);
       ++index) {

    std::vector<std::pair<int, int>> tempPositions;
    const size_t archivedPositionSize = archivedPositions.size();
    for (size_t archivedPositionIndex = 0;
         archivedPositionIndex < archivedPositionSize;
         ++archivedPositionIndex) {

      int currentX = archivedPositions[archivedPositionIndex].first,
          currentY = archivedPositions[archivedPositionIndex].second;

      const std::vector<char> availableDirections =
          maze.getAllPossibleDirectionsFromPoint(currentX, currentY);

      for (const char direction : availableDirections) {
        int archivedX = currentX + kDirections.at(direction).first;
        int archivedY = currentY + kDirections.at(direction).second;

        if (archivedX == maze.getMazeDimention() - 1 &&
            archivedY == maze.getMazeDimention() - 1) {
          return index;
        }

        auto currentPosition = std::make_pair<int, int>(std::move(archivedX),
                                                        std::move(archivedY));
        if (std::find(tempPositions.begin(), tempPositions.end(),
                      currentPosition) == tempPositions.end() &&
            std::find(previousPositions.begin(), previousPositions.end(),
                      currentPosition) == previousPositions.end()) {
          tempPositions.push_back(currentPosition);
        }
      }
    }

    previousPositions = archivedPositions;
    archivedPositions = tempPositions;
  }
  return -1;
}
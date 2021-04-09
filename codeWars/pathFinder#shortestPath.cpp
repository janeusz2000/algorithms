// https://www.codewars.com/kata/57658bfa28ed87ecfa00058a

#include <cmath>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>

void printVec(const std::vector<char> &vec) {
  std::cout << "[";
  for (const char &elem : vec) {
    std::cout << elem << ", ";
  }
  std::cout << std::endl;
}

void printPaths(const std::vector<std::vector<char>> &vec) {
  for (const auto &path : vec) {
    printVec(path);
  }
  std::cout << "===========" << std::endl;
}

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

  std::string_view parsedMazePlan = parseMazePlan(mazePlan);
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
  std::cout << std::endl;
  Maze maze(mazePlan);
  maze.print();
  std::vector<char> destinations = maze.getAllPossibleDirectionsFromPoint(0, 0);

  int x = 0, y = 0;
  std::vector<std::vector<char>> paths;
  for (int iteration = 0; iteration < std::pow(maze.getMazeDimention(), 3);
       ++iteration) {

    if (iteration == 0) {
      std::vector<char> availableDir =
          maze.getAllPossibleDirectionsFromPoint(x, y);

      if (availableDir.empty()) {
        break;
      }

      for (const char elem : availableDir) {
        std::vector<char> temp = {elem};
        paths.push_back(temp);
      }

    } else {
      size_t numberOfPaths = paths.size();
      for (size_t pathIndex = 0; pathIndex < paths.size(); ++pathIndex) {

        auto currentCoordinate = getCurrentPosition(paths[pathIndex]);

        if (currentCoordinate.first == maze.getMazeDimention() - 1 &&
            currentCoordinate.second == maze.getMazeDimention() - 1) {
          return paths[pathIndex].size();
        }

        std::vector<char> availableDir = maze.getAllPossibleDirectionsFromPoint(
            currentCoordinate.first, currentCoordinate.second);

        int numberOfNewPaths = availableDir.size() - 1;
        for (char dir : availableDir) {

          if (numberOfNewPaths > 0) {

            std::vector<char> temp = paths[pathIndex];
            temp.push_back(dir);
            paths.push_back(temp);

            --numberOfPaths;
          } else {
            paths[pathIndex].push_back(dir);
          }
        }
      }
    }
    printPaths(paths);
  }

  return -1;
}
#ifndef BATTLESHIP_HPP
#define BATTLESHIP_HPP

// https://www.codewars.com/kata/52bb6539a4cf1b12d90005b7

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

using Point = std::pair<int, int>;

// key value represents size of the ship, whereas value represents count of the
// ships in battlefield.
const std::unordered_map<int, int> battlefieldRules = {
    {4, 1}, {3, 2}, {2, 3}, {1, 4}};

bool validate_battlefield(std::vector<std::vector<int>> field);

class Printable {
public:
  virtual void printItself(std::ostream &os) const noexcept = 0;
};

inline std::ostream &operator<<(std::ostream &os, const Printable &object) {
  object.printItself(os);
  return os;
}

class Ship : public Printable {
public:
  explicit Ship(const Point &point);

  void addShipNewPoint(const Point &point);
  bool isPointInShipTerritory(const Point &point) const;
  bool isShipValid() const;

  enum class ShipShape { HORIZONTAL, VERTICAL, SINGLE };
  ShipShape getShape() const;

  // Returns all neighbors to the given point on the plane
  std::vector<Point> getPointTerritory(const Point &point);

  const std::vector<Point> &getShip() const { return shipPoints_; }
  const std::vector<Point> &getTerritory() const { return shipTerritory_; }
  int size() const;

  void printItself(std::ostream &os) const noexcept override;

private:
  bool isShapeValid() const;
  void recalculateShipTerritory();
  std::vector<Point> shipPoints_;
  std::vector<Point> shipTerritory_;
};

class Battlefield {
public:
  explicit Battlefield(int size) : size_(size){};
  // returns nullptr if given point doesn't belong to any ship territory
  Ship *doesPointBelongToAnyShip(const Point &point);
  void insertNewShipAtPoint(const Point &point);
  int size() const { return size_; };

  bool isNumberOfShipsValid() const;
  bool isArrangementOfShipsValid() const;

private:
  std::vector<Ship> battlefield_;
  int size_;
};

bool validate_battlefield(std::vector<std::vector<int>> field) {
  Battlefield battlefield(field.size());

  for (int x = 0; x < battlefield.size(); ++x) {
    for (int y = 0; y < battlefield.size(); ++y) {
      if (field[x][y] == 1) {
        auto currentPoint = std::make_pair(x, y);
        Ship *currentShip = battlefield.doesPointBelongToAnyShip(currentPoint);
        if (currentShip != nullptr) {
          currentShip->addShipNewPoint(currentPoint);
          if (!currentShip->isShipValid()) {
            return false;
          }

        } else {
          battlefield.insertNewShipAtPoint(currentPoint);
        }
      }
    }
  }
  return battlefield.isNumberOfShipsValid() &&
         battlefield.isArrangementOfShipsValid();
}

std::vector<Point> Ship::getPointTerritory(const Point &point) {
  int x = point.first;
  int y = point.second;
  std::vector<Point> outputTerritory;

  for (int currentX = x - 1; currentX <= x + 1; ++currentX) {
    for (int currentY = y - 1; currentY <= y + 1; ++currentY) {
      outputTerritory.push_back(std::make_pair(currentX, currentY));
    }
  }

  return outputTerritory;
}

Ship::Ship(const Point &point) { addShipNewPoint(point); }

bool Ship::isPointInShipTerritory(const Point &point) const {
  return (std::find(shipTerritory_.cbegin(), shipTerritory_.cend(), point) !=
          shipTerritory_.cend());
}

void Ship::addShipNewPoint(const Point &point) {
  shipPoints_.push_back(point);
  recalculateShipTerritory();
}

bool Ship::isShipValid() const { return isShapeValid() && size() < 5; }

int Ship::size() const { return shipPoints_.size(); }

Ship::ShipShape Ship::getShape() const {
  if (size() == 1) {
    return ShipShape::SINGLE;
  }

  return shipPoints_[0].first - shipPoints_[1].first == 0
             ? ShipShape::HORIZONTAL
             : ShipShape::VERTICAL;
}

bool Ship::isShapeValid() const {
  ShipShape shape = getShape();
  if (shape == ShipShape::HORIZONTAL) {
    int x = shipPoints_[0].first;
    for (auto &point : shipPoints_) {
      if (point.first != x) {
        return false;
      }
    }
    return true;
  } else if (shape == ShipShape::VERTICAL) {
    int y = shipPoints_[0].second;
    for (auto &point : shipPoints_) {
      if (point.second != y) {
        return false;
      }
    }
    return true;
  }
  return true;
}

void Ship::recalculateShipTerritory() {
  shipTerritory_.clear();

  for (auto &point : shipPoints_) {

    std::vector<Point> pointNeighboors = getPointTerritory(point);
    for (auto &neighboorPoint : pointNeighboors) {
      if (std::find(shipTerritory_.cbegin(), shipTerritory_.cend(),
                    neighboorPoint) == shipTerritory_.cend()) {
        shipTerritory_.push_back(neighboorPoint);
      }
    }
  }
}

void Ship::printItself(std::ostream &os) const noexcept {
  os << "SHIP\n"
     << "size: " << size() << "\n"
     << "Points: \n"
     << "x: \t y: \t";

  for (auto &point : shipPoints_) {
    os << point.first << "\t" << point.second;
  }

  os << "\n"
     << "Territory: \n"
     << "x: \t y: \t";

  for (auto &point : shipTerritory_) {
    os << point.first << "\t" << point.second;
  }
}

Ship *Battlefield::doesPointBelongToAnyShip(const Point &point) {
  for (auto &ship : battlefield_) {
    if (ship.isPointInShipTerritory(point)) {
      return &ship;
    }
  }
  return nullptr;
}

void Battlefield::insertNewShipAtPoint(const Point &point) {
  battlefield_.push_back(Ship(point));
}

bool Battlefield::isNumberOfShipsValid() const {
  for (auto recipe = battlefieldRules.cbegin();
       recipe != battlefieldRules.cend(); ++recipe) {
    int currentSize = recipe->first;
    int count = std::count_if(
        battlefield_.cbegin(), battlefield_.cend(),
        [&](Ship currentShip) { return currentShip.size() == currentSize; });

    if (count != recipe->second) {
      std::cout << "Count of the ships with size: " << currentSize
                << " is invalid\n"
                << "Expected: " << recipe->second << " got: " << count
                << std::endl;
      return false;
    }
  }

  return true;
}

bool Battlefield::isArrangementOfShipsValid() const {
  for (auto currentShip = battlefield_.cbegin();
       currentShip != battlefield_.end(); ++currentShip) {
    for (auto otherShip = battlefield_.cbegin();
         otherShip != battlefield_.cend(); ++otherShip) {
      if (currentShip == otherShip) {
        continue;
      }
      const auto shipPoints = currentShip->getShip();
      for (auto &point : shipPoints) {
        if (otherShip->isPointInShipTerritory(point)) {
          std::cout << "Arrangement is invalid!\n"
                    << "Ship: " << *currentShip
                    << "\nis in th territory of the: " << *otherShip << "\n"
                    << "at point: x: " << point.first << " y: " << point.second
                    << std::endl;
          return false;
        }
      }
    }
  }
  return true;
}

#endif
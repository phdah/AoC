#include "solutions.h"

const int Levels::isSafe() {
    const std::vector<int> levels = getLevels();
    if (noSafeLogic(levels)) return 0;
    return 1;
}

const std::vector<int> Levels::getLevels() {
    std::vector<int> levels;
    std::istringstream lineSplit(this->line);

    int level;
    while (lineSplit >> level) {
        levels.push_back(level);
    }

    return levels;
}

const bool Levels::noSafeLogic(const std::vector<int> levels) {
    int diff;
    for (int i=0; i<levels.size()-1; i++) {
        diff = levels[i+1] - levels[i];
        if (abs(diff) > 3) {
            return true;
        }

        if (invalidDirection(diff)) {
            return true;
        }
    }

    return false;
}

const bool Levels::invalidDirection(const int &diff) {
    enum Direction newDirection;

    if (diff < 0) {
        newDirection = Direction::DECREASING;
    } else if (diff > 0) {
        newDirection = Direction::INCREASING;
    } else {
        return true;
    }

    if (this->currDirection == Direction::STARTING) {
        this->currDirection = newDirection;
    } else if (this->currDirection != newDirection) {
        return true;
    }

    return false;
};

int firstSolution(std::string fileName) {
    FileOps file(fileName);
    std::ifstream &fileContents = file.getFile();

    std::string line;
    int resultFirst;
    while (std::getline(fileContents, line)) {
        Levels levels(line);
        resultFirst += levels.isSafe();
    }

    return resultFirst;
};


int secondSolution(std::string fileName) {
    FileOps file(fileName);
    std::ifstream &fileContents = file.getFile();

    int resultSecond = 0;
    return resultSecond;
}

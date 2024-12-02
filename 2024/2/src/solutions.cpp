#include "solutions.h"

const int Levels::isSafeFirst() {
    const std::vector<int> levels = getLevels();
    if (noSafeLogicFirst(levels)) return 0;
    return 1;
}

const int Levels::isSafeSecond() {
    std::vector<int> levels = getLevels();
    if (noSafeLogicSecond(levels)) return 0;
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

const bool Levels::logic(const int &diff) {
    if (abs(diff) > 3 || diff == 0) {
        return true;
    }

    if (invalidDirection(diff)) {
        return true;
    }

    return false;
}

const bool Levels::noSafeLogicFirst(const std::vector<int> &levels) {
    this->currDirection = Direction::STARTING; // Always start with direction start
    for (int i=0; i<levels.size()-1; i++) {
        if (logic(levels[i+1] - levels[i])) return true;
    }

    return false;
}

const bool Levels::bruteForceCheckWindows(const std::vector<int> &levels, const int i) {
    std::vector<int> withoutPrevValue(levels);
    withoutPrevValue.erase(withoutPrevValue.begin() + i -1);
    std::vector<int> withoutThisValue(levels);
    withoutThisValue.erase(withoutThisValue.begin() + i);
    std::vector<int> withoutNextValue(levels);
    withoutNextValue.erase(withoutNextValue.begin() + i +1);

    if (noSafeLogicFirst(withoutPrevValue) && noSafeLogicFirst(withoutThisValue) && noSafeLogicFirst(withoutNextValue)) {
        return true;
    }

    return false;
}

const bool Levels::noSafeLogicSecond(std::vector<int> &levels) {
    bool levelState = false;
    int vectorSize = levels.size();
    for (int i=0; i<vectorSize-1; i++) {
        levelState = logic(levels[i+1] - levels[i]);
        if (levelState && i<vectorSize-2) {
            return bruteForceCheckWindows(levels, i);
        }
    }

    return false;
}

const bool Levels::invalidDirection(const int &diff) {
    // set new direction
    enum Direction newDirection = Direction::INCREASING;
    if (diff < 0) newDirection = Direction::DECREASING;

    if (this->currDirection != Direction::STARTING && this->currDirection != newDirection) {
        return true;
    }

    this->currDirection = newDirection;

    return false;
};

int firstSolution(std::string fileName) {
    FileOps file(fileName);
    std::ifstream &fileContents = file.getFile();

    std::string line;
    int resultFirst;
    while (std::getline(fileContents, line)) {
        Levels levels(line);
        resultFirst += levels.isSafeFirst();
    }

    return resultFirst;
};


int secondSolution(std::string fileName) {
    FileOps file(fileName);
    std::ifstream &fileContents = file.getFile();

    std::string line;
    int resultSecond = 0;
    while (std::getline(fileContents, line)) {
        Levels levels(line);
        resultSecond += levels.isSafeSecond();
    }

    return resultSecond;
}

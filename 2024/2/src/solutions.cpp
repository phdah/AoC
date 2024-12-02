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
    if (abs(diff) > 3) {
        return true;
    }

    if (invalidDirection(diff)) {
        return true;
    }

    return false;
}

const bool Levels::noSafeLogicFirst(const std::vector<int> levels) {
    for (int i=0; i<levels.size()-1; i++) {
        if (logic(levels[i+1] - levels[i])) return true;
    }

    return false;
}

const bool Levels::noSafeLogicSecond(std::vector<int> &levels) {
    bool levelsState = false;
    int vectorSize = levels.size();
    for (int i=0; i<vectorSize-1; i++) {
        levelsState = logic(levels[i+1] - levels[i]);
        if (levelsState && this->noDropedLevel && i<vectorSize-2) {
            levels.erase(levels.begin()+i+1);
            vectorSize--;
            this->noDropedLevel = false;
            this->currDirection = this->prevDirection;
            if (logic(levels[i+1] - levels[i])) return true;
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

    this->prevDirection = this->currDirection; // save previous change
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

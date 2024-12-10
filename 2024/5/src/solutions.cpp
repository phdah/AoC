#include "solutions.h"

void Printer::setPageRule(const std::string &lh, const std::string &rh) {
    const int lhInt = std::stoi(lh);
    const int rhInt = std::stoi(rh);
    this->pageOrdersMap[lhInt].insert(rhInt);
};

void Printer::coutPageOrdersMap(const int &lh) {
    for (auto & val : this->pageOrdersMap[lh]) {
        std::cout << val << std::endl;
    }
};


const bool Printer::checkRule(const int&lh, const int &rh) {
    auto endMap = this->pageOrdersMap.end();
    if (this->pageOrdersMap.find(lh) != endMap) {
        auto endVec = this->pageOrdersMap[lh].end();
        if (this->pageOrdersMap[lh].find(rh) != endVec) {
            return true;
        }
    }

    return false;
};

const bool Printer::checkUpdate(const std::vector<int> &updateVec) {
    // Iterate over the vector values
    for (int i=1; i<updateVec.size(); i++) {
        // Check all previous values with the current one
        const int rh = updateVec[i]; // curr
        for (int j=0; j<i; j++) {
            const int lh = updateVec[j]; // prev
            if (!this->checkRule(lh, rh)) {
                return false;
            }
        }
    }

    return true;
};

const std::vector<int> Printer::reorderVector(const std::vector<int> &vec, const int &oldIndex, const int &newIndex) {
    std::vector<int> updatedVec;
    // Add all values before the newIndex, excluding the oldIndex
    for (int i=0; i<newIndex; i++) {
        if (i!=oldIndex) updatedVec.push_back(vec[i]);
    }
    // Add the oldIndex at the newIndex position
    updatedVec.push_back(vec[oldIndex]);
    // Add all remaining values after the newIndex, excluding the oldIndex
    for (int i=newIndex; i<vec.size(); i++) {
        if (i!=oldIndex) updatedVec.push_back(vec[i]);
    }

    return updatedVec;
}

const int Printer::recursiveCheckUpdate(const std::vector<int> &vec) {
    std::vector<int> updatedVec;
    // Iterate over the vector values
    for (int i=1; i<vec.size(); i++) {
        // Check all previous values with the current one
        const int rh = vec[i]; // curr
        for (int j=0; j<i; j++) {
            const int lh = vec[j]; // prev
            if (!this->checkRule(lh, rh)) {
                std::vector<int> updatedVec = this->reorderVector(vec, i, j);
                return this->recursiveCheckUpdate(updatedVec);
            }
        }
    }

    return vec[vec.size() / 2];
};


int firstSolution(std::string fileName) {
    FileOps file(fileName);
    std::ifstream &fileContents = file.getFile();
    Printer printer;

    int resultFirst = 0;
    std::string line, rule;
    while (std::getline(fileContents, line)) {
        // Debug cout of line
        /* std::cout << line << std::endl; */
        if (line == "\0") {
            printer.rulesDone = true;
            continue;
        }

        if (!printer.rulesDone) {
            int del = line.find('|');
            printer.setPageRule(line.substr(0,del), line.substr(del+1, line.size()));
        } else {
            Update update(line);
            if (printer.checkUpdate(update.vec)) {
                resultFirst += update.middleNumber;
            }
        }
    }

    return resultFirst;
};


int secondSolution(std::string fileName) {
    FileOps file(fileName);
    std::ifstream &fileContents = file.getFile();
    Printer printer;

    int resultSecond = 0;
    std::string line, rule;
    while (std::getline(fileContents, line)) {
        // Debug cout of line
        /* std::cout << line << std::endl; */
        if (line == "\0") {
            printer.rulesDone = true;
            continue;
        }

        if (!printer.rulesDone) {
            int del = line.find('|');
            printer.setPageRule(line.substr(0,del), line.substr(del+1, line.size()));
        } else {
            Update update(line);
            // If update is incorrect (a number can never be 0)
            // Made it easy for me, and find the initially wrong
            // updates using the part one solution first.
            if (printer.checkUpdate(update.vec) == 0) {
                resultSecond += printer.recursiveCheckUpdate(update.vec);
            }
        }
    }
    return resultSecond;
}

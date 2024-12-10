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

const int Printer::checkUpdate(const Update &update) {
    // Iterate over the vector values
    for (int i=1; i<update.vec.size(); i++) {
        // Check all previous values with the current one
        const int rh = update.vec[i]; // curr
        for (int j=0; j<i; j++) {
            const int lh = update.vec[j]; // prev
            if (!this->checkRule(lh, rh)) {
                return 0;
            }
        }
    }

    return update.middleNumber;
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
            resultFirst += printer.checkUpdate(update);
        }
    }

    return resultFirst;
};


int secondSolution(std::string fileName) {
    FileOps file(fileName);
    std::ifstream &fileContents = file.getFile();

    int resultSecond = 0;
    return resultSecond;
}

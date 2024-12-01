#include "solutions.h"

void FileOps::getLineContentTwoColumns(const std::string &line, std::vector<int> &rhVec, std::vector<int> &lhVec) {
    int first, second;
    std::istringstream lineSplit(line);
    lineSplit >> first >> second;
    rhVec.push_back(first);
    lhVec.push_back(second);
};

void FileOps::countVectorNumbers(std::vector<int> &resultVec, const std::vector<int> &inputVec) {
    for (auto &element : inputVec) {
        resultVec[element-1]++;
    }
};

int firstSolution(std::string fileName) {
    FileOps file(fileName);
    std::ifstream &fileContents = file.getFile();

    std::vector<int> rhVec, lhVec;
    std::string line;
    while (std::getline(fileContents, line)) {
        file.getLineContentTwoColumns(line, rhVec, lhVec);
    }
    fileContents.close();

    sort(rhVec.begin(), rhVec.end());
    sort(lhVec.begin(), lhVec.end());

    int resultFirst = 0;
    for (int i=0; i < rhVec.size(); i++) {
        Pair p(rhVec[i], lhVec[i]);
        resultFirst += p.diff;
    }

    return resultFirst;
};


int secondSolution(std::string fileName) {
    FileOps file(fileName);
    std::ifstream &fileContents = file.getFile();

    std::vector<int> rhVec, lhVec;
    std::string line;
    while (std::getline(fileContents, line)) {
        file.getLineContentTwoColumns(line, rhVec, lhVec);
    }
    fileContents.close();

    std::vector<int>  lhCountVec(lhVec.size(), 0);
    file.countVectorNumbers(lhCountVec, lhVec);

    int resultSecond = 0;
    for (auto & i : rhVec) {
        resultSecond += i * lhCountVec[i-1];
    }

    return resultSecond;
}

#include "solutions.h"
#include <string>
#include <regex>
#include <utility>

 const int Memory::multiplyMatch(std::pair<std::string, std::string> &matchPair) {
    return std::stoi(matchPair.first) * std::stoi(matchPair.second);
}
}

int firstSolution(std::string fileName) {
    FileOps file(fileName);
    std::ifstream &fileContents = file.getFile();

    // Match mul(123,456) and capture only the digits in groups
    const std::regex pat("mul\\(([0-9]{1,3}),([0-9]{1,3})\\)");
    std::pair<std::string, std::string> matchPair;

    int resultFirst = 0;
    int mult;
    std::string line;
    while (std::getline(fileContents, line)) {
        auto it = std::sregex_iterator(line.begin(), line.end(), pat);
        auto end = std::sregex_iterator();
        while (it != end) {
            std::smatch match = *it;
            matchPair = {match[1].str(), match[2].str()};
            resultFirst += Memory::multiplyMatch(matchPair);
            it++;
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

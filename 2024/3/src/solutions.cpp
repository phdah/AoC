#include "solutions.h"
#include <cstdio>
#include <string>
#include <regex>
#include <utility>

 const int Memory::multiplyMatch(std::pair<std::string, std::string> &matchPair) {
    return std::stoi(matchPair.first) * std::stoi(matchPair.second);
}
void Memory::switchMemoryState() {
    if (this->memoryState == MemoryState::ENABLED) {
        this->memoryState = MemoryState::DISABLED;
        return;
    }

    this->memoryState = MemoryState::ENABLED;
    return;
}

const int Memory::calculateMatches(std::string::iterator beginIt, std::string::iterator endIt) {
    // Match mul(123,456) and capture only the digits in groups
    const std::regex pat("mul\\(([0-9]{1,3}),([0-9]{1,3})\\)");
    std::pair<std::string, std::string> matchPair;

    // Create iterator search, using the iterators from the string
    auto it = std::sregex_iterator(beginIt, endIt, pat);
    auto end = std::sregex_iterator();

    int resultFirst = 0;
    while (it != end) {
        std::smatch match = *it;
        matchPair = {match[1].str(), match[2].str()};
        resultFirst += this->multiplyMatch(matchPair);
        it++;
    }
    return resultFirst;
}

const std::string Memory::getSearchString() {
    if (this->memoryState == MemoryState::ENABLED) {
        return this->delDont;
    }
    return this->delDo;
};

const std::string::iterator Memory::getDelEnd() {
    std::string::iterator delEndRestricted;
    std::size_t startPosNewSearch = this->prevStrEnd - this->line.begin();

    std::size_t delEnd = this->line.find(this->getSearchString(), startPosNewSearch);
    if (delEnd != std::string::npos) {
        delEndRestricted = delEnd + this->line.begin();
    } else {
        delEndRestricted = this->line.end();
    }
    return delEndRestricted;
};

const int Memory::findNextInterval() {
    int resultSecond = 0;
    std::string::iterator delEnd;

    while (this->prevStrEnd != line.end()) {
        if (this->memoryState == MemoryState::ENABLED) {
            delEnd = this->getDelEnd();
            std::string newLine = line.substr(this->prevStrEnd-line.begin(), delEnd-line.begin());
            resultSecond += this->calculateMatches(this->prevStrEnd, delEnd);
        } else {
            delEnd = this->getDelEnd();
        }
        // Update the previous starting pos and memory state
        this->switchMemoryState();
        this->prevStrEnd = delEnd;
    }

    return resultSecond;
}

int firstSolution(std::string fileName) {
    FileOps file(fileName);
    std::string line = file.getFileContentAsOneString();
    Memory memory(line);

    int resultFirst = 0;
    resultFirst += memory.calculateMatches(line.begin(), line.end());

    return resultFirst;
};


int secondSolution(std::string fileName) {
    FileOps file(fileName);
    std::string line = file.getFileContentAsOneString();
    Memory memory(line);

    int resultSecond = 0;
    resultSecond += memory.findNextInterval();

    return resultSecond;
}

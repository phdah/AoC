#include <cstdlib>
#include <regex>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>
#include <vector>

int firstSolution(std::string fileName);
int secondSolution(std::string fileName);

enum MemoryState {
    ENABLED,
    DISABLED
};

class Memory {
    public:
        Memory(std::string &line): line{line} {}

        const int calculateMatches(std::string::iterator beginIt, std::string::iterator endIt);

        const int findNextInterval();

    private:
        std::string &line;
        const std::string delDont = "don't()";
        const std::string delDo = "do()";

        std::string::iterator prevStrEnd = line.begin();
        enum  MemoryState memoryState = ENABLED;

        void switchMemoryState();
        const std::string::iterator getDelEnd();
        const std::string getSearchString();

        static const int multiplyMatch(std::pair<std::string, std::string> &matchPair);

};

class FileOps {
    public:
        FileOps(const std::string &fileName)
            : file(fileName) {
            if (!file) {
                std::cout << "Failed to read file: " << fileName << std::endl;
            }
        };

        // Get the file contents as is
        std::ifstream &getFile() {
            return file;
        };

        // Get all lines from the file as one string
        const std::string getFileContentAsOneString() {
            std::string line(
                (std::istreambuf_iterator<char>(this->file)),
                std::istreambuf_iterator<char>());
            return line;
        };

    private:
        std::ifstream file;

};

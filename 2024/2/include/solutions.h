#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

int firstSolution(std::string fileName);
int secondSolution(std::string fileName);

enum Direction {
    INCREASING,
    DECREASING,
    FLAT,
    STARTING
};

class Levels {
    public:
        Levels(const std::string &line): line(line) {};

        const int isSafeFirst();
        const int isSafeSecond();

    private:
        const std::string &line;
        bool noDropedLevel = true;

        enum Direction currDirection = STARTING;
        enum Direction prevDirection;

        const std::vector<int> getLevels();

        const bool logic(const int &diff);

        const bool noSafeLogicFirst(const std::vector<int> levels);
        const bool noSafeLogicSecond(std::vector<int> &levels);

        const bool invalidDirection(const int &diff);

};

class FileOps {
    public:
        FileOps(const std::string &fileName)
            : file(fileName) {
            if (!file) {
                std::cout << "Failed to read file: " << fileName << std::endl;
            }
        };

        // Get the file
        std::ifstream &getFile() {
            return file;
        };

    private:
        std::ifstream file;

};

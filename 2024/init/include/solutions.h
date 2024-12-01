#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

int firstSolution(std::string fileName);
int secondSolution(std::string fileName);

class Pair {
    public:
        int diff;
        Pair(const int &lh, const int &rh): lh{lh}, rh{rh} {
            diff = abs(rh - lh);
        };
    private:
        const int &lh;
        const int &rh;
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

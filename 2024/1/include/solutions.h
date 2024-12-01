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

        // Push column integers from a line onto two vectors
        void getLineContentTwoColumns(const std::string &line, std::vector<int> &rhVec, std::vector<int> &lhVec);

        // Count the number of entries of each number in a vector
        void countVectorNumbers(std::vector<int> &resultVec, const std::vector<int> &inputVec);

    private:
        std::ifstream file;

};

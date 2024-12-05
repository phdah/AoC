#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>
#include <vector>

int firstSolution(std::string fileName);
int secondSolution(std::string fileName);

class Matrix {
    public:
        Matrix(std::ifstream &file, std::string &pat): file(file), pat(pat) {
            std::vector<char> d1Vector;
            std::string line;
            while (std::getline(this->file, line)) {
                for (auto &c : line) {
                    d1Vector.push_back(c);
                }
                this->data.push_back(d1Vector);
                d1Vector.clear();
            }
            matrixSize = {this->data.size(), this->data[0].size()};
            marginalDown = this->matrixSize.first - this->patLength + 1;
            marginalRight = this->matrixSize.second - this->patLength + 1;
        };


        // Count the entire matrix, order of row -> column
        const int countNrPat();
        // Marginal lets the iteration skip edges since they will never work
        const int countNrStar(const int &marginal);

        // Search around char - Brut Force all directions
        const int countAroundCharPat(int &row, int &col);
        // Search around the char, and find the star
        const int countAroundCharStar(int &row, int &col);
        // Find out if the star matches the pattern
        const bool starMatch(char &rightUpper, char &leftUpper, char &rightDown, char &leftDown);

        // Decrement/increment vector
        const std::vector<int> decrementVec(const int startVal);
        const std::vector<int> incrementVec(const int startVal);

        // Get and check a string based on known vectors
        const int checkString(const std::vector<int> &rows, const std::vector<int> &cols);


        // Cout the entire matrix
        void cout();
        // Cout the dimensions: (rows, columns)
        void coutDim();


    private:
        std::string &pat;
        const int patLength = pat.size();

        const int marginalUp = this->patLength-2;
        const int marginalLeft = this->patLength-2;
        int marginalDown;
        int marginalRight;

        std::vector<std::vector<char>> data;
        std::pair<int, int> matrixSize;
        std::ifstream &file;
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

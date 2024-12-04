#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

int firstSolution(std::string fileName);
int secondSolution(std::string fileName);

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

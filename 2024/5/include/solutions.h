#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <strstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

int firstSolution(std::string fileName);
int secondSolution(std::string fileName);

class Update {
    public:
        Update(const std::string &line): line(line) {
            this->stringToVec();
            this->setMiddleNumber();
        };

    // Vector of update integers
    std::vector<int> vec;
    // Middle integer of the update vector
    int middleNumber;

    private:
        const std::string line;

        // Convert "," string to vector of int
        void stringToVec() {
            std::string number;
            std::stringstream s(this->line);
            while (std::getline(s, number, ',')) {
                this->vec.push_back(std::stoi(number));
            }
        };

        // Find and set middle number of vector
        void setMiddleNumber() {
            this->middleNumber = this->vec[(this->vec.size() / 2)];
        }

};

class Printer {
    public:
        Printer() {};
        // Populate the map<vec> with rules
        void setPageRule(const std::string &lh, const std::string &rh);
        // Check if the rule exists for the given input
        const bool checkRule(const int&lh, const int &rh);
        // Check if an entire update is correct, return middle number
        const int checkUpdate(const Update &update);

        // Util to cout the map
        void coutPageOrdersMap(const int &lh);
        // Boolean for when the rules have been processed
        bool rulesDone = false;
    private:
        // Map of each rule
        std::unordered_map<int, std::unordered_set<int>> pageOrdersMap;

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

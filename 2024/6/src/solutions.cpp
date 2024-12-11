#include "solutions.h"

int firstSolution(std::string fileName) {
    FileOps file(fileName);
    std::ifstream& fileContents = file.getFile();
    Matrix matrix(fileContents);
    // For debug only
    /* matrix.cout(); */

    bool trapped = true;
    while (trapped) {
        trapped = matrix.guardStep();
    }
    // For debug only
    /* std::cout << std::endl; */
    /* matrix.cout(); */

    int resultFirst = matrix.visitedPos.size();
    return resultFirst;
};

int secondSolution(std::string fileName) {
    FileOps file(fileName);
    std::ifstream& fileContents = file.getFile();

    int resultSecond = 0;
    return resultSecond;
}

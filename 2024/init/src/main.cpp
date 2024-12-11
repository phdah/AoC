#include "solutions.h"
#include <string>

int main(int argc, char** argv) {
    std::string fileName = "../example_input.txt";
    if (argc > 1) fileName = argv[1];

    int resultFirst = firstSolution(fileName);
    std::cout << "Result first: " << resultFirst << std::endl;

    int resultSecond = secondSolution(fileName);
    std::cout << "Result second: " << resultSecond << std::endl;

    return 0;
}

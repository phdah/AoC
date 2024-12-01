#include "solutions.h"
#include <string>

int main(int argc, char **argv) {

    int resultFirst = firstSolution(argv[1]);
    std::cout << "Result first: " << resultFirst << std::endl;

    int resultSecond = secondSolution(argv[1]);
    std::cout << "Result second: " << resultSecond << std::endl;

    return 0;
}

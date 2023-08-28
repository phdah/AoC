#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "game.h"

int main( int argc, char* argv[] ) {
    std::ifstream input(argv[1]);

    int sum1=0, sum2=0;

    std::string line;
    std::string word1, word2;

    NamespaceGame::Game game; // instance of Game

    while ( std::getline(input, line) ) {
        std::istringstream line_stream(line);
        line_stream >> word1 >> word2;
        sum1 += game.calculate(word1, word2);

        sum2 += game.reverse_calculate(word1, word2);

    }

    std::cout << "Task 1: " << sum1 << std::endl;
    std::cout << "Task 2: " << sum2 << std::endl;
    input.close();
    return 0;
}

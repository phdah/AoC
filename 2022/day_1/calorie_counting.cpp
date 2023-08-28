#include <iostream>
#include <fstream>
#include <vector>
#include "array_update.h"

int main( int argc, char* argv[] ) {
    std::ifstream input(argv[1]);
    int array_len = atoi(argv[2])-1;

    if ( !input ) {
        std::cerr << "Error reading file from " << argv[1] << std::endl;
        return 1;
    }

    std::vector<int> top_sum(array_len+1, 0);
    int sum=0;
    std::string line;
    while ( std::getline( input, line) ) {
        if ( line.empty() ) {
            top_sum = array_update(sum, top_sum, array_len);
            sum = 0;
        }
        else {
            const char* line_str = line.c_str();
            sum += atoi(line_str);
        }
    }

    for ( int i=array_len; i>=0; --i) {
        sum += top_sum[i];
        std::cout << top_sum[i] << std::endl;
    }
    printf("\nTotal sum: %d\n", sum);

    input.close();
    return 0;

}

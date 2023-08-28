#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define str_l 10

int main(int argc, char** argv)
{

    // define input
    FILE* ptr = fopen(argv[1], "r");
    char str[str_l];

    // define main objects
    int total_signal=0;
    int prev_iterative_signal=1;
    int iterative_signal=1;

    unsigned int cycle=0;
    unsigned int iterative_cycle=0;
    unsigned short first_run=0;

    char x_char[str_l]={0};
    unsigned short c;
    int x;

    while ( fgets(str, str_l, ptr) != NULL ) {
        if ( str[0] == 'a' ) {
            c=0;
            while ( str[5+c] != '\n') {
                x_char[c] = str[5+c];
                ++c;
            }
            iterative_signal += atoi(x_char);
            memset(x_char, 0, sizeof(x_char));
            iterative_cycle += 2;
            cycle += 2;
        }
        else {
            iterative_cycle += 1;
            cycle += 1;
        }

        if (  iterative_cycle >= 40 || ( cycle >= 20 && !first_run ) ) {
            total_signal += prev_iterative_signal * ( (cycle / 10) * 10);
            if ( iterative_cycle >= 40 ) {
                iterative_cycle -= 40;
            }
            else {
                iterative_cycle -= 20;
            }
            ++first_run;
        }
        else if (iterative_cycle == 40 || ( cycle == 20 && !first_run ) ) {
            total_signal += iterative_signal * ( (cycle / 10) * 10);
            if ( iterative_cycle >= 40 ) {
                iterative_cycle -= 40;
            }
            else {
                iterative_cycle -= 20;
            }
            ++first_run;
        }

        prev_iterative_signal = iterative_signal;

    }

    printf("%d\n", total_signal);


    fclose(ptr);
    return 0;
}

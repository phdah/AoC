#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define str_l 10
#define cycle_tick 40

int main(int argc, char** argv)
{

    // define input
    FILE* ptr = fopen(argv[1], "r");
    char str[str_l];

    // define main objects
    int prev_iterative_signal=1;
    int iterative_signal=1;

    unsigned short pixle=0;

    unsigned int cycle=0;
    unsigned short input_cycle;

    char x_char[str_l]={0};
    unsigned short c;

    while ( fgets(str, str_l, ptr) != NULL ) {
        // if addx
        if ( str[0] == 'a' ) {
            c=0;
            while ( str[5+c] != '\n') {
                x_char[c] = str[5+c];
                ++c;
            }
            // update signal strength
            iterative_signal += atoi(x_char);
            // reset char buffer
            memset(x_char, 0, sizeof(x_char));

            // loops over two cycles
            input_cycle=0;
            while ( input_cycle < 2 ) {
                // check if pixle is within window of 3
                if ( abs(prev_iterative_signal - pixle) < 2 ) {
                    ++pixle;
                    printf("#");
                }
                else {
                    ++pixle;
                    printf(".");
                }
                ++cycle;
                ++input_cycle;
                // switch row if reaching cycles of 40
                if ( (cycle % cycle_tick) == 0 ) {
                    printf("\n");
                    pixle=0;
                }
            }

        }
        // if noop
        else {
            // check if pixle is within window of 3
            if ( abs(prev_iterative_signal - pixle) < 2 ) {
                ++pixle;
                printf("#");
            }
            else {
                ++pixle;
                printf(".");
            }
            ++cycle;
            // switch row if reaching cycles of 40
            if ( (cycle % cycle_tick) == 0 ) {
                printf("\n");
                pixle=0;
            }
        }

        // update previous signal strength after cycles
        prev_iterative_signal = iterative_signal;

    }

    fclose(ptr);
    return 0;
}

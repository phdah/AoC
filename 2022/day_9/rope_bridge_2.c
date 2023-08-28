// https://adventofcode.com/2022/day/9
#include <stdio.h>
#include <stdlib.h>
#include "rope.h"

#define str_l 20

int main(int argc, char** argv)
{

    FILE* ptr = fopen(argv[1], "r");
    char str[str_l];
    char direction;
    char moves_char[str_l]={0};
    int moves;

    // initialize visited sum and map
    int visited=1;
    int** map=(int**)calloc(map_mid*2, sizeof(int));
    for ( int i=0; i < map_mid*2; i++ )
        map[i]=(int*)calloc(map_mid*2, sizeof(int));
    map[map_mid][map_mid]=1;

    // initialize head and tail position
    BridgePoint posHead;
    posHead.nr = 0;
    posHead.x = map_mid;
    posHead.y = map_mid;

    createPoint(&posHead, num_tails);

    int digit;

    while ( fgets(str, str_l, ptr) != NULL ) {
        direction=str[0];
        digit=2; // digit alwasy start on the 3rd byte
        while ( str[digit] != '\n' ) {
            moves_char[digit-2] = str[digit];
            ++digit;
        }
        moves = atoi(moves_char);

        while ( moves > 0 ) {
            moveHead(&posHead, direction);

            checkTail(map, &visited, &posHead, posHead.tail);

            --moves;
        }
        digit=0;
        while ( str[digit] != '\n' ) {
            moves_char[digit] = 0;
            ++digit;
        }

    }

    printf("%d\n", visited);

    freePoint(posHead.tail);
    free(posHead.tail->tail->tail);
    for ( int i=0; i < map_mid*2; i++ )
        free(map[i]);
    free(map);
    fclose(ptr);
    return 0;
}

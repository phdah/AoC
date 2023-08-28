// https://adventofcode.com/2022/day/9
#include <stdio.h>
#include <stdlib.h>

#define str_l 20
#define map_mid 12000

typedef struct BridgePoint {
    unsigned int x;
    unsigned int y;
} BridgePoint;

void checkNewPosition(int** map, int* visited, unsigned int x, unsigned int y)
{
    if ( map[x][y] == 0 ) {
        map[x][y]=1;
        ++*visited;
    }
}


void moveHead(BridgePoint* point, BridgePoint* old_point, char dir)
{
    // save old state
    old_point->x=point->x;
    old_point->y=point->y;

    // y: up and down
    if ( dir=='U' ) {
        ++point->y;
    }
    if ( dir=='D' ) {
        --point->y;
    }

    // x: right->and left
    if ( dir=='R' ) {
        ++point->x;
    }
    if ( dir=='L' ) {
        --point->x;
    }

}

void checkTail(int** map, int* visited, BridgePoint* head, BridgePoint* old_head, BridgePoint* tail, char dir)
{
    // check distance to head
    int head_x = head->x;
    int head_y = head->y;
    int tail_x = tail->x;
    int tail_y = tail->y;

    int dist = abs(head_x - tail_x) + abs(head_y - tail_y);
    int dist_x = abs(head_x - tail_x);
    int dist_y = abs(head_y - tail_y);
    //printf("dist %d\n ", dist);

    // move tail
    if ( dist > 1 ) {
        if ( dist > 2 && dist_x > 0 && dist_y > 0 ) {
            tail->x=old_head->x;
            tail->y=old_head->y;
            checkNewPosition(map, visited, tail->x, tail->y);
        }
        else if ( ( dist_x > 0) != ( dist_y > 0 ) ) {
            tail->x=old_head->x;
            tail->y=old_head->y;
            checkNewPosition(map, visited, tail->x, tail->y);
        }
    }

}

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
    //int map[map_mid*2][map_mid*2]={{0}};
    map[map_mid][map_mid]=1;

    // initialize head and tail position
    BridgePoint posHead;
    posHead.x = map_mid;
    posHead.y = map_mid;

    BridgePoint old_posHead=posHead;

    BridgePoint posTail;
    posTail.x = map_mid;
    posTail.y = map_mid;

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
            moveHead(&posHead, &old_posHead, direction);

            checkTail(map, &visited, &posHead, &old_posHead, &posTail, direction);

//    for ( int y=14; y > 9; y-- ) {
//        for ( int x=10; x < 16; x++ ) {
//        printf("%d", map[x][y]);
//        }
//        printf("\n");
//    }
            --moves;
        }
        digit=0;
        while ( str[digit] != '\n' ) {
            moves_char[digit] = 0;
            ++digit;
        }

    }

    printf("%d\n", visited);
    fclose(ptr);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "rope.h"
void checkNewPosition(int** map, int* visited, unsigned int x, unsigned int y)
{
    if ( map[x][y] == 0 ) {
        map[x][y]=1;
        ++*visited;
    }
}


void moveHead(BridgePoint* point, char dir)
{
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

void checkTail(int** map, int* visited, BridgePoint* head, BridgePoint* tail)
{

    if ( !head->tail ) {
        checkNewPosition(map, visited, head->x, head->y);
    }
    else {
        // check distance to head
        int head_x = head->x;
        int head_y = head->y;
        int tail_x = tail->x;
        int tail_y = tail->y;

        int dist = abs(head_x - tail_x) + abs(head_y - tail_y);
        int dist_x = abs(head_x - tail_x);
        int dist_y = abs(head_y - tail_y);

        // move tail
        if ( dist > 1 ) {
            // move in horizontal/vertical direction
            if ( dist_x == 0 || dist_y == 0 ) {
                // move in x
                if ( tail_x < head_x ) {
                    ++tail->x;
                }
                if ( tail_x > head_x ) {
                    --tail->x;
                }

                // move in y
                if ( tail_y < head_y ) {
                    ++tail->y;
                }
                if ( tail_y > head_y ) {
                    --tail->y;
                }
            }
            // move in diagonal direction
            else if ( dist > 2 ) {
                // move up+right
                if ( tail_x < head_x && tail_y < head_y ) {
                    ++tail->x;
                    ++tail->y;
                }
                // move up+left
                if ( tail_x > head_x && tail_y < head_y ) {
                    --tail->x;
                    ++tail->y;
                }
                // move down+right
                if ( tail_x < head_x && tail_y > head_y ) {
                    ++tail->x;
                    --tail->y;
                }
                // move down+left
                if ( tail_x > head_x && tail_y > head_y ) {
                    --tail->x;
                    --tail->y;
                }
            }
            checkTail(map, visited, tail, tail->tail);
        }
    }
}

void createPoint(BridgePoint* head, int iteration)
{
    BridgePoint* point=(BridgePoint*)malloc(sizeof(BridgePoint));
    point->nr = num_tails - iteration + 1;
    point->x = map_mid;
    point->y = map_mid;
    point->head = head;

    head->tail = point;

    if ( iteration > 0 )
        createPoint(point, --iteration);
}

void freePoint(BridgePoint* head)
{
    if ( head->tail ) {
        freePoint(head->tail);
    }
    free(head);
}

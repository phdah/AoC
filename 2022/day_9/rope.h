#ifndef ROPE_H
#define ROPE_H

#define map_mid 12000
#define num_tails 8

typedef struct BridgePoint {
    unsigned int nr;
    unsigned int x;
    unsigned int y;
    BridgePoint* head;
    BridgePoint* tail=NULL;
} BridgePoint;

void checkNewPosition(int**, int*, unsigned int, unsigned int);

void moveHead(BridgePoint*, char);

void checkTail(int**, int*, BridgePoint*, BridgePoint*);

void createPoint(BridgePoint*, int);

void freePoint(BridgePoint*);

#endif

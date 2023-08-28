// https://adventofcode.com/2022/day/2
#include <stdio.h> // printf
#include <stdlib.h> // fopen, fgets, fclose

int main(int argc, char** argv)
{

  FILE* ptr = fopen(argv[1], "r");
  char str[6];

  int outcome;
  int opponent;
  int me;

  int myscore=0;

  while ( fgets(str, 6, ptr) != NULL ) {
    // 1 = rock, 2 = paper, 3 = scissors
    opponent = str[0]-64;
    me = str[2]-87;

    outcome = opponent == 3 && (me-opponent)<0 ? (me - opponent + 3) : (me - opponent);

    myscore += 6*(outcome == 1) + 3*(outcome == 0) + me;

  }
  printf("%d\n", myscore);

  return 0;
}

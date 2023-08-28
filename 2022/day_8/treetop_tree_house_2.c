// https://adventofcode.com/2022/day/8
#include <stdio.h>
#include <stdlib.h>
#include "treetop.h"

#define str_l 101


int main(int argc, char** argv)
{

  FILE* ptr = fopen(argv[1], "r");
  char str[str_l];
  char map[map_l][map_l];

  int highest_scenic_score=0;
  int tree_scenic_score=0;

  int width=0;
  int height=1;

  fgets(str, str_l, ptr);

  while ( str[width] != '\n' ) {
    map[0][width] = str[width];
    ++width;
  }

  int i;

  while ( fgets(str, str_l, ptr) != NULL ) {
    i = 0;
    while ( i < width ) {
      map[height][i] = str[i];
      ++i;
    }
    ++height;
  }

  i=1;
  int j=1;

  while ( i < width-1 ) {
    while ( j < height-1 ) {
      tree_scenic_score = heightCheck(map, j, i, height, width);
      if ( tree_scenic_score >  highest_scenic_score ) {
         highest_scenic_score = tree_scenic_score;
      }
      ++j;
    }
    ++i;
    j=1;
  }
  printf("%d\n", highest_scenic_score);

  fclose(ptr);
  return 0;
}

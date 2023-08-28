// https://adventofcode.com/2022/day/8
#include <stdio.h>
#include <stdlib.h>

#define str_l 101
#define map_l 99

int heightCheck(char map[map_l][map_l], int height, int width, int max_height, int max_width)
{

  int blocked=0;

  int i=1;


  // up
  while ( height-i >= 0 ) {
    if ( map[height][width] <= map[height-i][width] ) {
      ++blocked;
      break;
    }
    ++i;
  }
  i=1;
  // down
  while ( height+i < max_height ) {
    if ( map[height][width] <= map[height+i][width] ) {
      ++blocked;
      break;
    }
    ++i;
  }
  i=1;
  // left
  while ( width-i >= 0 ) {
    if ( map[height][width] <= map[height][width-i] ) {
      ++blocked;
      break;
    }
    ++i;
  }
  i=1;
  // right
  while ( width+i < max_width ) {
    if ( map[height][width] <= map[height][width+i] ) {
      ++blocked;
      break;
    }
    ++i;
  }


  if ( blocked == 4 ) {
    return 0;
  } else {
    return 1;
  }

}

int main(int argc, char** argv)
{

  FILE* ptr = fopen(argv[1], "r");
  char str[str_l];
  char map[map_l][map_l];

  int visable_tree=0;

  int width=0;
  int height=1;

  fgets(str, str_l, ptr);

  while ( str[width] != '\n' ) {
    map[0][width] = str[width];
    ++width;
  }
  visable_tree += width*2;

  int i;

  while ( fgets(str, str_l, ptr) != NULL ) {
    i = 0;
    while ( i < width ) {
      map[height][i] = str[i];
      ++i;
    }
    ++height;
  }

  visable_tree += (height*2) - 4; // remove 4 for the corners

  i=1;
  int j=1;

  while ( i < width-1 ) {
    while ( j < height-1 ) {
      visable_tree += heightCheck(map, j, i, height, width);
      ++j;
    }
    ++i;
    j=1;
  }
  printf("%d\n", visable_tree);

  fclose(ptr);
  return 0;
}

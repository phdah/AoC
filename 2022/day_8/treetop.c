#include "treetop.h"
int heightCheck(char map[map_l][map_l], int height, int width, int max_height, int max_width)
{

  int view=1;

  int i=1;


  // up
  while ( height-i >= 0 ) {
    if ( map[height][width] <= map[height-i][width] ) {
      ++i;
      break;
    }
    ++i;
  }
  view*=(i-1);
  i=1;
  // down
  while ( height+i < max_height ) {
    if ( map[height][width] <= map[height+i][width] ) {
      ++i;
      break;
    }
    ++i;
  }
  view*=(i-1);
  i=1;
  // left
  while ( width-i >= 0 ) {
    if ( map[height][width] <= map[height][width-i] ) {
      ++i;
      break;
    }
    ++i;
  }
  view*=(i-1);
  i=1;
  // right
  while ( width+i < max_width ) {
    if ( map[height][width] <= map[height][width+i] ) {
      ++i;
      break;
    }
    ++i;
  }
  view*=(i-1);


  return view;

}

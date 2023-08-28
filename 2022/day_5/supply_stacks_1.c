// https://adventofcode.com/2022/day/5
#include <stdio.h>
#include <stdlib.h>

void printStack(int box_stack[9][50])
{
  int i=9;
  int j=0;
  while ( i > 0) {
    while ( j < 9 ) {
      printf("[%c] ", box_stack[j][i-1]);
      ++j;
    }
    j=0;
    --i;
    printf("\n");
  }
  printf("\n");
}

int main(int argc, char** argv)
{

  FILE* ptr_boxes = fopen(argv[1], "r");
  char str_boxes[100];

  unsigned short box_height=7; //for input use 7; 2
  unsigned short box_input_width=0;
  unsigned short box_width=0;
  unsigned short box_place=1;

  // for input, use [3][4] - [8],[100]
  int box_stack[9][50]={0};
  int col_height[9]={0};

  while ( fgets(str_boxes, 100, ptr_boxes) != NULL ) {
    while ( box_input_width < 9) { // set limit to be 8 for input
      // assign value to place in box stack
      box_stack[box_width][box_height] = str_boxes[box_place];
      if ( !col_height[box_width] && str_boxes[box_place] > 64 && str_boxes[box_place] < 91 ) {
        col_height[box_width] = box_height;
      }

      // iterate right in stack
      ++box_width;
      ++box_input_width;
      box_place +=4;
    }
    box_width=0;
    box_input_width=0;
    box_place=1;
    // iterate down in stack
    --box_height;
  }

  printf("Starting stack:\n");
  printStack(box_stack);


  FILE* ptr_moves = fopen(argv[2], "r");
  char str_moves[50];

  unsigned short moves_start=0;
  char moves_char[2];
  unsigned short moves;
  unsigned short from_col;
  unsigned short to_col;

  while ( fgets(str_moves, 50, ptr_moves) != NULL ) {
    moves_char[0]=str_moves[5];
    moves_char[1]=str_moves[6];
    moves = atoi(moves_char);
    if ( str_moves[6] > 47 ) {
      ++moves_start;
    }
    from_col = str_moves[12+moves_start]-49;
    to_col = str_moves[17+moves_start]-49;
    moves_start=0;

    while ( moves > 0 ) {
      box_stack[to_col][col_height[to_col]+1] = box_stack[from_col][col_height[from_col]];
      box_stack[from_col][col_height[from_col]] = 0;

      col_height[to_col] = col_height[to_col] + 1;
      col_height[from_col] = col_height[from_col] - 1;

      --moves;
    }
    printStack(box_stack);

  }

  for (int k = 0; k < 9; k++) {
    printf("%c", box_stack[k][col_height[k]]);
  }
  printf("\n");

  fclose(ptr_boxes);
  fclose(ptr_moves);
  return 0;
}

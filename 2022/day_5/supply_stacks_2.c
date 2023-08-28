// https://adventofcode.com/2022/day/5
#include <stdio.h>
#include <stdlib.h>

#define n 9//3 // number of stacks/columns

void printStack(int box_stack[n][50])
{
  int i=n+1;
  int j=0;
  while ( i > 0) {
    while ( j < n ) {
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

  // Initial box stack //
  FILE* ptr_boxes = fopen(argv[1], "r");
  char str_boxes[100];

  unsigned short box_height=n-1; //for input use 7; 2
  unsigned short box_input_width=0;
  unsigned short box_width=0;
  unsigned short box_place=1;

  int box_stack[n][50]={0};
  int col_height[n]={0};

  while ( fgets(str_boxes, 100, ptr_boxes) != NULL ) {
    while ( box_input_width < n) {
      // assign value to place in box stack
      box_stack[box_width][box_height] = str_boxes[box_place];
      if ( !col_height[box_width] && str_boxes[box_place] > 64 && str_boxes[box_place] < 91 ) {
        col_height[box_width] = box_height+1;
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
  // Done with initial box stack//


  // Initializing moving //
  FILE* ptr_moves = fopen(argv[2], "r");
  char str_moves[50];

  unsigned short moves_start=0;
  char moves_char[2];
  unsigned short moves;
  unsigned short from_col;
  unsigned short to_col;

  unsigned short total_moves;
  unsigned short from_height;
  unsigned short to_height;

  while ( fgets(str_moves, 50, ptr_moves) != NULL ) {
    printf("%s\n", str_moves);
    moves_char[0]=str_moves[5];
    moves_char[1]=str_moves[6];
    moves = atoi(moves_char);
    if ( str_moves[6] > 47 ) {
      ++moves_start;
    }
    from_col = str_moves[12+moves_start]-49;
    to_col = str_moves[17+moves_start]-49;
    moves_start=0;

    total_moves=moves;
    from_height = col_height[from_col];
    to_height = col_height[to_col];

    col_height[to_col] = col_height[to_col] + moves;
    col_height[from_col] = col_height[from_col] - moves;

    // I could have used memcpy() to move the bytes, instead of while looping
    while ( moves > 0 ) {
      box_stack[to_col][to_height+(total_moves-moves)] = box_stack[from_col][from_height-moves];
      box_stack[from_col][from_height-moves] = 32;

      --moves;
    }
    printStack(box_stack);

  }

  for (int k = 0; k < n; k++) {
    printf("%c", box_stack[k][col_height[k]-1]);
  }
  printf("\n");
  // Done with moving boxes //

  fclose(ptr_boxes);
  fclose(ptr_moves);
  return 0;
}

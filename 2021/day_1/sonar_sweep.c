// https://adventofcode.com/2021/day/1
#include <stdio.h>
#include <stdlib.h>

//char read_file(char* )
int n=1;

int main()
{

  FILE* ptr = fopen("input.txt", "r");
  char str[50];

  int stack_array[5000];
  int* previous_ptr;
  int* current_ptr;
  int i=0;
  int count=0;

  while ( fgets(str, 50, ptr) != NULL )
    stack_array[i++]= atoi(str);

  fclose(ptr);

  previous_ptr = stack_array;
  current_ptr = stack_array + n;

  while ( current_ptr <= stack_array + i ) {
    if ( *previous_ptr++ < *current_ptr++ )
      ++count;

  }

  printf("%d\n", count);

  return 0;
}

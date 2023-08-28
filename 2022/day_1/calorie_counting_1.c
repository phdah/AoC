// https://adventofcode.com/2022/day/1
#include <stdio.h> // printf
#include <stdlib.h> // fopen, fgets, fclose


int main(int argc, char** argv)
{

  FILE* ptr = fopen(argv[1], "r");
  char str[50];

  int current_calorie_sum=0;
  int max_calorie_sum=0;


  while ( fgets(str, 50, ptr) != NULL ) {
    if ( !atoi(str) ) {
      if ( current_calorie_sum > max_calorie_sum ) max_calorie_sum = current_calorie_sum;
      current_calorie_sum = 0;
    } else {
      current_calorie_sum += atoi(str);
    }

  }
  printf("%d\n", max_calorie_sum);
  fclose(ptr);

  return 0;
}

// https://adventofcode.com/2022/day/1
#include <stdio.h> // printf
#include <stdlib.h> // fopen, fgets, fclose

int n=3;

int main(int argc, char** argv)
{

  FILE* ptr = fopen(argv[1], "r");
  char str[50];

  int current_calorie_sum=0;
  int max_calorie_sum[3]={0};
  int max_calorie=0;

  while ( fgets(str, 50, ptr) != NULL ) {
    if ( !atoi(str) ) {
      if ( current_calorie_sum > max_calorie_sum[0] ) {
        max_calorie_sum[2] = max_calorie_sum[1];
        max_calorie_sum[1] = max_calorie_sum[0];
        max_calorie_sum[0] = current_calorie_sum;
      }
      else if ( current_calorie_sum > max_calorie_sum[1] ) {
        max_calorie_sum[2] = max_calorie_sum[1];
        max_calorie_sum[1] = current_calorie_sum;
      }
      else if ( current_calorie_sum > max_calorie_sum[2] ) {
        max_calorie_sum[2] = current_calorie_sum;
      }
      current_calorie_sum = 0;
    } else {
      current_calorie_sum += atoi(str);
    }

  }
  for ( int i = 0; i < n; i++ )
    max_calorie += max_calorie_sum[i];

  printf("%d\n", max_calorie);
  fclose(ptr);

  return 0;
}

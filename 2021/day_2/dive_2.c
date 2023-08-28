// https://adventofcode.com/2021/day/2
#include <stdio.h> // printf
#include <stdlib.h> // fopen, fgets, fclose


int main()
{

  FILE* ptr = fopen("input.txt", "r");
  char str[50];


  int position=0;
  int depth=0;
  int aim=0;

  while ( fgets(str, 50, ptr) != NULL ) {
    switch (str[0]){
      case 102:
        position += str[8]-48;
        depth += (str[8]-48) * aim;
        break;
      case 100:
        aim += str[5]-48;
        break;
      case 117:
        aim -= str[3]-48;
        break;


    }
  }

  printf("%d\n", position * depth);

  return 0;

}

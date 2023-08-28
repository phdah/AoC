// https://adventofcode.com/2022/day/4
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void stringSplitter(char* value, char* firstMin, char* firstMax, char* secondMin, char* secondMax)
{

  unsigned short i=0;
  unsigned short j=0;
  unsigned short k=0;

  while ( value[i] != '\n' ) {
    // first bound
    if ( j == 0 ) {
      if ( value[i] == '-' ) {
        ++j;
        k=0;
      } else {
        firstMin[k] = value[i];
        ++k;
      }
    }
    else if ( j == 1 ) {
      if ( value[i] == ',' ) {
        ++j;
        k=0;
      } else {
        firstMax[k] = value[i];
        ++k;
      }
    }

    // second bound
    else if ( j == 2 ) {
      if ( value[i] == '-' ) {
        ++j;
        k=0;
      } else {
        secondMin[k] = value[i];
        ++k;
      }
    }
    else if ( j == 3 ) {
      secondMax[k] = value[i];
      ++k;
    }

  ++i;
  }

}

int main(int argc, char** argv)
{

  FILE* ptr = fopen(argv[1], "r");
  char str[50];

  char firstMin[10];
  char firstMax[10];
  char secondMin[10];
  char secondMax[10];

  unsigned int count=0;

  while ( fgets(str, 50, ptr) != NULL ) {
    // reset the char array
    memset(firstMin, 0, 10);
    memset(firstMax, 0, 10);
    memset(secondMin, 0, 10);
    memset(secondMax, 0, 10);

    stringSplitter(str, firstMin, firstMax, secondMin, secondMax);

    if ( ( atoi(firstMin) <= atoi(secondMin) && atoi(firstMax) >= atoi(secondMax) ) ||  ( atoi(firstMin) >= atoi(secondMin) && atoi(firstMax) <= atoi(secondMax) ) ) {
      ++count;
    }

  }
  printf("%d\n", count);

  fclose(ptr);
  return 0;
}

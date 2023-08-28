// https://adventofcode.com/2022/day/3
#include <stdio.h> // printf
#include <stdlib.h> // fopen, fgets, fclose

int findMatch(char value[50], unsigned short length);

int main(int argc, char** argv)
{

  FILE* ptr = fopen(argv[1], "r");
  char str[50];

  unsigned short matchingValue;
  unsigned int matchingSums = 0;


  while ( fgets( str, 50, ptr) != NULL ) {

    // length of input string
    unsigned short length=0;
    while ( str[++length] != '\n' ) {}

    matchingValue = findMatch(str, length);
    matchingSums += matchingValue > 96 ? matchingValue - 96 : matchingValue - 38;

  }

  printf("Matching sum: %d\n", matchingSums);

  fclose(ptr);
  return 0;
}

int findMatch(char value[50], unsigned short length)
{
  for ( int i = 0; i < length/2; i++ ) {
    for ( int j = (length/2); j < length; j++ ) {
      if ( value[i] == value[j] ) {
        return value[i];
      }
    }

  }
  return 64;

}

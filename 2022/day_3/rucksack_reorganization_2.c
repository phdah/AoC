// https://adventofcode.com/2022/day/3
#include <stdio.h> // printf
#include <stdlib.h> // fopen, fgets, fclose

void findMatch(char value[50], char comp[50], char (*match)[50]);

int main(int argc, char** argv)
{

  FILE* ptr = fopen(argv[1], "r");
  char str[50];
  char comp[50];
  char match[50];
  char matchingValue[50];

  unsigned int matchingSums=0;

  unsigned short alf=0;
  unsigned short length;

  while ( fgets( str, 50, ptr) != NULL ) {

    if ( alf == 1 ) {
      findMatch(str, comp, &match);
      ++alf;
    }
    else if ( alf == 2) {
      findMatch(match, str, &matchingValue);
      matchingSums += matchingValue[0] > 96 ? matchingValue[0] - 96 : matchingValue[0] - 38;
      alf = 0;

    }
    else {
      length=0;
      while ( str[length] != '\n' ) {
        comp[length] = str[length];
        ++length;
      }
      comp[length] = '\n';
      ++alf;
    }

  }

  printf("%d\n", matchingSums);

  fclose(ptr);
  return 0;
}

void findMatch(char value[50], char comp[50], char (*match)[50])
{
  unsigned short i=0;
  unsigned short j=0;
  unsigned short k=0;

  while ( value[i] != '\n' ) {
    while ( comp[j] != '\n' ) {
      if ( value[i] == comp[j] ) {
        (*match)[k++] = value[i];
      }
      ++j;
    }
    j=0;
    ++i;
  }
  (*match)[k] = '\n';
}

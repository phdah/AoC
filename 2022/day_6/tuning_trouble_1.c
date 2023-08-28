// https://adventofcode.com/2022/day/6
#include <stdio.h>
#include <stdlib.h>

#define n 14 // the number of values to check for
#define m 26 // number of letters

int main(int argc, char** argv)
{

  FILE* ptr = fopen(argv[1], "r");
  char str[5000];

  int check[m]={0};
  int curr;

  int i=0;
  int k=0;
  int duplicate=0;

  fgets(str, 5000, ptr);
  while ( str[i] != '\n' ) {
    if ( i > (n-2) ) {
      for ( int j=0; j < n; j++ ) {
        check[str[i-j]-97] += 1;
      }
      for ( int j=0; j < n; j++ ) {
        if ( check[str[i-j]-97] > 1 ) {
          duplicate=1;
        }
        check[str[i-j]-97]=0;
      }
      if ( !duplicate ) {
        printf("Found %d unique values after: %d\n", n, i+1);
        return 0;
      }
      duplicate=0;
    }
    ++i;
  }



  fclose(ptr);
  return 0;
}

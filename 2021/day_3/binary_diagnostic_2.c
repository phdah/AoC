// https://adventofcode.com/2021/day/3
#include <stdio.h> // printf
#include <stdlib.h> // fopen, fgets, fclose
#include <math.h> // pow


int main(int argc, char** argv) // array of strings, array of chars
{

  FILE* ptr = fopen(argv[1], "r");
  char str[50];

  int length_binary=0;
  float* gamma_count;

  int power_consumption;
  int epsilon_rate=0;
  int gamma_rate=0;

  short* array = (short*)calloc(5000, 2);

  float i=0;

  while ( fgets(str, 50, ptr) != NULL ) {
    if ( !length_binary ) {
      while ( str[length_binary++] != '\0' ) {}
      length_binary -= 2;
      gamma_count = (float*)calloc(length_binary, 4);

    }

    for ( int j = 0; j < length_binary; j++ )
      gamma_count[j] += str[j]-48;
    ++i;
  }

  for ( int k = 0; k < length_binary; k++ ) {
    gamma_rate += (gamma_count[k] / i) < 0.5 ? 0 : pow(2, length_binary-1-k);
    epsilon_rate += (gamma_count[k] / i) > 0.5 ? 0 : pow(2, length_binary-1-k);
  }

  // Free allocated memory
  free(gamma_count);
  free(array);

  // print result
  printf("Power consumption: %d\n", gamma_rate * epsilon_rate);

  fclose(ptr);

  return 0;

}

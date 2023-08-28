// https://adventofcode.com/2022/day/2
#include <stdio.h> // printf
#include <stdlib.h> // fopen, fgets, fclose

int setMyChoice(int *outcome, int *opponent, int *me); // define function that depend on main

int calculateScore(int *myscore, int *opponent, int *me); // define function that depends on main

int main(int argc, char** argv)
{

  FILE* ptr = fopen(argv[1], "r");
  char str[6];

  int outcome;
  int opponent;
  int me;

  int myscore=0;

  while ( fgets(str, 6, ptr) != NULL ) {
    // 1 = loose, 2 = draw, 3 = win
    outcome = str[2]-87;
    // 1 = rock, 2 = paper, 3 = scissors
    opponent = str[0]-64;
    setMyChoice(&outcome, &opponent, &me);

    myscore += me; // add score for my choice

    calculateScore(&myscore, &opponent, &me);

  }
  printf("%d\n", myscore);

  return 0;
}

int setMyChoice(int *outcome, int *opponent, int *me)
{
  // loose = 1
  if ( *outcome == 1 ) {
    if ( *opponent == 1 )
      *me = 3;
    else if ( *opponent == 2 )
      *me = 1;
    else
      *me = 2;
  }
  // draw = 2
  if ( *outcome == 2 )
    *me = *opponent;
  // win = 3
  if ( *outcome == 3 ) {
    if ( *opponent == 1 )
      *me = 2;
    else if ( *opponent == 2 )
      *me = 3;
    else
      *me = 1;
  }

}

int calculateScore(int *myscore, int *opponent, int *me)
{
  // Opponent rock = 1
  if ( *opponent == 1 ) {
    if ( *me == 1 )
      *myscore += 3; // draw
    else if ( *me == 2)
      *myscore += 6; // victory
  }
  // Opponent paper = 2
  if ( *opponent == 2 ) {
    if ( *me == 2 )
      *myscore += 3; // draw
    else if ( *me == 3)
      *myscore += 6; // victory
  }
  // Opponent siccors = 3
  if ( *opponent == 3 ) {
    if ( *me == 3 )
      *myscore += 3; // draw
    else if ( *me == 1)
      *myscore += 6; // victory
  }
  return 0;
}

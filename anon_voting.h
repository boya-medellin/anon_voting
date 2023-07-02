#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#define OUTPUT "output.txt"

int polynomial(int x, int a, int b, int vote){
  return a*x*x + b*x + vote;
}

int power(int a, int b){
  int i, tot=1;
  for (i=1; i<=b; ++i){
    tot *= a;
  }
  return tot;
}

void solve_linear_system(int SIZE, double *X, double *F){
  /* Solves the linear system A*X=F  using Gauss-Jordan Elimination */
  /* A is the matrix of the coefficients */
  /* X is the unknown vector */
  /* F is the known vector */
  /* For 3 voters, the linear system looks like this: */
  /*     A     *   X    =    F */    
  /* | 1 1 1 |   | d2 |   | D(1) | */
  /* | 4 2 1 | * | d1 | = | D(2) | */
  /* | 9 3 1 |   | d0 |   | D(3) | */
  int i, j, k, a[SIZE][SIZE];
  double ratio, inverse[SIZE][SIZE];
  int value[SIZE];
  for (i=0; i<SIZE; ++i){
    value[i] = i+1;
  }

  /* A is not passed and is computed here because it is a function of the number of voters. */
  for (i=0; i<SIZE; ++i){
    for (j=0; j<SIZE; ++j){
      if ( j != SIZE -1 ){
        a[i][j] = power(value[i], SIZE-j-1);
      } else {
        a[i][j] = 1;
      }
    }
  }
  /* Augmented Matrix */
  double aug[SIZE][2*SIZE];
  for (i=0; i <SIZE; ++i){
    for (j=0; j<2*SIZE; ++j){
      if ( j < SIZE )
        aug[i][j] = a[i][j];
      else 
        if ( i == j-SIZE )
          aug[i][j] = 1;
        else
          aug[i][j] = 0;
    }
  }
  /* Gauss-Jordan elimination */
  for (i=0; i<SIZE-1; ++i){
    for (k=i+1; k<SIZE; ++k){
      ratio = aug[k][i]/aug[i][i];
      for (j=0; j<2*SIZE; ++j){
        aug[k][j] -= ratio*aug[i][j];
      }
    }
  }
  for (i=SIZE-1; i>0; --i){
    for (k=i-1; k>=0; --k){
      ratio = (double)aug[k][i]/(double)aug[i][i];
      for (j=0; j<2*SIZE; ++j){
        aug[k][j] -= ratio*aug[i][j];
      }
    }
  }
  for (i=0; i<SIZE; ++i){
    ratio = aug[i][i];
    for (j=0; j<2*SIZE; ++j){
      aug[i][j] /= ratio;
    }
  }
  /* Isolate the Inverse Matrix: */
  for (i=0; i<SIZE; ++i){
    for (j=SIZE; j<2*SIZE; ++j){
      inverse[i][j-SIZE] = aug[i][j];
    }
  }
  /* Matrix Multiplication: A^(-1)*F = X */
  for (i=0; i<SIZE; ++i){
    X[i] = 0;
    for (j=0; j<SIZE; ++j){
      X[i] += inverse[i][j] * F[j];
    }
  }
}

void count_votes(int SIZE, double *F){
  double X[SIZE], count;        // X is the vector containing the coefficients of the D polynomial
  int votes_for, votes_against;

  solve_linear_system(SIZE, X, F);
  count = X[SIZE-1];
  votes_for = round(count);
  votes_against = SIZE - votes_for;
  printf("FOR: %d\nAGAINST: %d\n", votes_for, votes_against);
}


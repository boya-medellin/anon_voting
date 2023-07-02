#include "anon_voting.h"

int main(int argc, char *argv[]){
  double D[argc-1];         // The vector containing the values each voter computes (D(1), D(2), D(3), ...)
  int i, j, vote, a, b;
  bool simple;

  for (i=0; i<argc-1; ++i){
    D[i] = 0;
  }
  srand(time(NULL));

  // Votes are read from argv[]
  if (argc==1){
    printf("No votes were given!\n");
    return 0;
  }
  for (i=1; i<argc; ++i){
    if ((atoi(argv[i])!=0)&&(atoi(argv[i])!=1)){
      printf("Votes are binary!\n");
      return 0;
    }
    vote = atoi(argv[i]);
    a = rand()%10;
    b = rand()%10;
    for (j=0; j<argc-1; ++j){
      D[j] += polynomial(j+1, a, b, vote);
    }
  }

  count_votes(argc-1, D);
  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "Liste.c"

int main(){
LISTE l;
int i, succes;
  //Allocation de memoire et verifications
  l = malloc( sizeof( struct une_Liste) );
  if (l == NULL) {
    printf("Allocation impossible \n");
    exit(EXIT_FAILURE);
  }

  //verification de l'opération listeVide
  l = listevide();
  if (l->longeur !=0) {succes = 0;}

  //verification de l'opération EstVide
  if(Estvide(listevide())){succes = 0;}

}

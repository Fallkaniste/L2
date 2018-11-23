#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MaxSize 1000
#define FAUX 0
#define VRAI 1
typedef int
BOOLEEN;

typedef struct une_Liste{
  int longeur;
  float tab[MaxSize];
}Liste;

typedef struct une_Liste* LISTE;

LISTE listevide();
int Estvide();
LISTE cons(int Elem, LISTE liste);
LISTE fin(LISTE liste);
float tete(LISTE liste);
int taill(LISTE liste);

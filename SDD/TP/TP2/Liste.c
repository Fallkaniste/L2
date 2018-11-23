#include "Liste.h"

LISTE listevide(){
  LISTE l = malloc(sizeof(struct une_Liste));

}

int Estvide(LISTE l){
  return((l->longeur)==0);
}

LISTE cons(int Elem, LISTE l){
    l->tab[l->longeur] = Elem;
    l->longeur = l->longeur + 1;
}

LISTE fin(LISTE l){
  for (int i = 0; i < l->longeur-1; i++) {
    l->tab[i]=l->tab[i+1];
  }
  l->longeur = l->longeur-1;
}

float tete(LISTE l){
    return(l->tab[0]);
}

float taille(LISTE l){
  return(l->longeur);
}



int main() {
  LISTE liste = listevide();
  for (int i = 0; i <= 10; i++) {
    cons(i,liste);
  }
  fin(liste);
  for (int i = 0; i < 10; i++) {
    printf("%lf\n",liste->tab[i]);
  }
  printf("%f\n", tete(liste));
  printf("%f\n", taille(liste));
}


/* TP3
set /BAG
SET = enssemble
 un elem appartient ou non a l'enssemble
si il appartient a l'enssemble il n'appaait qu'une seul fois au Max
mais si l'elem appartient a l'enssemble + de 1 fois
alors on optient un BAG
liste chainée obligé
*/

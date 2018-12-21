#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MaxSize 10
#define FAUX 0
#define VRAI 1
typedef int BOOLEEN;
typedef   struct liste
          {
	           int  longueur;
	           float  tab[MaxSize];
          }liste;

typedef  struct liste *  LISTE;
	LISTE listeVide();		/*création d’une liste vide*/
  LISTE consListe(int Elem,LISTE l);		/*insère l'élément en première position*/
  LISTE fin(LISTE);		/*enlever le premier terme*/
	float tete(LISTE);		/*prendre le premier terme*/
	int taille(LISTE);		/*donne la taille de la liste*/
	

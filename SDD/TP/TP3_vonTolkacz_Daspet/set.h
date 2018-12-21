#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MaxSize 10
#define FAUX 0
#define VRAI 1
typedef int BOOLEEN;
typedef   struct Set
          {
	           int  longueur;
	           float  tab[MaxSize];
          }liste;

typedef  struct Set *  SET;
	SET setVide();	/*Créer un set vide*/
  SET ajouterSet(int Elem,SET s);		/*Ajouter un objet*/
  SET enleverSet(SET);		/*enleve un objet*/
	int  appartient(SET);		/*test si un objet appartient a un set*/
	int estVide(LISTE);		/*test la vacuité d'un set*/

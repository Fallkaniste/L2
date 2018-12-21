#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MaxSize 10
#define FAUX 0
#define VRAI 1
typedef int BOOLEEN;
typedef   struct Arbre
          {
	           int  longueur;
	           float  tab[MaxSize];
          }Arbre;

typedef  struct Arbre *  ARBRE;
	Arbre arbreVide();	/*créer un arbre vide*/
  Arbre arbreEstVide(); /*tester si un arbre est vide*/
  Arbre construireAbre(nt Elem,SET s);		/*construire un arbre*/
  SET racineArbre(SET);		/*connaitre la racine d'un arbre*/
	int  nbSousArbre(SET);		/*connaitre le nombre de sous arbre d'un arbre*/
	int foretSousArbre(LISTE);		/*connaitre la foret des sous arbres d'un arbre*/
  Arbre iemeSousArbre /*connaitre le ième sous arbre d'un arbre*/

#include "liste.h"

LISTE listeVide(){
	LISTE l=malloc(sizeof(struct liste));
	}

int EstVide(LISTE L)
	{
	return ((L->longueur)==0);
	}


LISTE consListe(int Elem,LISTE L){
	L->tab[L->longueur]=Elem;
	L->longueur = L->longueur+1;

	}

LISTE finListe(LISTE L)
{
	for (int i=0;i<1;i++){
		L->tab[i]=L->tab[i+1];
	}
	L->longueur =L->longueur-1;
}
float tete(LISTE L)
{
	return ((L->tab[0]));
}

int taille(LISTE L)
{
	return (L->longueur);
}

int main(){
	LISTE liste=listeVide();
	for (int i=0; i<=10;i++) {
		consListe(i,liste);
		printf("%lf\n",liste->tab[i] );
	}
	printf("%lf\n",tete(liste) );
	printf("%d\n",taille(liste) );
	return 0;


}
//par rapport au tp3: set (ensemble) un ele appartient ou pas a l'ensemble et si il apparait c'est que une fois au max mais si l'ele qui fait partie de l'ensemble apparait plus de une fois on obtient un bag

#include "set.h"

SET setVide()
{
  if (estVide(SET)=true);
}

SET ajouterSet(int Elem,SET s)
{
  nouv=malloc(sizeof(SET));
  nouv->elt=e;
  nouv->suiv=x;
  return;
}

SET enleverSet(int e, SET S)
{
	if (s->elt==e)
		return s->suiv;
	set ptr=S;
	while (ptr->suiv!=NULL){
		if(ptr->suiv->elt==e)
		{
			ptr->suiv = ptr-> suiv->suiv;
		}else
			ptr=ptr->suiv;
	return S;
	}

int appartient(SET)
{

}

int estVide(SET)
{
  return ()(SET->longueur)==0);
}

int main()
{

}

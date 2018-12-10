#include <stdio.h>
int main()
{int note;
	do
	{	printf("entrez une note\n");
		scanf("%d",&note);
	}while(note < 0 || note > 20);

	if (note < 0 || note > 20) {printf("note invalive, ");}
	if (note <= 10 && note >=0) {printf("failing\n");}
	if (note <= 12 && note >10) {printf("satisfactory\n");}
	if (note <= 16 && note >12) {printf("good\n");}
	if (note > 16 && note <=20)  {printf("excellent\n");}

}

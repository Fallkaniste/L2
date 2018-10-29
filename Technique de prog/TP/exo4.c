#include <stdio.h>
int main()
{int note;
	do
	{	printf("entrez une note\n");
		scanf(note);
		if (note <= 10) {printf("failing\n");}
		else if (note <= 12) {printf("satisfactory\n");}
		else if (note <= 16) {printf("good\n");}
		else if (note > 16)  {printf("excellent\n");}
	} while (note < 0 || note > 20);

}
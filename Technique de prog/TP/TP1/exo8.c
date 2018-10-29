#include <stdio.h>

int main()
{
	int billet,c5=0,c10=0,c20=0,c50=0,c100=0,c200=0,c500=0;

	do
	{
		printf("entrez un billet\n");
		scanf("%d",&billet);
		printf("banknote: %d\n",billet);
		switch(billet){
			case 5: c5=c5+1; break;
			case 10: c10=c10+1; break;
			case 20: c20=c20+1; break;
			case 50: c50=c50+1; break;
			case 100: c100=c100+1; break;
			case 200: c200=c200+1; break;
			case 500: c500=c500+1; break;
			default : fprintf(stderr, "invalid banknote value\n");
		}
		printf("%d banknote(s) of 5 euros\n",c5);
		printf("%d banknote(s) of 10 euros\n",c10);
		printf("%d banknote(s) of 20 euros\n",c20);
		printf("%d banknote(s) of 50 euros\n",c50);
		printf("%d banknote(s) of 100 euros\n",c100);
		printf("%d banknote(s) of 200 euros\n",c200);
		printf("%d banknote(s) of 500 euros\n",c500);
	} while (billet != (-1));
}
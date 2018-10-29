#include <stdio.h>

int main()
{
	float max;
	float test;
	do
	{	printf("entrez une nombre\n");
		scanf("%f",&max);
		test=max;
		do
		{
			if (test == 1){test = test-1;}
			else{test = test-2;}
		} while (test > 0);
		printf("max : %f\n",max);
	}while(max < 0 || test!=0);

	for (int i = 0; i <= max; ++i)
	{
		printf("%d\n",i);
	}




}
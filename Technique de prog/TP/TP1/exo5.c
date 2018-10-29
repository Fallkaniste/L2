#include <stdio.h>
int main(){
	int note = 25;
	while (note < 0 || note > 20){
		printf("mark: ");
		scanf("%d",&note);

	}
		if (note > 16)  {printf("excellent\n");}
		else if (note <= 10) {printf("failing\n");}
		else if (note <= 12) {printf("satisfactory\n");}
		else if (note <= 16) {printf("good\n");}
		else {printf("note invalive, ");} 
	
}
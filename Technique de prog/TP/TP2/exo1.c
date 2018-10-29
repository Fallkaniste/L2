#include <stdio.h>

	typedef struct {
		char name[100];
		char authors[10][100];
		int nauthors;
		char publisher[100];
		int year;
		long int isbn;
	}book_t;


	typedef enum{
		monday,tuesday,wednesday,thursday,friday,saturday,sunday
	}day_e;


	typedef struct {
		char *name;
		int ndays;
		day_t *days;
		book_t *books;
		int nbooks;
	}library_t;

book_t* book_creat(){
	book_t *pt = malloc(sizeof(book_t));
	pt -> name = NULL;

}


void book_print(book_t book){

	printf("Titre : %s\n", book.name);
	printf("Ecrit par : ");
	for (int i = 0; i < book.nauthors; ++i){printf("%s\n", book.authors[i]);}
	printf("Edition : %s\n", book.publisher);
	printf("Année : %d\n", book.year);
	printf("ISBN : %ld\n", book.isbn);
	}

void library_print(library_t library){
	printf("biliothèque : %s\n", library.name);
	printf("ouverte %d jours sur 7\n", library.ndays);
	printf("jours d'ouverture : ");
	for (int i = 0; i < library.ndays; ++i){
		switch(library.days[i]){
			case 0: printf("monday, ");break;
			case 1: printf("tuesday, ") ;break;
			case 2: printf("wednesday, ") ;break;
			case 3: printf("thursday, ") ;break;
			case 4: printf("friday, ") ;break;
			case 5: printf("saturday, ") ;break;
			case 6: printf("sunday,") ;break;
			default : fprintf(stderr, "invalid day value\n");
		}
	}
	printf("\n");
	printf("nombre de livres en stock : %d\n", library.nbooks);
	for (int i = 0; i < library.nbooks; ++i)
	{
		printf("livre N°%d:\n", i+1);
		book_print(library.books[i]);
	}
}
int main(){

	library_t Sciences_Library={
		"Sciences Library",
		4,
		{monday,thursday,wednesday,thursday},
		{
		{//livre N°1
			"The C Programming Language",
			{//auteurs
				"Brian W. Kernighan","Dennis M. Ritchie"
			},
			2,"rentice Hall",1988,9780131103627
		},
		{//livre N°2
			"C: The Complete Reference",
			{//auteurs
				"Herbert Schildt"
			},
			1,"McGraw-Hill Education",2000,9780072121247
		}

		},2,
	};
	library_t Novel_Library={
		"Novel Library",
		4,
		{tuesday,wednesday,thursday,friday},
		{
		{//livre N°1
			"Harry Potter and the Philosopher’s Stone",
			{//auteurs
				"J. K. Rowling"
			},
			1,"Bloomsbury",1997,9780747532699
		},
		{//livre N°2
			"Harry Potter and the Chamber of Secret",
			{//auteurs
				"J. K. Rowling"
			},
			1,"Bloomsbury",1998,9780747538493

		},
	},2,

	};

library_print(Sciences_Library);
library_print(Novel_Library);

}
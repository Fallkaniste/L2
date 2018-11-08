#include <stdio.h>
#include "stdlib.h"

	typedef struct {
		char *name;
		char **authors;
		int nauthors;
		char *publisher;
		int year;
		long int isbn;
	}book_t;


	typedef enum{
		monday,tuesday,wednesday,thursday,friday,saturday,sunday
	}day_e;


	typedef struct {
		char *name;
		int ndays;
		day_e *days;
		book_t *books;
		int nbooks;
	}library_t;

book_t* book_creat(){
	book_t *book = malloc(sizeof(book_t));
	book -> name = NULL;
	book -> authors = NULL;
	book -> nauthors = 0;
	book -> publisher = NULL;
	book -> year = 0;
	book -> isbn = 0;
	return(book);
	}

library_t* library_create(){
	library_t *library = malloc(sizeof(library_t));
	library -> name = NULL;
	library -> ndays = 0;
	library -> days = NULL;
	library -> books = NULL;
	library -> nbooks = 0;
	return(library);
}

int book_add_author(book_t *book, char* author){
	book -> nauthors ++;
	book -> authors = realloc(book -> authors,sizeof(char*)*book -> nauthors);
	book -> authors[book -> nauthors-1] = author;
	return 0;
}


void book_free(book_t *book){
	free(book);
}

void library_free(library_t *library){
	free(library);
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
/*
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
*/
}

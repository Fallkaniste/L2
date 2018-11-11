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

book_t* book_create(){
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

int library_add_day(library_t *library , day_e day){
	library -> ndays ++;
	library -> days = realloc(library -> days,sizeof(day_e)*library -> ndays);
	library -> days[library -> ndays-1] = day;
	return 0;
}

int library_add_book(library_t *library , book_t book){
	library -> nbooks ++;
	library -> books = realloc(library -> books,sizeof(book_t)*library -> nbooks);
	library -> books[library -> nbooks-1] = book;
	return 0;
}


void book_free(book_t *book){
	free(book);
}

void library_free(library_t *library){
	free(library);
}

void book_print(book_t* book){

	printf("Titre : %s\n", book -> name);
	printf("Ecrit par : ");
	for (int i = 0; i < book->nauthors; ++i){printf("%s\n", book->authors[i]);}
	printf("Edition : %s\n", book->publisher);
	printf("Année : %d\n", book->year);
	printf("ISBN : %ld\n", book->isbn);
	}

void library_print(library_t* library){
	printf("biliothèque : %s\n", library->name);
	printf("ouverte %d jours sur 7\n", library->ndays);
	printf("jours d'ouverture : ");
	for (int i = 0; i < library->ndays; ++i){
		switch(library->days[i]){
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
	printf("nombre de livres en stock : %d\n", library->nbooks);
	for (int i = 0; i < library->nbooks; ++i)
	{
		printf("livre N°%d:\n", i+1);
		book_print(library->books);
	}
}
int main(){
library_t *Sciences_Library = library_create();
library_t *Novel_Library = library_create();

book_t *SlBook1 = book_create();
book_t *SlBook2 = book_create();
book_t *NlBook1 = book_create();
book_t *NlBook2 = book_create();

Sciences_Library -> name = "Sciences Library";
library_add_day(Sciences_Library,monday);
library_add_day(Sciences_Library,tuesday);
library_add_day(Sciences_Library,wednesday);
library_add_day(Sciences_Library,thursday);

Novel_Library -> name = "Novel Library";
library_add_day(Novel_Library,tuesday);
library_add_day(Novel_Library,wednesday);
library_add_day(Novel_Library,thursday);
library_add_day(Novel_Library,friday);

SlBook1 -> name = "The C Programming Language";
book_add_author(SlBook1,"Brian W. Kernighan");
book_add_author(SlBook1,"Dennis M. Ritchie");
SlBook1 -> publisher = "rentice Hall";
SlBook1 -> year = 1988;
SlBook1 -> isbn = 9780131103627;

SlBook2 -> name = "C: The Complete Reference";
book_add_author(SlBook2,"Herbert ScThe C Programming Language");
SlBook2 -> publisher = "McGraw-Hill Education";
SlBook2 -> year = 2000;
SlBook2 -> isbn = 9780072121247;

NlBook1 -> name = "Harry Potter and the Philosopher’s Stone";
book_add_author(NlBook1,"J. K. Rowling");
NlBook1 -> publisher = "Bloomsbury";
NlBook1 -> year = 1997;
NlBook1 -> isbn = 9780747532699;

NlBook2 -> name = "Harry Potter and the Chamber of Secret";
book_add_author(NlBook2,"J. K. Rowling");
NlBook2 -> publisher = "Bloomsbury";
NlBook2 -> year = 1998;
NlBook2 -> isbn = 9780747538493;

library_add_book(Sciences_Library,*SlBook1);
library_add_book(Sciences_Library,*SlBook2);

library_add_book(Novel_Library,*NlBook1);
library_add_book(Novel_Library,*NlBook2);

library_print(Sciences_Library);
library_print(Novel_Library);

library_free(Sciences_Library);
library_free(Novel_Library);
book_free(SlBook1);
book_free(SlBook2);
book_free(NlBook1);
book_free(NlBook2);

}

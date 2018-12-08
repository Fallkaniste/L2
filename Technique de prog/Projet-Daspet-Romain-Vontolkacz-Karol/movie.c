#include "movie.h"
#include <stdlib.h>
#include <stdio.h>

movie_t *movie_create(){
  movie_t* movie = malloc(sizeof(movie_t));
  if (movie == NULL) {
   fprintf(stderr, "the memory allocation is a failure\n");
  }
  return movie;
}

void movie_free(movie_t *movie) {
  free(movie);
}

void movie_handle_mv(movie_t movie){
  printf("%s (%d), %f\n",movie.name, movie.year, movie.price);
}

void movie_handle_mvn(movie_t movie, const char *name){
  if (movie.name == name) {
    printf("%s (%d), %f\n",movie.name, movie.year, movie.price);
  }

}
void movie_handle_mvp(movie_t movie, float price){
    if(movie.price == price){
      printf("%s (%d), %f\n",movie.name, movie.year, movie.price);
    }
}
void movie_handle_mvpge(movie_t movie, float price){
  if (movie.price >= price) {
    printf("%s (%d), %f\n",movie.name, movie.year, movie.price);
  }
}
void movie_handle_mvpgt(movie_t movie, float price){
  if (movie.price > price) {
    printf("%s (%d), %f\n",movie.name, movie.year, movie.price);
  }
}
void movie_handle_mvple(movie_t movie, float price){
  if (movie.price <= price) {
    printf("%s (%d), %f\n",movie.name, movie.year, movie.price);
  }
}
void movie_handle_mvplt(movie_t movie, float price){
  if (movie.price < price) {
    printf("%s (%d), %f\n",movie.name, movie.year, movie.price);
  }
}
void movie_handle_mvy(movie_t movie, int year){
  if (movie.year == year) {
    printf("%s (%d), %f\n",movie.name, movie.year, movie.price);
  }
}
void movie_handle_mvyge(movie_t movie, int year){
  if (movie.year >= year) {
    printf("%s (%d), %f\n",movie.name, movie.year, movie.price);
  }
}
void movie_handle_mvygt(movie_t movie, int year){
  if (movie.year > year) {
    printf("%s (%d), %f\n",movie.name, movie.year, movie.price);
  }
}
void movie_handle_mvyle(movie_t movie, int year){
  if (movie.year <= year) {
    printf("%s (%d), %f\n",movie.name, movie.year, movie.price);
  }
}
void movie_handle_mvylt(movie_t movie, int year){
  if (movie.year < year) {
    printf("%s (%d), %f\n",movie.name, movie.year, movie.price);
  }
}

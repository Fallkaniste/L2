#include "vrs.h"
#include <stdlib.h>
#include <stdio.h>
int i;

int vrs_add_movie(vrs_t *vrs, movie_t *movie){
  vrs -> nmovies ++;
	vrs -> movies = realloc(vrs -> movies,sizeof(movie_t)*vrs -> nmovies);
  if (vrs -> movies == NULL) {
    return -1;
  }
	vrs -> movies[vrs -> nmovies-1] = movie;
  return 0;
}
vrs_t *vrs_create(){
  vrs_t *vrs = malloc(sizeof(vrs_t));
  return vrs;

}
void vrs_free(vrs_t *vrs){
  free(vrs);
}
void vrs_handle_addr(vrs_t vrs){
  /*Rent a video, 1 rue Richelieu, 64000, Pau*/
  printf("%s, %s, %d, %s\n",vrs.name, vrs.street, vrs.postal_code, vrs.city);
}
void vrs_handle_mv(vrs_t vrs){
  for (i = 0; i < vrs.nmovies-1; i++) {
    movie_handle_mv(*(vrs.movies)[i]);
  }
}
void vrs_handle_mvn(vrs_t vrs, const char *name){
  for (i = 0; i < vrs.nmovies-1; i++) {
    movie_handle_mvn(*(vrs.movies)[i],name);
  }
}
void vrs_handle_mvp(vrs_t vrs, float price){
  for (i = 0; i < vrs.nmovies-1; i++) {
    movie_handle_mvp(*(vrs.movies)[i],price);
  }
}
void vrs_handle_mvpge(vrs_t vrs, float price){
  for (i = 0; i < vrs.nmovies-1; i++) {
    movie_handle_mvpge(*(vrs.movies)[i],price);
  }
}
void vrs_handle_mvpgt(vrs_t vrs, float price){
  for (i = 0; i < vrs.nmovies-1; i++) {
    movie_handle_mvpgt(*(vrs.movies)[i],price);
  }
}
void vrs_handle_mvple(vrs_t vrs, float price){
  for (i = 0; i < vrs.nmovies-1; i++) {
    movie_handle_mvple(*(vrs.movies)[i],price);
  }
}
void vrs_handle_mvplt(vrs_t vrs, float price){
  for (i = 0; i < vrs.nmovies-1; i++) {
    movie_handle_mvplt(*(vrs.movies)[i],price);
  }
}
void vrs_handle_mvy(vrs_t vrs, int year){
  for (i = 0; i < vrs.nmovies-1; i++) {
    movie_handle_mvy(*(vrs.movies)[i],year);
  }
}
void vrs_handle_mvyge(vrs_t vrs, int year){
  for (i = 0; i < vrs.nmovies-1; i++) {
    movie_handle_mvyge(*(vrs.movies)[i],year);
  }
}
void vrs_handle_mvygt(vrs_t vrs, int year){
  for (i = 0; i < vrs.nmovies-1; i++) {
    movie_handle_mvygt(*(vrs.movies)[i],year);
  }
}
void vrs_handle_mvyle(vrs_t vrs, int year){
  for (i = 0; i < vrs.nmovies-1; i++) {
    movie_handle_mvyle(*(vrs.movies)[i],year);
  }
}
void vrs_handle_mvylt(vrs_t vrs, int year){
  for (i = 0; i < vrs.nmovies-1; i++) {
    movie_handle_mvylt(*(vrs.movies)[i],year);
  }
}

#include "vrs.h"


int vrs_add_movie(vrs_t *vrs, movie_t *movie){
  vrs -> nmovies ++;
	vrs -> movie = realloc(vrs -> movie,sizeof(movie_t)*vrs -> nmovies);
	vrs -> movie[vrs -> nmovies-1] = movie;
}
vrs_t *vrs_create(){
  vrs = malloc(sizeof(struct vrs_t));
  if (vrs == NULL) {
   fprintf(stderr, "the memory allocation is a failure\n");
  }
  return 0;
}
void vrs_free(vrs_t *vrs){
  free(vrs);
}
void vrs_handle_addr(vrs_t vrs){
  //Rent a video, 1 rue Richelieu, 64000, Pau
  printf("%s, %s, %d, %s\n",vrs->name, vrs->street, vrs->postal_code, vrs->city);
}
void vrs_handle_mv(vrs_t vrs){
  for (int i = 0; i < vrs->nmovies-1; i++) {
    movie_handle_mv(movies[i]);
  }
}
void vrs_handle_mvn(vrs_t vrs, const char *name){
  for (int i = 0; i < vrs->nmovies-1; i++) {
    movie_handle_mvn(movies[i],name);
  }
}
void vrs_handle_mvp(vrs_t vrs, float price){
  for (int i = 0; i < vrs->nmovies-1; i++) {
    movie_handle_mv(movies[i],price);
  }
}
void vrs_handle_mvpge(vrs_t vrs, float price){
  for (int i = 0; i < vrs->nmovies-1; i++) {
    movie_handle_mv(movies[i],price);
  }
}
void vrs_handle_mvpgt(vrs_t vrs, float price){
  for (int i = 0; i < vrs->nmovies-1; i++) {
    movie_handle_mv(movies[i],price);
  }
}
void vrs_handle_mvple(vrs_t vrs, float price){
  for (int i = 0; i < vrs->nmovies-1; i++) {
    movie_handle_mv(movies[i],price);
  }
}
void vrs_handle_mvplt(vrs_t vrs, float price){
  for (int i = 0; i < vrs->nmovies-1; i++) {
    movie_handle_mv(movies[i],price);
  }
}
void vrs_handle_mvy(vrs_t vrs, int year){
  for (int i = 0; i < vrs->nmovies-1; i++) {
    movie_handle_mv(movies[i],price);
  }
}
void vrs_handle_mvyge(vrs_t vrs, int year){
  for (int i = 0; i < vrs->nmovies-1; i++) {
    movie_handle_mv(movies[i],price);
  }
}
void vrs_handle_mvygt(vrs_t vrs, int year){
  for (int i = 0; i < vrs->nmovies-1; i++) {
    movie_handle_mv(movies[i],price);
  }
}
void vrs_handle_mvyle(vrs_t vrs, int year){
  for (int i = 0; i < vrs->nmovies-1; i++) {
    movie_handle_mv(movies[i],price);
  }
}
void vrs_handle_mvylt(vrs_t vrs, int year){
  for (int i = 0; i < vrs->nmovies-1; i++) {
    movie_handle_mv(movies[i],price);
  }
}

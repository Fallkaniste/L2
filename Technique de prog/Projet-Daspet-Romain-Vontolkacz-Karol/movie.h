/**
* \file movie.h
*/
#ifndef MOVIE_H
#define MOVIE_H
/**
* A movie.
*/
typedef struct
{
char *name; /**< The movie name. */
float price; /**< The movie renting price. */
int year; /**< The movie release year. */
} movie_t;
/**
* Creates a movie.
* \return NULL on error (i.e., if the memory allocation is a failure), else a movie.
*/
movie_t *movie_create();
/**
* Frees a movie.
* \param movie The movie.
*/
void movie_free(movie_t *movie);
/**
* Handles the mv command for a movie.
* \param movie The movie.
*/
void movie_handle_mv(movie_t movie);
/**
* Handles the mvn command for a movie.
* \param movie The movie.
* \param name The movie name.
*/
void movie_handle_mvn(movie_t movie, const char *name);
/**
* Handles the mvp command for a movie.
* \param movie The movie.
* \param price The movie renting price.
*/
void movie_handle_mvp(movie_t movie, float price);
/**
* Handles the mvpge command for a movie.
* \param movie The movie.
* \param price The movie renting price.
*/
void movie_handle_mvpge(movie_t movie, float price);
/**
* Handles the mvpgt command for a movie.
* \param movie The movie.
* \param price The movie renting price.
*/
void movie_handle_mvpgt(movie_t movie, float price);
/**
* Handles the mvple command for a movie.
* \param movie The movie.
* \param price The movie renting price.
*/
void movie_handle_mvple(movie_t movie, float price);
/**
* Handles the mvplt command for a movie.
* \param movie The movie.
* \param price The movie renting price.
*/
void movie_handle_mvplt(movie_t movie, float price);
/**
* Handles the mvy command for a movie.
* \param movie The movie.
* \param year The movie release year.
*/
void movie_handle_mvy(movie_t movie, int year);
/**
* Handles the mvyge command for a movie.
* \param movie The movie.
* \param year The movie release year.
*/
void movie_handle_mvyge(movie_t movie, int year);
/**
* Handles the mvygt command for a movie.
* \param movie The movie.
* \param year The movie release year.
*/
void movie_handle_mvygt(movie_t movie, int year);
/**
* Handles the mvyle command for a movie.
* \param movie The movie.
* \param year The movie release year.
*/
void movie_handle_mvyle(movie_t movie, int year);
/**
* Handles the mvylt command for a movie.
* \param movie The movie.
* \param year The movie release year.
*/
void movie_handle_mvylt(movie_t movie, int year);
#endif

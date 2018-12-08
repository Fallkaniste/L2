/**
* \file vrs.h
*/
#ifndef VRS_H
#define VRS_H
#include "movie.h" /* for movie_t */
/**
* A VRS (Video Rental Shop).
*/
typedef struct
{
char *city; /**< The VRS city. */
movie_t **movies; /**< The VRS movies. */
char *name; /**< The VRS name. */
int nmovies; /**< The VRS number of movies. */
int postal_code; /**< The VRS postal code. */
char *street; /**< The VRS street. */
} vrs_t;
/**
* Add a movie to a VRS.
* \param vrs The VRS.
* \param movie The movie.
* \return -1 on error (i.e., if the memory allocation is a failure), else 0.
*/
int vrs_add_movie(vrs_t *vrs, movie_t *movie);
/**
2711/2018 Techniques de programmation - Projet - VRSP 5/7
versité de Pau et des Pays de l’Adour L2 informatique
* Creates a VRS.
* \return NULL on error (i.e., if the memory allocation is a failure), else a VRS.
*/
vrs_t *vrs_create();
/**
* Frees a VRS.
* \param vrs The VRS.
*/
void vrs_free(vrs_t *vrs);
/**
* Handles the addr command for a VRS.
* \param vrs The VRS.
Rent a video, 1 rue Richelieu, 64000, Pau*/
void vrs_handle_addr(vrs_t vrs);
/**
* Handles the mv command for all the movies of a VRS.
* \param vrs The VRS.
*/
void vrs_handle_mv(vrs_t vrs);
/**
* Handles the mvn command for all the movies of a VRS.
* \param vrs The VRS.
* \param name The VRS name.
*/
void vrs_handle_mvn(vrs_t vrs, const char *name);
/**
* Handles the mvp command for all the movies of a VRS.
* \param vrs The VRS.
* \param price The movie renting price.
*/
void vrs_handle_mvp(vrs_t vrs, float price);
/**
* Handles the mvpge command for all the movies of a VRS.
* \param vrs The VRS.
* \param price The movie renting price.
*/
void vrs_handle_mvpge(vrs_t vrs, float price);
/**
* Handles the mvpgt command for all the movies of a VRS.
* \param vrs The VRS.
* \param price The movie renting price.
*/
void vrs_handle_mvpgt(vrs_t vrs, float price);
/**
* Handles the mvple command for all the movies of a VRS.
* \param vrs The VRS.
* \param price The movie renting price.
*/
void vrs_handle_mvple(vrs_t vrs, float price);
/**
* Handles the mvplt command for all the movies of a VRS.
* \param vrs The VRS.
* \param price The movie renting price.
*/
void vrs_handle_mvplt(vrs_t vrs, float price);
/**
* Handles the mvy command for all the movies of a VRS.
* \param vrs The VRS.
* \param year The movie release year.
*/
void vrs_handle_mvy(vrs_t vrs, int year);
/**
* Handles the mvyge command for all the movies of a VRS.
* \param vrs The VRS.
* \param year The movie release year.
*/
void vrs_handle_mvyge(vrs_t vrs, int year);
/**
* Handles the mvygt command for all the movies of a VRS.
* \param vrs The VRS.
* \param year The movie release year.
*/
void vrs_handle_mvygt(vrs_t vrs, int year);
/**
* Handles the mvyle command for all the movies of a VRS.
* \param vrs The VRS.%s
1/2018 Techniques de programmation - Projet - VRSP 6/7
ersité de Pau et des Pays de l’Adour L2 informatique
* \param year The movie release year.
*/
void vrs_handle_mvyle(vrs_t vrs, int year);
/**
* Handles the mvylt command for all the movies of a VRS.
* \param vrs The VRS.
* \param year The movie release year.
*/
void vrs_handle_mvylt(vrs_t vrs, int year);
#endif

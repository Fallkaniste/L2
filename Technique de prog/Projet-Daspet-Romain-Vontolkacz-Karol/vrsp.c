#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include "vrs.h"
#include "movie.h"
int i,j,k;

void split(char* saisie,char* arg,char* command){
  int split = 0;

  for (i = 0; i < strlen(saisie); i++) {
    if (saisie[i] == ' ') {
      split = 1;
    }
  }

  if (split == 1) {
    i = 0;
    do {
        command[i] = saisie[i];
        i++;
    } while(saisie[i] != ' ');
    for (k = i; k < strlen(command); k++) {
      command[k]=0;
    }
    i++;

    for (j = 0; i < strlen(saisie)-1; j++) {
      arg[j] = saisie[i];
      i++;
    }

  }else{
    for ( i = 0; i < strlen(saisie); i++) {
      command[i] = saisie[i];
    }
    }



}

void print_help(){
  printf("addr: Prints the VRS address\n");
  printf("help: Prints this help\n");
  printf("mv: Prints the VRS movies\n");
  printf("mvn NAME: Prints the VRS movies containing the name NAME\n");
  printf("mvp PRICE: Prints the VRS movies with the renting price equal to PRICE\n");
  printf("mvpge PRICE: Prints the VRS movies with the renting price greater than or equal to PRICE\n");
  printf("mvpgt PRICE: Prints the VRS movies with the renting price greater than PRICE\n");
  printf("mvple PRICE: Prints the VRS movies with the renting price less than or equal to PRICE\n");
  printf("mvplt PRICE: Prints the VRS movies with the renting price less than PRICE\n");
  printf("mvy YEAR: Prints the VRS movies with the release year equal to YEAR\n");
  printf("mvyge YEAR: Prints the VRS movies with the release year greater than or equal to YEAR\n");
  printf("mvygt YEAR: Prints the VRS movies with the release year greater than YEAR\n");
  printf("mvyle YEAR: Prints the VRS movies with the release year less than or equal to YEAR\n");
  printf("mvylt YEAR: Prints the VRS movies with the release year less than YEAR\n");
  printf("version: Prints the VRSP version\n");
  printf("quit: Quits VRSP\n");
}

void buildVrsMovies(xmlDocPtr doc,xmlNodePtr cur, vrs_t *vrs){
  movie_t *movie = movie_create();
  xmlNodePtr aux;
  char*p_conv = malloc(sizeof(double));
  cur = cur->xmlChildrenNode;
  cur = cur->next;
for(i = 0 ; i<9 ; i++){
    movie = realloc(movie,sizeof(movie_t*));
    movie->name = (char*) xmlGetProp(cur , (const xmlChar *) "name" );
    aux = cur->xmlChildrenNode;
    aux = aux->next;
    movie->year = (int)strtol((char*) xmlNodeListGetString(doc, aux->xmlChildrenNode, 1),&p_conv,10);
    aux = aux->next;
    aux = aux->next;
    movie->price = (float)strtod((char*) xmlNodeListGetString(doc, aux->xmlChildrenNode, 1),&p_conv);
    if (p_conv != NULL) {
      if (*p_conv != '\0') {
        fprintf(stderr, "conversion incomplete !");
        *p_conv = '\0';
      }
    }
    cur = cur->next;
    cur = cur->next;
    vrs_add_movie(vrs,movie);
    movie = NULL;
  }

}

int main(int argc, char *argv[]) {
  xmlDocPtr doc;
  xmlNodePtr cur;
  char *p_conv;
  vrs_t *vrs = vrs_create();
  char * command = malloc(sizeof(char*));
  char * arg = malloc(sizeof(char*));
  char * saisie = malloc(sizeof(char*));

  if (argc != 2) {
    fprintf(stderr, "invalid number of arguments\n");
    return 1;
  }
  if (argc != 2) {
    fprintf(stderr, "invalid number of arguments\n");
    return 1;
  }
  doc = xmlParseFile(argv[1]);
  if (doc == NULL ) {
    fprintf(stderr,"Document not parsed successfully. \n");
    return 1;
  }
  cur = xmlDocGetRootElement(doc);
  if (cur == NULL) {
    fprintf(stderr,"empty document\n");
    xmlFreeDoc(doc);
    return 1;
  }
  vrs->name = (char*) xmlGetProp(cur , (const xmlChar *) "name" );
  cur = cur->xmlChildrenNode;
  cur = cur->next;

  vrs->street = (char*) xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
  cur = cur->next;
  cur = cur->next;
  vrs->postal_code = (int)strtol((char*) xmlNodeListGetString(doc, cur->xmlChildrenNode, 1),&p_conv,10);
  cur = cur->next;
  cur = cur->next;
  vrs->city = (char*) xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
  cur = cur->next;
  cur = cur->next;

  buildVrsMovies(doc,cur,vrs);

  while ((strcmp(saisie,"quit"))!= 10) {
    i = 0;
    printf("VRSP>");
    fgets(saisie,100,stdin);
    split(saisie,arg,command);
    if ((strcmp(saisie,"addr") == 10)) {
      vrs_handle_addr(*vrs);
    }else     if ((strcmp(command,"help") == 10)) {
          print_help();
        }else     if ((strcmp(command,"mv") == 10)) {
              vrs_handle_mv(*vrs);
            }else    if ((strcmp(command,"mvn") == 0)) {
                  vrs_handle_mvn(*vrs,arg);
                }else    if ((strcmp(command,"mvp") == 0)) {
                      vrs_handle_mvp(*vrs,(float)strtod(arg,&p_conv));
                    }else    if ((strcmp(command,"mvpge") == 0)) {
                          vrs_handle_mvpge(*vrs,(float)strtod(arg,&p_conv));
                        }else    if ((strcmp(command,"mvpgt") == 0)) {
                              vrs_handle_mvpgt(*vrs,(float)strtod(arg,&p_conv));
                            }else    if ((strcmp(command,"mvple") == 0)) {
                                  vrs_handle_mvple(*vrs,(float)strtod(arg,&p_conv));
                                }else    if ((strcmp(command,"mvplt") == 0)) {
                                      vrs_handle_mvplt(*vrs,(float)strtod(arg,&p_conv));
                                    }else    if ((strcmp(command,"mvy") == 0)) {
                                          vrs_handle_mvy(*vrs,(int)strtol(arg,&p_conv,10));
                                        }else    if ((strcmp(command,"mvyge") == 0)) {
                                              vrs_handle_mvyge(*vrs,(int)strtol(arg,&p_conv,10));
                                            }else    if ((strcmp(command,"mvygt") == 0)) {
                                                  vrs_handle_mvygt(*vrs,(int)strtol(arg,&p_conv,10));
                                                }else    if ((strcmp(command,"mvyle") == 0)) {
                                                      vrs_handle_mvyle(*vrs,(int)strtol(arg,&p_conv,10));
                                                    }else    if ((strcmp(command,"mvylt") == 0)) {
                                                          vrs_handle_mvylt(*vrs,(int)strtol(arg,&p_conv,10));
                                                        }else    if ((strcmp(command,"version") == 10)) {
                                                              printf("VRSP (Video Rental Shop Program) 20181210\n\n");
                                                              printf("Copyright (C) 2018 Daspet Romain and Vontolkacz Karol.\n\n");
                                                              printf("Written by Daspet Romain <daspet.romain@univ-pau.fr> and Vontolkacz Karol <vontolkacz.karol@univ-pau.fr>.\n");
                                                            }else if((strcmp(command,"quit")!= 10)){
                                                              fprintf(stderr, "%s Invalid command\n",argv[0]);
                                                            }


  }
  free(arg);
  free(command);
  free(saisie);
  return 0;
}

/*xmlgetprop pour atribut du noeud
mxlnodelistgetstring pour la chaine de cara du entre les balises
xmlstrcmm compare deux chaine de cara xml
xmlDocGetRootElement pour le premier noeud*/

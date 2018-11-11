#include <stdio.h>
#include "stdlib.h"
#include <string.h>

int main(int argc,char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "invalid number of arguments\n");
    return 1;
  }else{
    if (strlen(argv[1])>10) {
      fprintf(stderr, "the string length is greater than 10\n");
      return 1;
    }
  }

  char* chaine = argv[1];
  for (int i = 0; i < strlen(chaine)/2; i++) {
    char aux;
    aux = chaine[i];
    chaine[i] = chaine[strlen(chaine)-i-1];
    chaine[strlen(chaine)-i-1] = aux;
  }
  printf("%s\n", chaine);
  return 0;
}

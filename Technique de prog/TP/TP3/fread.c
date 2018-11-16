#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  FILE *file = NULL;
  int nitems = -1;
  int ret = EOF;
  char buf[9] = "\0";
  if (argc != 2) {
    fprintf(stderr, "invalid number of arguments\n");
    return 1;
  }
  file = fopen(argv[1],"w");
  if (file == NULL) {
    fprintf(stderr, "unable to open the file\n");
    return 1;
  }
  while (nitems != 0) {
    nitems = fread(argv[2] , sizeof(char) , strlen(argv[1]) , file);
    buf[nitems] = '\0';
    printf("read : %s (%d byte(s) from %s)\n",buf , nitems , argv[1]);
  }



  if (ferror(file)) {
    return 1;
  }
  printf("written: \"%s\" (%d byte(s))\n", argv[2], nitems);
  ret = fclose(file);
  if (ret == EOF) {
    return 1;
  }
  return 0;
}

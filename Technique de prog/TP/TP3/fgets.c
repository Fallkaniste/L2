#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  FILE *file = NULL;
  int ret = EOF;
  char buf[10] = "\0";
  if (argc != 2) {
    fprintf(stderr, "invalid number of arguments\n");
    return 1;
  }
  file = fopen(argv[1],"r");
  if (file == NULL) {
    fprintf(stderr, "unable to open the file\n");
    return 1;
  }

  while (fgets(buf , 10, file) != NULL) {
    printf("read : %s (%lu byte(s) from %s)\n",buf , strlen(buf) , argv[1]);
  }



  if (ferror(file)) {
    return 1;
  }
  ret = fclose(file);
  if (ret == EOF) {
    return 1;
  }
  return 0;
}

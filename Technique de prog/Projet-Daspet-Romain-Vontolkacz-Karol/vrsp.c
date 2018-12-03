#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  FILE *file = NULL;
  int ret = EOF;
  char buf[10] = "\0";
  char comm[5] = "\0";
  if (argc != 2) {
    fprintf(stderr, "invalid number of arguments\n");
    return 1;
  }
  file = fopen(argv[1],"r");
  if (file == NULL) {
    fprintf(stderr, "I/O warning : failed to load external entity \"%s\"\n", argv[1]);
    return 1;
  }
  if (ferror(file)) {
    printf("test\n", );
    return 1;
  }


  scanf("VRSP\n",comm);


  ret = fclose(file);
  if (ret == EOF) {
    return 1;
  }
  return 0;
}

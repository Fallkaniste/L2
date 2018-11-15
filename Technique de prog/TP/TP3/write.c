#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int file = -1;
  int nbytes = -1;
  int ret = -1;
  if (argc != 3) {
    fprintf(stderr, "invalid number of arguments\n");
    return 1;
  }
  file = open(argv[1], O_RDWR | O_CREAT, 0644);
  if (file == -1) {
    fprintf(stderr, "unable to open the file\n");
    return 1;
  }
  nbytes = write(file, argv[2], strlen(argv[2]));
  if (nbytes == -1) {
    return 1;
  }
  printf("written: \"%s\" (%d byte(s))\n", argv[2], nbytes);
  ret = close(file);
  if (ret == -1) {
    return 1;
  }
  return 0;
}

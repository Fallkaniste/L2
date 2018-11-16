#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int file = -1;
  int bytes = -1;
  int ret = -1;
  char buf[9] = "\0";
  if (argc != 2) {
    fprintf(stderr, "invalid number of arguments\n");
    return 1;
  }
  file = open(argv[1], O_RDONLY);
  if (file == -1) {
    fprintf(stderr, "unable to open the file\n");
    return 1;
  }

  while (bytes != 0) {
    bytes = read(file , buf , 9);
    buf[bytes] = '\0';
    printf("read : %s (%d byte(s) from %s)\n",buf , bytes , argv[1]);
  }


  ret = close(file);
  if (ret == -1) {
    return 1;
  }
  return 0;
}

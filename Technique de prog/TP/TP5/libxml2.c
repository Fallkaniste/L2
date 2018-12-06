#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

int main(int argc, char *argv[]) {
  FILE *file = NULL;
  int ret = EOF;
  char buf[10] = "\0";
  char comm[5] = "\0";
  xmlDocPtr doc;
  xmlNodePtr cur;

  if (argc != 2) {
    fprintf(stderr, "invalid number of arguments\n");
    return 1;
  }

  doc = xmlParseFile(argv[1]);

  if (doc == NULL ) {
    fprintf(stderr,"Document not parsed successfully. \n");
    return;
  }

  cur = xmlDocGetRootElement(doc);

  if (cur == NULL) {
    fprintf(stderr,"empty document\n");
    xmlFreeDoc(doc);
    return;
  }




  file = fopen(argv[1],"r");
  if (file == NULL) {
    fprintf(stderr, "I/O warning : failed to load external entity \"%s\"\n", argv[1]);
    return 1;
  }
  if (ferror(file)) {
    return 1;
  }

  printf("VRSP>");
  scanf("%c\n",comm);


  ret = fclose(file);
  if (ret == EOF) {
    return 1;
  }
  return 0;
}

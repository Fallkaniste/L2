#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

int main(int argc, char *argv[]) {
  xmlDocPtr doc;
  xmlNodePtr cur;
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

cur = cur->xmlChildrenNode;

printf("%s\n", xmlGetProp(cur , (const xmlChar *) "name" ));
printf("%s\n", xmlGetProp(cur , (const xmlChar *) "name" ));
  return 0;
}

/*xmlgetprop pour atribut du noeud
mxlnodelistgetstring pour la chaine de cara du entre les balises
xmlstrcmm compare deux chaine de cara xml
xmlDocGetRootElement pour le premier noeud*/

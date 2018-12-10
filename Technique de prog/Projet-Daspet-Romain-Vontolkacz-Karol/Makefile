all:
	gcc -std=c89 -pedantic -Wall -Werror -g `pkg-config libxml-2.0 --cflags` -c -o movie.o movie.c -lxml2
	gcc -std=c89 -pedantic -Wall -Werror -g `pkg-config libxml-2.0 --cflags` -c -o vrs.o vrs.c -lxml2
	gcc -std=c89 -pedantic -Wall -Werror -g `pkg-config libxml-2.0 --cflags` -o vrsp.out vrsp.c vrs.o -lxml2
	movie.o `pkg-config libxml-2.0 --libs-only-L` `pkg-config libxml-2.0 --libs-only-l` -lxml2
clean :
	rm -f *.o

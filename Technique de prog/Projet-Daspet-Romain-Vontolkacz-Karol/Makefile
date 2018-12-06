all: movie.c vrs.c vrsp.c
	gcc -std=c89 -pedantic -Wall -Werror -g `pkg-config libxml-2.0 --cflags` -c -o movie.o movie.c
	gcc -std=c89 -pedantic -Wall -Werror -g `pkg-config libxml-2.0 --cflags` -c -o vrs.o vrs.c
	gcc -std=c89 -pedantic -Wall -Werror -g `pkg-config libxml-2.0 --cflags` -o vrsp.out vrsp.c vrs.o
	movie.o ‘pkg-config libxml-2.0 --libs-only-L‘ `pkg-config libxml-2.0 --libs-only-l`

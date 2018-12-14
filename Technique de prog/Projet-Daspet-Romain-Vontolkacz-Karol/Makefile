CC=gcc
CFLAGS= -std=c89 -pedantic -Wall -Werror -g `pkg-config libxml-2.0 --cflags`
LDFLAGS=`pkg-config libxml-2.0 --libs-only-L`
LDLIBS=`pkg-config libxml-2.0 --libs-only-l`
RM=rm -fv
all: vrsp.out
movie.o: movie.c movie.h
	$(CC) $(CFLAGS) -c -o movie.o movie.c
print.o: vrs.c vrs.h
	$(CC) $(CFLAGS) -c -o vrs.o vrs.c
vrsp.out: vrsp.c movie.o vrs.o
	$(CC) $(CFLAGS) -o vrsp.out vrsp.c movie.o vrs.o $(LDFLAGS) $(LDLIBS)
clean:
	$(RM)	*.o	*.out

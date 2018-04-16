CC=gcc
# warnings all and debugging
CFLAGS=-c -Wall -g
CURRENT_DIR := $(mem basename `pwd`)
THIS_FILE := $(lastword $(MAKEFILE_LIST))

all: hw5

hw5: mem.o main.o
	$(CC) mem.o main.o -o main

mem.o: mem.c mem.h
	$(CC) $(CFLAGS) mem.c

main.o:	main.c mem.h
	$(CC) $(CFLAGS) main.c

clean:
	/bin/rm -f main *.o *~

run:
	./main

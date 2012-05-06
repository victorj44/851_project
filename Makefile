#makefile for our hashmaps

CC=g++
CFLAGS= -g -Wall
LDFLAGS=


all:
	$(CC) $(CFLAGS) -o test test.cpp tabulationHash/tabulationHash.cpp

clean:
	rm -r -f *.o *.x */*.x */*.o
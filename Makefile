#makefile for our hashmaps

CC=g++
CFLAGS= -g -Wall
LDFLAGS=


all:
	$(CC) $(CFLAGS) -o test test.cpp tabulationHash/tabulationHash.cpp multiplicationHash/multiplicationHash.cpp
	$(CC) $(CFLAGS) -o testSanja testSanja.cpp tabulationHash/tabulationHash.cpp multiplicationHash/multiplicationHash.cpp

clean:
	rm -r -f *.o *.x */*.x */*.o

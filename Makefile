#makefile for our hashmaps

CC=g++
CFLAGS= -O2 -Wall
LDFLAGS=

all:
	$(CC) $(CFLAGS) -o test test.cpp tabulationHash/tabulationHash.cpp multiplicationHash/multiplicationHash.cpp
	$(CC) $(CFLAGS) -o testSanja testSanja.cpp tabulationHash/tabulationHash.cpp multiplicationHash/multiplicationHash.cpp
	$(CC) $(LDFLAGS) $(CLFAGS) -o benchmarks/bm1 benchmarks/bm1.cpp tabulationHash/tabulationHash.cpp multiplicationHash/multiplicationHash.cpp
	$(CC) $(LDFLAGS) $(CLFAGS) -o benchmarks/bm2 benchmarks/bm2.cpp tabulationHash/tabulationHash.cpp multiplicationHash/multiplicationHash.cpp
	$(CC) $(LDFLAGS) $(CLFAGS) -o benchmarks/bm3 benchmarks/bm3.cpp tabulationHash/tabulationHash.cpp multiplicationHash/multiplicationHash.cpp
	$(CC) $(LDFLAGS) $(CLFAGS) -o benchmarks/bm1_individual benchmarks/bm1_individual.cpp tabulationHash/tabulationHash.cpp multiplicationHash/multiplicationHash.cpp


clean:
	rm -r -f *.o *.x */*.x */*.o

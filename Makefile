CC = g++
CFLAGS = -g -Wall -std=c++11

all: LZ77

LZ77: mainLZ77.o analysis.o similarities.o lz77.o
	$(CC) $(CFLAGS) mainLZ77.o analysis.o similarities.o lz77.o -o LZ77

lz77.o: lz77.cpp
	$(CC) $(CFLAGS) -c lz77.cpp

similarities.o: similarities.cpp
	$(CC) $(CFLAGS) -c similarities.cpp

analysis.o: analysis.cpp
	$(CC) $(CFLAGS) -c analysis.cpp

mainLZ77.o: mainLZ77.cpp
	$(CC) $(CFLAGS) -c mainLZ77.cpp





#all:
#	$(CC) $(CFLAGS) -o lz77.o -c lz77.cpp
#	$(CC) $(CFLAGS) -o lz77equiv.o -c lz77equiv.cpp
#	$(CC) $(CFLAGS) -o mainLZ77.o -c mainLZ77.cpp
#	$(CC) $(CFLAGS) -o $(MAIN) lz77equiv.o mainLZ77.o
#
#allx: $(MAIN)
#
#run:
#	make all
#	./$(MAIN)
#
#$(MAIN): mainLZ77.o lz77equiv.o mainLZ77.o
#	$(CC) $(CFLAGS) -o $(MAIN) mainLZ77.o
#
#mainLZ77.o: mainLZ77.cpp lz77equiv.hpp
#	$(CC) $(CFLAGS) -o mainLZ77.o -c mainLZ77.cpp
#
#lz77equiv.o: lz77equiv.cpp lz77.hpp
#	$(CC) $(CFLAGS) -o lz77equiv.o -c lz77equiv.cpp
#
#lz77.o: lz77.cpp
#	$(CC) $(CFLAGS) -o lz77.o -c lz77.cpp


clean:
	rm *.o
	rm *~
	rm LZ77

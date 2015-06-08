CC = g++

CFLAGS = -g -Wall -std=c++11

OBJ = mainLZ77.o lz77.o lz77equiv.o
SRCM = mainLZ77.cpp
SRC = lz77.cpp

MAIN = LZ77

all: $(MAIN)

run:
	make all
	./$(MAIN)

$(MAIN): lz77equiv.o lz77.o mainLZ77.o
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJ)

lz77equiv.o: lz77equiv.cpp
	$(CC) $(CFLAGS) -o lz77.o -c lz77equiv.cpp

lz77.o: lz77.cpp
	$(CC) $(CFLAGS) -o lz77.o -c lz77.cpp

mainLZ77.o: $(SRCM) lz77.hpp lz77equiv.hpp
	$(CC) $(CFLAGS) -o mainLZ77.o -c $(SRCM)


clean:
	rm *.o
	rm *~
	rm $(MAIN)

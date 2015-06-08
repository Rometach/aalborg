CC = g++

CFLAGS = -g -Wall -std=c++11

#LIBS =

OBJ = mainLZ77.o lz77.o
SRCM = mainLZ77.cpp
SRC = lz77.cpp

MAIN = LZ77

# TEST = test/test

all: $(MAIN)

run:
	make all
	./$(MAIN)

$(MAIN): $(OBJ)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJ)

lz77.o: lz77.cpp
	$(CC) $(CFLAGS) -o lz77.o -c $(SRC)

mainLZ77.o: $(SRCM) lz77.hpp
	$(CC) $(CFLAGS) -o mainLZ77.o -c $(SRCM)

#$(MAIN): $(SRCM) $(SRC)
#	$(CC) $(CFLAGS) -o $(MAIN) $(SRCM)

#$(SRC): $(SRC)
#	$(CC) $(CFLAGS) -o $(SRC) $(SRC)

#.c.o:
#	$(CC) $(CFLAGS) -c $< -o $@

#test: $(OBJS) $(OBJT)
#	$(CC) $(CFLAGS) $(INCLUDES) -o $(TEST) $(OBJS) $(OBJT) $(LIBS)
#	./$(TEST)

clean:
	rm *.o
	rm *~
	rm $(MAIN)

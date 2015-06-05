CC = g++

CFLAGS = -g -Wall -std=c++11

#LIBS =

SRCM = mainLZ77.cpp

MAIN = LZ77

# TEST = test/test

all: $(MAIN)

run:
	make all
	./$(MAIN)

$(MAIN): $(SRCM)
	$(CC) $(CFLAGS) -o $(MAIN) $(SRCM)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

#test: $(OBJS) $(OBJT)
#	$(CC) $(CFLAGS) $(INCLUDES) -o $(TEST) $(OBJS) $(OBJT) $(LIBS)
#	./$(TEST)

clean:
	rm src/*.o src/*~ $(MAIN)

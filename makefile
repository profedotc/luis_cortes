CC = gcc $(CFLAGS)
CFLAGS = -Wall -Wextra -std=c99

.PHONY: all test debug release clean

all: gol

gol: gol.o
	$(CC) gol.o main.c -o gol

gol.o: gol.c gol.h
	$(CC) -c gol.c

clean:
	rm gol
	rm *.o

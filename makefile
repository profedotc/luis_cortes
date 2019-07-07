CC = gcc $(CFLAGS)
CFLAGS = -Wall -Wextra -std=c99

.PHONY: all test debug release clean

debug: CFLAGS += -g -O0
debug: gol

release: CFLAGS += -g -O3
release: gol

all: debug

gol: gol.o main.o
	$(CC) gol.o main.c -o gol

main.o: main.c gol.h
	$(CC) -c main.c

gol.o: gol.c gol.h
	$(CC) -c gol.c

clean:
	rm gol
	rm *.o

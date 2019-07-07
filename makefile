CC = gcc $(CFLAGS)
CFLAGS = -Wall -Wextra -std=c99

.PHONY: all test debug release clean test

debug: CFLAGS += -g -O0
debug: gol

release: CFLAGS += -g -O3
release: gol

all: debug

test : CFLAGS += -g -O0
test : mem_test
	valgrind --track-origins=yes --leak-check=full ./mem_test

gol: gol.o main.o
	$(CC) gol.o main.c -o gol

mem_test: mem_test.o gol.o
	$(CC) mem_test.o gol.o -o mem_test

main.o: main.c gol.h
	$(CC) -c main.c

gol.o: gol.c gol.h
	$(CC) -c gol.c

mem_test.o: mem_test.c gol.h
	$(CC) -c mem_test.c

clean:
	rm -f gol *.o mem_test

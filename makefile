all: mi_prog

mi_prog: main.o
	gcc main.o -o gol

main.o: main.c main.h
	gcc -c main.c

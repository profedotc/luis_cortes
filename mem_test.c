#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gol.h"

#define It 100

int main()
{
    int i = 0;

    struct gol worlds;
    gol_alloc(&worlds);

    gol_init(&worlds);
    while(i < It){
        gol_step(&worlds);
	i++;
    }
    gol_free(&worlds);

    return EXIT_SUCCESS;
}


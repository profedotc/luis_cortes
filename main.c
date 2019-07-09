#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gol.h"

int main()
{
    struct gol worlds;
    gol_alloc(&worlds);
    gol_init(&worlds);    

    int i = 0;
    do {
        printf("\033cIteration %d\n", i++);
        gol_print(&worlds);
        gol_step(&worlds);
    } while (getchar() != 'q');

    gol_free(&worlds);

    return EXIT_SUCCESS;
}


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gol.h"

int main()
{
    int i = 0;
    struct gol worlds;
    struct gol *pw = &worlds;
    gol_init(pw);
    do {
        printf("\033cIteration %d\n", i++);
        gol_print(pw);
        gol_step(pw);
    } while (getchar() != 'q');

    return EXIT_SUCCESS;
}


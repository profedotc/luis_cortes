#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gol.h"

int main()
{
    int i = 0;
    bool board[ROWS][COLS][2], w = 0;
    gol_init(board);
    do {
        printf("\033cIteration %d\n", i++);
        gol_print(board, w);
        gol_step(board, w);
        w = !w;
    } while (getchar() != 'q');

    return EXIT_SUCCESS;
}


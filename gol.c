#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gol.h"

static int count_neighbors(struct gol *, int x, int y);
static bool get_cell(struct gol *, int x, int y);

bool init[3][3] = {
    {0, 1, 0},
    {0, 0, 1},
    {1, 1, 1}
};

void gol_alloc(struct gol *worlds)
{
    worlds->board = (bool ***) malloc(ROWS * sizeof(bool**));
    for(int i = 0; i < ROWS; i++){
        worlds->board[i] = (bool **) malloc(COLS * sizeof(bool*));
        for(int j = 0; j < COLS; j++)
            worlds->board[i][j] = (bool *) malloc(2 * sizeof(bool));
    }
}

void gol_free(struct gol *worlds)
{
    for(int i = 0; i< ROWS; i++){
        for(int j = 0; j < COLS; j++)
            free(worlds->board[i][j]);
	free(worlds->board[i]);
    }
    free(worlds->board);
}

void gol_init(struct gol *worlds)
{
    for(int i = 0; i < ROWS; i++)
        for(int j = 0; j < COLS; j++)
            worlds->board[i][j][0] = (i < 3 && j < 3)?init[i][j]:0;
    worlds->cw = 0;
}

void gol_print(struct gol *worlds)
{
   bool w = worlds->cw;
   for(int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++)
            printf("%c ", (worlds->board[i][j][w])?'#':'.');
        printf("\n");
        }
}

void gol_step(struct gol *worlds)
{
    bool w = worlds->cw;
    int x, y, cell, neighbors;
    for(x = 0; x < ROWS; x++)
        for(y = 0; y < COLS; y++){
        cell = worlds->board[x][y][w];
        neighbors = count_neighbors(worlds, x, y) - cell;
            if (cell)
                worlds->board[x][y][!w] = (neighbors == 2 || neighbors == 3);
            else
                worlds->board[x][y][!w] = neighbors == 3;
        }
    worlds->cw = !worlds->cw;
}

// Funciones estáticas
static int count_neighbors(struct gol *worlds, int x, int y)
{
    int k, z, neighbors = 0;
    for(k = -MAX_DIST; k <= MAX_DIST; k++)
        for(z = -MAX_DIST; z <= MAX_DIST; z++)
            neighbors += get_cell(worlds, x + k, y + z);
    return neighbors;
}

static bool get_cell(struct gol *worlds, int x, int y)
{
    if (x >= 0 && x < ROWS && y >= 0 && y < COLS)
        return worlds->board[x][y][worlds->cw];
    return 0;
}



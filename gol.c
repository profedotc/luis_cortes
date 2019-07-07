#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gol.h"

static bool get_cell(struct gol *, int, int);
static void set_cell(struct gol *, int, int, bool);
static bool get_cw(struct gol *);
static void set_cw(struct gol *, bool);
static int fix_coords(int, int);
static int count_neighbors(struct gol *, int, int);

bool init[3][3] = {
    {0, 1, 0},
    {0, 0, 1},
    {1, 1, 1}
};

void gol_alloc(struct gol *worlds)
{
    worlds->board[0] = (bool *) malloc(ROWS * COLS * sizeof(bool));
    worlds->board[1] = (bool *) malloc(ROWS * COLS * sizeof(bool));
}

void gol_free(struct gol *worlds)
{
    free(worlds->board[0]);
    free(worlds->board[1]);
}

void gol_init(struct gol *worlds)
{
    set_cw(worlds, 1);
    for(int i = 0; i < ROWS; i++)
        for(int j = 0; j < COLS; j++)
            set_cell(worlds,i,j,(i < 3 && j < 3)?init[i][j]:0);
    set_cw(worlds, 0);
}

void gol_print(struct gol *worlds)
{
   for(int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++)
            printf("%c ", get_cell(worlds, i, j)?'#':'.');
        printf("\n");
        }
}

void gol_step(struct gol *worlds)
{
    int cell, neighbors;
    for(int x = 0; x < ROWS; x++)
        for(int y = 0; y < COLS; y++){
        cell = get_cell(worlds,x,y);
        neighbors = count_neighbors(worlds, x, y) - cell;
            if (cell)
                set_cell(worlds, x, y, (neighbors == 2 || neighbors == 3));
            else
                set_cell(worlds, x, y, neighbors == 3);
        }
    set_cw(worlds, !get_cw(worlds));
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
    return worlds->board[worlds->cw][fix_coords(x,y)];
}

static void set_cell(struct gol *worlds, int x, int y, bool b)
{
    worlds->board[!worlds->cw][fix_coords(x,y)] = b;
}

static int fix_coords(int x, int y)
{
    x = (x % ROWS + ROWS) % ROWS;
    y = (y % COLS + COLS) % COLS;
    return  x * COLS + y;
}

static bool get_cw(struct gol *worlds)
{
    return worlds->cw;
}

static void set_cw(struct gol *worlds, bool b)
{
    worlds->cw = b;
}

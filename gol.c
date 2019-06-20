#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gol.h"

bool init[3][3] = {
    {0, 1, 0},
    {0, 0, 1},
    {1, 1, 1}
};

void gol_init(bool board[ROWS][COLS][2])
{
    for(int i = 0; i < ROWS; i++)
        for(int j = 0; j < COLS; j++)
            board[i][j][0] =(i < 3 && j < 3)?init[i][j]:0;
}

void gol_print(bool board[ROWS][COLS][2], bool w)
{
   for(int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++)
            printf("%c ", (board[i][j][w])?'#':'.');
        printf("\n");
        }
}

void gol_step(bool board[ROWS][COLS][2], bool w)
{
    int x, y, cell, neighbors;
    for(x = 0; x < ROWS; x++)
        for(y = 0; y < COLS; y++){
        cell = board[x][y][w];
        neighbors = gol_count_neighbors(board, w, x, y) - cell;
            if (cell)
                board[x][y][!w] = (neighbors == 2 || neighbors == 3);
            else
                board[x][y][!w] = neighbors == 3;
        }
}

int gol_count_neighbors(bool board[ROWS][COLS][2], bool w, int x, int y)
{
    int k, z, neighbors = 0;
    for(k = -MAX_DIST; k <= MAX_DIST; k++)
        for(z = -MAX_DIST; z <= MAX_DIST; z++)
            neighbors += gol_get_cell(board, w, x + k, y + z);
    return neighbors;
}

bool gol_get_cell(bool board[ROWS][COLS][2], bool w, int x, int y)
{
    if (TOROID)
        return board[((x % ROWS) + ROWS) % ROWS][((y % COLS + COLS)) % COLS][w];
    else if (x >= 0 && x < ROWS && y >= 0 && y < COLS)
        return board[x][y][w];
    return 0;
}

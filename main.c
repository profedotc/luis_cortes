#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include <assert.h>

#define MAX_DIST 1
#define ROWS 16
#define COLUMNS 16
#define TOROID 0

void gol_init(bool *);
void gol_print(bool *);
void gol_step(bool *, bool *);
char gol_count_neighbors(bool *, char, char);
bool gol_get_cell(bool *, char, char);
void gol_copy(bool *, bool *);

bool init[3][3] = {
    {0, 1, 0},
    {0, 0, 1},
    {1, 1, 1}
};

int main()
{
	int i = 0;
	bool board[ROWS * COLUMNS];
    bool board_copy[ROWS * COLUMNS];
	gol_init(board);
	do {
		printf("\033cIteration %d\n", i++);
		gol_print(board);
		gol_step(board, board_copy);
	} while (getchar() != 'q');

	return EXIT_SUCCESS;
}

void gol_init(bool *board)
{
    char i, j;
    for(i = 0; i < ROWS; i++)
        for(j = 0; j < COLUMNS; j++)
            board[ROWS * i + j] =(i < 3 && j < 3)?init[i][j]:0;
}

void gol_print(bool *board)
{
   for(char i = 0; i < ROWS; i++){
        for (char j = 0; j < COLUMNS; j++)
            printf("%c ",(board[ROWS * i + j])?'#':'.');
        printf("\n");
	    }
}

void gol_step(bool *board, bool *board_copy)
{
    char cell, neighbors;
    gol_copy(board, board_copy);
    for(char x = 0; x < ROWS; x++)
        for(char y = 0; y < COLUMNS; y++){
		    cell = board_copy[ROWS * x + y];
			neighbors = gol_count_neighbors(board_copy, x, y) - cell;               
            if (cell)
                board[ROWS * x + y] = (neighbors == 2 || neighbors == 3);
            else
                board[ROWS * x + y] = neighbors == 3;
        }
}

char gol_count_neighbors(bool *board, char x, char y)
{
	char a, b, in_board;
	char neighbors = 0;
	for(char k = -MAX_DIST; k < MAX_DIST + 1; k++)
	    for(char z = -MAX_DIST; z < MAX_DIST + 1; z++){
	        if (TOROID){
                a = (((x + k) % ROWS) + ROWS) % ROWS;
                b = (((y + z) % COLUMNS) + COLUMNS) % COLUMNS;
                neighbors += board[ROWS * a + b];
            } else {
                a = x + k;
                b = y + z;
                neighbors += gol_get_cell(board, a, b);
           }
		}
	return neighbors;
}

bool gol_get_cell(bool *board, char x, char y)
{
// assert(x >= 0 && x < ROWS && y >= 0 && y < COLUMNS);
	if ((x >= 0 && x < ROWS && y >= 0 && y < COLUMNS) || TOROID)
        return board[ROWS * x + y];
    return 0;
}

void gol_copy(bool *board, bool *board_copy)
{
	for(char i = 0; i < ROWS; i++)
    	for(char j = 0; j < COLUMNS; j++)
        	board_copy[ROWS * i + j] = board[ROWS * i + j];
}

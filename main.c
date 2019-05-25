#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include <assert.h>

#define MAX_DIST 1
#define ROWS 16
#define COLUMNS 16
#define TOROID 0

void gol_init(bool [ROWS][COLUMNS][2]);
void gol_print(bool [ROWS][COLUMNS][2], bool);
void gol_step(bool [ROWS][COLUMNS][2], bool);
char gol_count_neighbors(bool [ROWS][COLUMNS][2], bool, char, char);
bool gol_get_cell(bool [ROWS][COLUMNS][2], bool, char, char);

bool init[3][3] = {
    {0, 1, 0},
    {0, 0, 1},
    {1, 1, 1}
};

int main()
{
	int i = 0;
	bool board[ROWS][COLUMNS][2], w = 0;
	gol_init(board);
	do {
		printf("\033cIteration %d\n", i++);
		gol_print(board, w);
		gol_step(board, w);
        w = !w;
	} while (getchar() != 'q');

	return EXIT_SUCCESS;
}

void gol_init(bool board[ROWS][COLUMNS][2])
{
    char i, j;
    for(i = 0; i < ROWS; i++)
        for(j = 0; j < COLUMNS; j++)
            board[i][j][0] =(i < 3 && j < 3)?init[i][j]:0;
}

void gol_print(bool board[ROWS][COLUMNS][2], bool w)
{
   for(char i = 0; i < ROWS; i++){
        for (char j = 0; j < COLUMNS; j++)
            printf("%c ", (board[i][j][w])?'#':'.');
        printf("\n");
	    }
}

void gol_step(bool board[ROWS][COLUMNS][2], bool w)
{
    char cell, neighbors;
    for(char x = 0; x < ROWS; x++)
        for(char y = 0; y < COLUMNS; y++){
		    cell = board[x][y][w];
			neighbors = gol_count_neighbors(board, w, x, y) - cell;
            if (cell)
                board[x][y][!w] = (neighbors == 2 || neighbors == 3);
            else
                board[x][y][!w] = neighbors == 3;
        }
}

char gol_count_neighbors(bool board[ROWS][COLUMNS][2], bool w, char x, char y)
{
	char a, b, in_board;
	char neighbors = 0;
	for(char k = -MAX_DIST; k < MAX_DIST + 1; k++)
	    for(char z = -MAX_DIST; z < MAX_DIST + 1; z++){
	        if (TOROID){
                a = (((x + k) % ROWS) + ROWS) % ROWS;
                b = (((y + z) % COLUMNS) + COLUMNS) % COLUMNS;
                neighbors += gol_get_cell(board, w, a, b);
            } else {
                a = x + k;
                b = y + z;
                neighbors += gol_get_cell(board, w, a, b);
           }
		}
	return neighbors;
}

bool gol_get_cell(bool board[ROWS][COLUMNS][2], bool w, char x, char y)
{
// assert(x >= 0 && x < ROWS && y >= 0 && y < COLUMNS);
	if ((x >= 0 && x < ROWS && y >= 0 && y < COLUMNS) || TOROID)
        return board[x][y][w];
    return 0;
}

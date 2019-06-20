#ifndef _GOL_H_
#define _GOL_H_

#include <stdbool.h>

#define MAX_DIST 1
#define ROWS 16
#define COLS 16
#define TOROID 0

void gol_init(bool [ROWS][COLS][2]);
void gol_step(bool [ROWS][COLS][2], bool);
void gol_print(bool [ROWS][COLS][2], bool);
int gol_count_neighbors(bool [ROWS][COLS][2], bool, int, int);
bool gol_get_cell(bool [ROWS][COLS][2], bool, int, int);

#endif

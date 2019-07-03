#ifndef _GOL_H_
#define _GOL_H_

#include <stdbool.h>

#define MAX_DIST 1
#define ROWS 16
#define COLS 24

struct gol {
	bool board[ROWS][COLS][2];
        bool cw;
};

void gol_init(struct gol *);
void gol_step(struct gol *);
void gol_print(struct gol *);

#endif

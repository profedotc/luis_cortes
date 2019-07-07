#ifndef _GOL_H_
#define _GOL_H_

#include <stdbool.h>

#define MAX_DIST 1
#define ROWS 16
#define COLS 24

struct gol {
	bool ***board;
        int cw; // current_world
};

void gol_init(struct gol *);
void gol_step(struct gol *);
void gol_print(struct gol *);

void gol_alloc(struct gol *);
void gol_free(struct gol *);

#endif

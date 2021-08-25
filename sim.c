/**
 * Assignment: life
 * Name: Kyle Nakai
 * PID: A15867067
 * Class: UCSD CSE30-WI21
 *
 */
#include "sim.h"

#define CIMP
extern void asm_doRow(belem *, belem *, belem *, uint32_t);

/**
 * process one row of the board
 */
static void doRow(belem *dest, belem *srcStart, belem * srcEnd, uint32_t cols){
  // TODO:
  	int i;
 	for (i = 0; i < cols - 2; i++){
		int neighbors = 0;
		if(*(srcStart + i - 1) == 1){
			neighbors++;
		}
		if(*(srcStart + i + 1) == 1){
			neighbors++;
		}
		if(*(srcStart + i + cols) == 1){
			neighbors++;
		}
		if(*(srcStart + i + cols - 1) == 1){
			neighbors++;
		}
		if(*(srcStart + i + cols + 1) == 1){
			neighbors++;
		}
		if(*(srcStart + i - cols) == 1){
			neighbors++;
		}
		if(*(srcStart + i - cols - 1) == 1){
			neighbors++;
		}
		if(*(srcStart + i - cols + 1) == 1){
			neighbors++;
		}

		if (*(srcStart + i) == 0){
			if (neighbors == 3){
				*(dest + i) = 1;
			}
			else{
				*(dest + i) = 0;
			}
		}
		else{
			if (neighbors == 0 || neighbors == 1){
				*(dest + i) = 0;
			}
			else if (neighbors == 2 || neighbors == 3){
				*(dest + i) = 1;
			}
			else{
				*(dest + i) = 0;
			}
		}
	}
}


/**
 * perform a simulation for "steps" generations
 *
 * for steps
 *   calculate the next board
 *   swap current and next
 */
void simLoop(boards_t *self, uint32_t steps){
  // TODO:
	int i;
	int j;
	
	belem *dest;
	belem *start;
	belem *end;

	int cols = self->numCols;

	int step = steps;

	for (i = 0; i < step; i++){
		int ind1 = cols + 1;
		int ind2 = 2 * (cols - 1);
		for (j = 0; j < self->numRows - 2; j++){
			dest = (self->nextBuffer + ind1);
			start = (self->currentBuffer + ind1);
			end = (self->currentBuffer + ind2);
			doRow(dest, start, end, cols);
			ind1 = ind1 + cols;
			ind2 = ind2 + cols;
		}
		swapBuffers(self);
		self->gen++;
	}
}





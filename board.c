/**
 * Assignment: life
 * Name : Kyle Nakai
 * PID: A15867067
 * Class: UCSD CSE30-WI21
 *
 */
#include "cse30life.h"
#include "board.h"


/**
 * create a new board
 *
 * - malloc a boards structure
 * - set the generation to 0
 * - open the file (if it doesn't exist, return a NULL pointer
 * - read the first line which is the number of rows
 * - read the second line which is the number of cols
 * - set the # of rows and # of cols in the boards structure
 * - malloc bufferA and bufferB 
 * - Set currentBuffer and nextBuffer
 * - clear both board buffers
 * - read the file until done.  each row contains a row and a columns separted by
 *   white space
 *     for each line, set the cell in the current buffer
 * - ensure that no border cells are set to alive
 * - close the file
 * - return the boards pointer if successfull or NULL ptr otherwise
 */
boards_t * createBoard(char *initFileName){
  // TODO: 
  	FILE *fp;
	if ((fp = fopen(initFileName, "r")) == NULL){
		return NULL;
	}
	boards_t *bptr = (boards_t *)malloc(sizeof(boards_t));

	int number;
	fscanf(fp, "%d", &number);
	bptr->numRows = number;

	fscanf(fp, "%d", &number);
	bptr->numCols = number;

	int size = bptr->numRows * bptr->numCols;

	bptr->bufferA = (belem *)malloc(sizeof(belem) * size);
	bptr->bufferB = (belem *)malloc(sizeof(belem) * size);

	bptr->currentBuffer = bptr->bufferA;
	bptr->nextBuffer = bptr->bufferB;

	clearBoards(bptr);

	int num;
	int numTwo;
	
	while(fscanf(fp, "%d %d", &num, &numTwo) > 0){
		int index = getIndex(bptr, num, numTwo);
		*(bptr->currentBuffer + index) = 1;	
	}
	fclose(fp);

	int cols = bptr->numCols;
	int i;
	for (i = 0; i < size; i++){
		if (i <= cols){
			*(bptr->currentBuffer + i) = 0;
		}
		else if ((i % cols) == 0 || (i % cols) == (cols - 1)){
			*(bptr->currentBuffer + i) = 0;
		}
		if (i >= size - bptr->numCols){
			*(bptr->currentBuffer + i) = 0;
		}
	}
	bptr->gen = 0;
	return bptr;
}



/**
 * delete a board
 */
void deleteBoard(boards_t **bptrPtr){
  // TODO:
  	free((*bptrPtr)->bufferA);
	free((*bptrPtr)->bufferB);
	free(*bptrPtr);
	*bptrPtr = NULL;
}

/**
 * set all the belems in both buffers to 0
 */
void clearBoards(boards_t *self){
  // TODO:
  int rows = self->numRows;
  int cols = self->numCols;
  memset(self->bufferA, 0, rows * cols * sizeof(belem));
  memset(self->bufferB, 0, rows * cols * sizeof(belem));
}

/**
 * swap the current and next buffers
 */
void swapBuffers(boards_t *self){
  // TODO:
  	belem *temp = self->currentBuffer;
	self->currentBuffer = self->nextBuffer;
	self->nextBuffer = temp;
}


/**
 * get a cell index
 */
int getIndex(boards_t *self, int row, int col){
  // TODO:
  return row * self->numCols + col;
}
  

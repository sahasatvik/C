#ifndef _BOARD_H
#define _BOARD_H

#define NOUGHTS_WIN -100
#define CROSSES_WIN +100

/* Types of symbols in the grid */
typedef enum {
        EMPTY = 0,
        NOUGHT = -1,
        CROSS = +1
} BoardItem;

/* The tic-tac-toe board records the positions of the noughts and crosses as
   bit flags, along with the current turn and the best move (set by minimax) */
typedef struct {
        unsigned int noughts;
        unsigned int crosses;
        BoardItem turn;
        int bestmove;
} Board;

/* Initialize an empty board, crosses get the first move */
Board *board_init();
/* Free the board from memory */
void board_free(Board *);

/* Get the symbol at a given position (0-8) */
BoardItem board_get(Board *, int);
/* Set the symbol at the given position (0-8) */
void board_set(Board *, int, BoardItem);

/* Check whether a side has won, return the appropriate evaluation */
int board_won(Board *);
/* Calculate the evaluation of the current position using the minimax algorithm,
   and set board->bestmove appropriately */
int minimax(Board *, BoardItem, int);

/* Display the tic-tac-toe board */
void board_show(Board *);

#endif

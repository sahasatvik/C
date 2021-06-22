#ifndef _BOARDBIG_H
#define _BOARDBIG_H

#define NOUGHTS_WIN -1000
#define CROSSES_WIN +1000

/* Types of symbols in the grid */
typedef enum {
        EMPTY = 0,
        NOUGHT = -1,
        CROSS = +1
} BoardItem;

typedef struct {
        BoardItem **cells;
        int width, height;
        int target;
        BoardItem turn;
        int moves;
        int bestmove_i, bestmove_j;
} BoardBig;

/* Initialize an empty board, crosses get the first move */
BoardBig *board_init(int, int, int);
/* Free the board from memory */
void board_free(BoardBig *);

/* Check whether a side has won, return the appropriate evaluation */
int board_won(BoardBig *);
int board_heuristic(BoardBig *);
/* Calculate the evaluation of the current position using the minimax algorithm,
   and set board->bestmove appropriately */
int minimax(BoardBig *, BoardItem, int, int);

/* Display the tic-tac-toe board */
void board_show(BoardBig *);

#endif

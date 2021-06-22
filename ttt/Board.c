#include <stdlib.h>
#include <stdio.h>
#include "Board.h"

Board *board_init() {
        Board *board = malloc(sizeof(Board));
        board->noughts = 0;
        board->crosses = 0;
        board->turn = CROSS;
        return board;
}

void board_free(Board *board) {
        free(board);
}

BoardItem board_get(Board *board, int position) {
        /* The bit in the 2^i th place is on if a nought/cross is placed there */
        if (board->noughts & (1 << position))
                return NOUGHT;
        if (board->crosses & (1 << position))
                return CROSS;
        return EMPTY;
}

void board_set(Board *board, int position, BoardItem item) {
        switch (item) {
                case NOUGHT:
                        board->noughts |= 1 << position;
                        break;
                case CROSS:
                        board->crosses |= 1 << position;
                        break;
                case EMPTY:
                        board->noughts &= ~(1 << position);
                        board->crosses &= ~(1 << position);
                        break;
        }
}

int board_won(Board *board) {
        /* The game has been won if the noughts/crosses bit pattern matches one of
           these three-in-a-row patterns */
        static const unsigned int three_in_a_row[] = {
                0007,   // Horizontal patterns
                0070,
                0700,
                0111,   // Vertical patterns
                0222,
                0444,
                0421,   // Diagonal patterns
                0124
        };
        for (int i = 0; i < 8; i++) {
                if ((three_in_a_row[i] & board->noughts) == three_in_a_row[i])
                        return NOUGHTS_WIN;
                if ((three_in_a_row[i] & board->crosses) == three_in_a_row[i])
                        return CROSSES_WIN;
        }
        return 0;
}

int minimax(Board *board, BoardItem turn, int depth) {
        int eval = board_won(board);
        /* Neutral if nobody wins and the board is full */
        if (eval == 0 && (board->noughts | board->crosses) == 0777)
                return 0;
        /* If the board has been won, return the evaluation with a penalty on depth */
        if (eval == NOUGHTS_WIN || eval == CROSSES_WIN)
                return eval + (turn * depth);
        eval = 100 * turn * -1;
        int bestmove = -1;
        for (int i = 0; i < 9; i++) {
                /* Try to make a move at position i */
                if (board_get(board, i) != EMPTY)
                        continue;
                board_set(board, i, turn);
                /* Recursively calculate the resultant evaluation */
                int next_eval = minimax(board, turn * -1, depth + 1);
                /* Maximize the evaluation, relative to whose turn it is */
                if ((next_eval * turn) > (eval * turn)) {
                        eval = next_eval;
                        bestmove = i;
                }
                board_set(board, i, EMPTY);
        }
        /* Record the best move, and return the evaluation */
        board->bestmove = bestmove;
        return eval;
}

void board_show(Board *board) {
        for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                        switch (board_get(board, i * 3 + j)) {
                                case NOUGHT:
                                        printf("O ");
                                        break;
                                case CROSS:
                                        printf("X ");
                                        break;
                                case EMPTY:
                                        printf("- ");
                                        break;
                        }
                }
                printf("\n");
        }
}

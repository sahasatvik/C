#include <stdio.h>
#include "Board.h"

void take_turn(Board *);

int main(int argc, const char *argv[]) {
        Board *board = board_init();
        
        board_show(board);
        printf("\n");

        /* Play at most 9 moves */
        for (int i = 0; i < 9; i++) {
                take_turn(board);
                printf("\n");
                board_show(board);
                printf("\n");

                /* Stop if either side has won, or there are no more moves */
                int eval = board_won(board);
                if (eval == NOUGHTS_WIN) {
                        printf("Noughts win!\n");
                        break;
                } else if (eval == CROSSES_WIN) {
                        printf("Crosses win!\n");
                        break;
                } else if (eval == 0 && i == 8) {
                        printf("Draw!\n");
                }
        }

        board_free(board);
        return 0;
}

void take_turn(Board *board) {
        /* The computer play noughts */
        if (board->turn == NOUGHT) {
                int eval = minimax(board, NOUGHT, 0);
                board_set(board, board->bestmove, NOUGHT);
                printf("Computer played %d (evaluation %d).\n", board->bestmove, eval);
        } else {
                int pos, c;
                /* Prompt the player for the move */
                do {
                        printf("Your turn: ");
                        scanf("%d", &pos);
                        if (pos >= 0 && pos < 9 && board_get(board, pos) == EMPTY)
                                break;
                        while ((c = getchar()) != '\n' && c != EOF);    // Skip extra characters
                } while (1);
                board_set(board, pos, board->turn);
        }
        board->turn *= -1;
}

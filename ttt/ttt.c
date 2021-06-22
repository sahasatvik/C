#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Board.h"

void take_turn(Board *, BoardItem, int);
void usage();

int main(int argc, char * const argv[]) {
        BoardItem computer = NOUGHT;

        /* Read the command line options */
        int c, cflag = 0, nflag = 0, eflag = 0;
        while ((c = getopt(argc, argv, "hcne")) != -1) {
                switch (c) {
                        case 'h':
                                printf("Tic-tac toe vs the computer.\n");
                                usage();
                                exit(0);
                                break;
                        case 'c':
                                cflag++;
                                break;
                        case 'n':
                                nflag++;
                                break;
                        case 'e':
                                eflag++;
                                break;
                        case '?':
                                usage();
                                exit(1);
                                break;
                }
        }
        if (cflag && nflag) {
                printf("%s: can only use one of -c, -n\n", argv[0]);
                exit(1);
        }
        if (cflag)
                computer = NOUGHT;
        if (nflag)
                computer = CROSS;

        Board *board = board_init();
        
        board_show(board);
        printf("\n");

        /* Play at most 9 moves */
        for (int i = 0; i < 9; i++) {
                take_turn(board, computer, eflag);
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

void take_turn(Board *board, BoardItem computer, int showeval) {
        if (board->turn == computer) {
                /* The computer plays using the minimax algorithm */
                int eval = minimax(board, board->turn, 0);
                board_set(board, board->bestmove, board->turn);
                printf("Computer played %d", board->bestmove);
                if (showeval)
                        printf(" (evaluation %d)\n", eval);
                else
                        printf("\n");
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

void usage() {
        printf("usage: ttt [-he] [-c | -n]\n");
        printf("    -h  Show this help message\n");
        printf("    -c  Take the first turn (crosses) [default]\n");
        printf("    -n  Take the second turn (noughts)\n");
        printf("    -e  Show the computer evaluation\n");
}

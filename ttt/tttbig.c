#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "BoardBig.h"

void take_turn(BoardBig *, BoardItem, int, int);
void usage();

int main(int argc, char * const argv[]) {
        BoardItem computer = NOUGHT;
        int width = 4, height = 4, target = 4, depth = 5;

        /* Read the command line options */
        int c, cflag = 0, nflag = 0, eflag = 0;
        while ((c = getopt(argc, argv, "hcnex:y:t:d:")) != -1) {
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
                        case 'x':
                                width = atoi(optarg);
                                break;
                        case 'y':
                                height = atoi(optarg);
                                break;
                        case 't':
                                target = atoi(optarg);
                                break;
                        case 'd':
                                depth = atoi(optarg);
                                break;
                        case ':':
                                printf("%s: option requires an argument -- %c\n", argv[0], optopt);
                        case '?':
                                usage();
                                exit(1);
                                break;
                }
        }
        if (cflag && nflag) {
                printf("%s: can only use one of -c, -n\n", argv[0]);
                usage();
                exit(1);
        }
        if (cflag)
                computer = NOUGHT;
        if (nflag)
                computer = CROSS;

        BoardBig *board = board_init(width, height, target);
        
        board_show(board);
        printf("\n");

        for (int i = 0; i < board->width * board->height; i++) {
                take_turn(board, computer, eflag, depth);
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
                } else if (eval == 0 && i == (board->width * board->height - 1)) {
                        printf("Draw!\n");
                }
        }

        board_free(board);
        return 0;
}

void take_turn(BoardBig *board, BoardItem computer, int showeval, int maxdepth) {
        if (board->turn == computer) {
                /* The computer plays using the minimax algorithm */
                int eval = minimax(board, board->turn, 0, maxdepth);
                board->cells[board->bestmove_i][board->bestmove_j] = board->turn;
                printf("Computer played %d %d", board->bestmove_i, board->bestmove_j);
                if (showeval)
                        printf(" (evaluation %d)\n", eval);
                else
                        printf("\n");
        } else {
                int pos_i, pos_j, c;
                /* Prompt the player for the move */
                do {
                        printf("Enter a move (row column): ");
                        scanf("%d %d", &pos_i, &pos_j);
                        if (pos_i >= 0 && pos_i < board->height &&
                            pos_j >= 0 && pos_j < board->width && 
                            board->cells[pos_i][pos_j] == EMPTY)
                                break;
                        while ((c = getchar()) != '\n' && c != EOF);    // Skip extra characters
                } while (1);
                board->cells[pos_i][pos_j] = board->turn;
        }
        board->moves++;
        board->turn *= -1;
}

void usage() {
        printf("usage: tttbig [-he] [-c | -n] [-x width] [-y height] [-t target] [-d depth]\n");
        printf("    -h  Show this help message\n");
        printf("    -c  Take the first turn (crosses) [default]\n");
        printf("    -n  Take the second turn (noughts)\n");
        printf("    -x  Board width [default 4]\n");
        printf("    -y  Board height [default 4]\n");
        printf("    -t  Target for t-in-a-row [default 4]\n");
        printf("    -e  Show the computer evaluation\n");
        printf("    -d  Maximum depth while minimaxing [default 5]\n");
}

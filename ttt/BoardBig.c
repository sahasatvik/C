#include <stdlib.h>
#include <stdio.h>
#include "BoardBig.h"

BoardBig *board_init(int width, int height, int target) {
        BoardBig *board = malloc(sizeof(BoardBig));
        board->width = width;
        board->height = height;
        board->target = target;
        board->turn = CROSS;
        board->moves = 0;
        board->cells = calloc(height, sizeof(BoardItem *));
        for (int i = 0; i < height; i++)
                board->cells[i] = calloc(width, sizeof(BoardItem));
        return board;
}

void board_free(BoardBig *board) {
        for (int i = 0; i < board->height; i++)
                free(board->cells[i]);
        free(board->cells);
        free(board);
}

int board_won(BoardBig *board) {
        for (int i = 0; i < board->height; i++) {
                for (int j = 0; j <= board->width - board->target; j++) {
                        int hcount = 0;
                        for (int k = 0; k < board->target; k++) {
                                hcount += board->cells[i][j + k];
                        }
                        if (hcount  == board->target * NOUGHT)
                                return NOUGHTS_WIN;
                        if (hcount  == board->target * CROSS)
                                return CROSSES_WIN;
                }
        }
        for (int i = 0; i <= board->height - board->target; i++) {
                for (int j = 0; j < board->width; j++) {
                        int vcount = 0;
                        for (int k = 0; k < board->target; k++) {
                                vcount += board->cells[i + k][j];
                        }
                        if (vcount  == board->target * NOUGHT)
                                return NOUGHTS_WIN;
                        if (vcount  == board->target * CROSS)
                                return CROSSES_WIN;
                }
        }
        for (int i = 0; i <= board->height - board->target; i++) {
                for (int j = 0; j <= board->width - board->target; j++) {
                        int ldcount = 0, rdcount = 0;
                        for (int k = 0; k < board->target; k++) {
                                ldcount += board->cells[i + k][j + k];
                                rdcount += board->cells[i + k][j + board->target - k - 1];
                        }
                        if (ldcount == board->target * NOUGHT ||
                            rdcount == board->target * NOUGHT)
                                return NOUGHTS_WIN;
                        if (ldcount == board->target * CROSS ||
                            rdcount == board->target * CROSS)
                                return CROSSES_WIN;
                }
        }
        return 0;
}

int board_heuristic(BoardBig *board) {
        int eval = 0;
        BoardItem sym;
        for (int i = 0; i < board->height; i++) {
                for (int j = 0; j <= board->width - board->target; j++) {
                        int hcount_n, hcount_c = 0;
                        for (int k = 0; k < board->target; k++) {
                                sym = board->cells[i][j + k];
                                hcount_n += (sym == NOUGHT);
                                hcount_c += (sym == CROSS);
                        }
                        if (hcount_n > 0 && hcount_c == 0)
                                eval += hcount_n * NOUGHT;
                        if (hcount_c > 0 && hcount_n == 0)
                                eval += hcount_c * CROSS;
                }
        }
        for (int i = 0; i <= board->height - board->target; i++) {
                for (int j = 0; j < board->width; j++) {
                        int vcount_n = 0, vcount_c = 0;
                        for (int k = 0; k < board->target; k++) {
                                sym = board->cells[i + k][j];
                                vcount_n += (sym == NOUGHT);
                                vcount_c += (sym == CROSS);
                        }
                        if (vcount_n > 0 && vcount_c == 0)
                                eval += vcount_n * NOUGHT;
                        if (vcount_c > 0 && vcount_n == 0)
                                eval += vcount_c * CROSS;
                }
        }
        for (int i = 0; i <= board->height - board->target; i++) {
                for (int j = 0; j <= board->width - board->target; j++) {
                        int ldcount_n = 0, ldcount_c = 0;
                        int rdcount_n = 0, rdcount_c = 0;
                        for (int k = 0; k < board->target; k++) {
                                sym = board->cells[i + k][j + k];
                                ldcount_n += (sym == NOUGHT);
                                ldcount_c += (sym == CROSS);
                                sym = board->cells[i + k][j + board->target - k - 1];
                                rdcount_n += (sym == NOUGHT);
                                rdcount_c += (sym == CROSS);
                        }
                        if (ldcount_n > 0 && ldcount_c == 0)
                                eval += ldcount_n * NOUGHT;
                        if (ldcount_c > 0 && ldcount_n == 0)
                                eval += ldcount_c * CROSS;
                        if (rdcount_n > 0 && rdcount_c == 0)
                                eval += rdcount_n * NOUGHT;
                        if (rdcount_c > 0 && rdcount_n == 0)
                                eval += rdcount_c * CROSS;
                }
        }
        return eval;
}

int minimax(BoardBig *board, BoardItem turn, int depth, int maxdepth) {
        int eval = board_won(board);
        /* Neutral if nobody wins and the board is full */
        if (eval == 0 && (board->moves == board->width * board->height))
                return 0;
        /* If the board has been won, return the evaluation with a penalty on depth */
        if (eval == NOUGHTS_WIN || eval == CROSSES_WIN)
                return eval + (turn * board->moves);
        /* Use a heuristic if maximum depth reached */
        if (depth > maxdepth)
                return board_heuristic(board) + (turn * board->moves);
        eval = 1000 * turn * -1;
        board->moves++;
        int bestmove_i, bestmove_j;
        for (int i = 0; i < board->height; i++) {
                for (int j = 0; j < board->width; j++) {
                        /* Skip non-empty cells */
                        if (board->cells[i][j] != EMPTY)
                                continue;
                        /* Make a move */
                        board->cells[i][j] = turn;
                        /* Recursively calculate the resultant evaluation */
                        int next_eval = minimax(board, turn * -1, depth + 1, maxdepth);
                        /* Maximize the evaluation, relative to whose turn it is */
                        if ((next_eval * turn) > (eval * turn)) {
                                eval = next_eval;
                                bestmove_i = i;
                                bestmove_j = j;
                        }
                        board->cells[i][j] = EMPTY;
                }
        }
        /* Record the best move, and return the evaluation */
        board->bestmove_i = bestmove_i;
        board->bestmove_j = bestmove_j;
        board->moves--;
        return eval;
}

void board_show(BoardBig *board) {
        for (int i = 0; i < board->height; i++) {
                for (int j = 0; j < board->width; j++) {
                        switch (board->cells[i][j]) {
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

#include <stdlib.h>
#include <stdio.h>

void solve(int, int[], int);
int  is_valid(int[], int);
void show_board(int[], int);

unsigned long int total = 0;

/* Solving the n-queens problem using backtracking */
void solve(int n, int board[], int k) {
        if (k == n) {
                if (n <= 8) {
                        show_board(board, n);
                }
                total += 1;
                return;
        }
        for (int i = 0; i < n; i++) {
                board[k] = i;
                if (is_valid(board, k)) {
                        solve(n, board, k + 1);
                }
        }
}

/* Check whether a board is valid, up to column k */
int is_valid(int board[], int k) {
        for (int i = 0; i < k; i++) {
                if (board[i] == board[k]
                    || (board[i] - board[k]) == (i - k)
                    || (board[i] - board[k]) == (k - i)) {
                        return 0;
                }
        }
        return 1;
}

/* Pretty print a board */
void show_board(int board[], int n) {
        for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                        if (j == board[i]) {
                                printf("Q ");
                        } else {
                                printf("- ");
                        }
                }
                printf("\n");
        }
        printf("\n");
}

int main(int argc, const char *argv[]) {
        int n = 8;
        if (argc > 1) {
                n = atoi(argv[1]);
        }
        int board[n];
        solve(n, board, 0);
        printf("Total solutions : %lu\n", total);
        return 0;
}

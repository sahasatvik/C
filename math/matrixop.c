#include <stdlib.h>
#include <stdio.h>
#include "Matrix.h"

double f(unsigned int i, unsigned int j) {
        return i * i + j;
}
double g(unsigned int i, unsigned int j) {
        return i + j * j;
}

int main(int argc, const char *argv[]) {
        Matrix *a = matrix_formula(2, 3, f);
        Matrix *b = matrix_formula(3, 4, g);

        printf("Matrix A :\n");
        matrix_show(a, "%5.1f ");
        printf("\nMatrix B :\n");
        matrix_show(b, "%5.1f ");
        
        Matrix *a_transpose = matrix_transpose(a);
        printf("\nMatrix A transpose:\n");
        matrix_show(a_transpose, "%5.1f ");
        matrix_free(a_transpose);
        
        Matrix *ab = matrix_mul(a, b);
        printf("\nMatrix AB :\n");
        matrix_show(ab, "%5.1f ");
        matrix_free(ab);

        Matrix *b_sub = matrix_submatrix(b, 0, 1, 2, 3);
        printf("\nMatrix B, submatrix from (0, 1) to (2, 3):\n");
        matrix_show(b_sub, "%5.1f ");
        matrix_free(b_sub);

        matrix_row_swap(a, 0, 1);
        printf("\nMatrix A after swapping rows 0, 1 in place:\n");
        matrix_show(a, "%5.1f ");

        matrix_row_scale(a, 0, 2);
        printf("\nMatrix A after doubling row 0 in place:\n");
        matrix_show(a, "%5.1f ");

        matrix_row_add_scaled(a, 0, 1, -4);
        printf("\nMatrix A after subtracting four times row 1 from row 0 in place:\n");
        matrix_show(a, "%5.1f ");

        matrix_free(a);
        matrix_free(b);
        
        return 0;
}

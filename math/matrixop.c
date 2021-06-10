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
        
        printf("\nMatrix A transpose:\n");
        matrix_show(matrix_transpose(a), "%5.1f ");
        
        printf("\nMatrix AB :\n");
        matrix_show(matrix_mul(a, b), "%5.1f ");

        printf("\nMatrix B, submatrix from (0, 1) to (2, 3):\n");
        matrix_show(matrix_submatrix(b, 0, 1, 2, 3), "%5.1f ");

        matrix_row_swap(a, 0, 1);
        printf("\nMatrix A after swapping rows 0, 1 in place:\n");
        matrix_show(a, "%5.1f ");
        
        matrix_row_scale(a, 0, 2);
        printf("\nMatrix A after doubling row 0 in place:\n");
        matrix_show(a, "%5.1f ");
        
        matrix_row_add_scaled(a, 0, 1, -4);
        printf("\nMatrix A after subtracting four times row 1 from row 0 in place:\n");
        matrix_show(a, "%5.1f ");

        free(a);
        free(b);
        
        return 0;
}

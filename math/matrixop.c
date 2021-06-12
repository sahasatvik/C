#include <stdlib.h>
#include <stdio.h>
#include "Matrix.h"

double f(int i, int j) {
        return i * i + j;
}
double g(int i, int j) {
        return i + j * j;
}
double square(double x, int i, int j) {
        return x * x;
}

int main(int argc, const char *argv[]) {
        Matrix *a = matrix_formula(2, 3, f);
        Matrix *b = matrix_formula(3, 4, g);

        printf("Matrix A :\n");
        matrix_show(a, "%5.1f ");
        printf("\nMatrix B :\n");
        matrix_show(b, "%5.1f ");
        
        printf("\nSum of elements in A : %5.1f\n", matrix_sum_elem(a));
        printf("Sum of elements in B : %5.1f\n", matrix_sum_elem(b));
        
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
        
        matrix_map(a, square);
        printf("\nMatrix A after squaring all elements in place:\n");
        matrix_show(a, "%5.1f ");

        matrix_free(a);
        matrix_free(b);
        
        return 0;
}

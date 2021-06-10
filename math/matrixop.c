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

        free(a);
        free(b);
        
        return 0;
}

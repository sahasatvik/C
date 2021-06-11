#include <stdlib.h>
#include <stdio.h>
#include "Matrix.h"

int main(int argc, const char *argv[]) {
        double elements[4][4] = {
                {0, 2, 3, 4},
                {5, 4, 3, 2},
                {6, 2, 9, 5},
                {1, 7, 8, 9}
        };
        Matrix *a = matrix_zeros(4, 4);
        for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                        a->data[i][j] = elements[i][j];
        printf("Matrix:\n");
        matrix_show(a, "%8.4f ");

        double det = matrix_det(a);
        printf("\nDeterminant: %f\n", det);

        Matrix *inv = matrix_inv(a);
        printf("\nInverse matrix:\n");
        matrix_show(inv, "%8.4f ");

        Matrix *idt = matrix_mul(a, inv);
        printf("\nCheck that the product with the inverse is the identity:\n");
        matrix_show(idt, "%8.4f ");

        matrix_free(a);
        matrix_free(inv);
        matrix_free(idt);
        
        return 0;
}

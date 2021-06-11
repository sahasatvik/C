#include <stdlib.h>
#include <stdio.h>
#include "Matrix.h"

int main(int argc, const char *argv[]) {
        double elements[4][4] = {
                {1, 2, 3, 4},
                {5, 4, 3, 2},
                {7, 8, 3, 5},
                {1, 7, 8, 9}
        };
        Matrix *a = matrix_zeros(4, 4);
        for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                        a->data[i][j] = elements[i][j];
        matrix_show(a, "%8.4f ");

        double det = matrix_det(a);
        printf("\nDeterminant : %f\n", det);

        matrix_free(a);
        
        return 0;
}

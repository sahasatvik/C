#include <stdlib.h>
#include <stdio.h>
#include "Matrix.h"

Matrix *matrix_zeros(unsigned int rows, unsigned int columns) {
        Matrix *m = (Matrix *) malloc(sizeof(Matrix));
        m->rows = rows;
        m->columns = columns;
        m->data = (double **) malloc(sizeof(double *) * rows);
        for (unsigned int i = 0; i < rows; i++)
                m->data[i] = (double *) malloc(sizeof(double) * columns);
        return m;
}

Matrix *matrix_formula(unsigned int rows, unsigned int columns, double (*f)(unsigned int, unsigned int)) {
        Matrix *m = matrix_zeros(rows, columns);
        for (unsigned int i = 0; i < rows; i++)
                for (unsigned int j = 0; j < columns; j++)
                        m->data[i][j] = f(i, j);
        return m;
}

Matrix *matrix_transpose(Matrix *m) {
        Matrix *mt = matrix_zeros(m->columns, m->rows);
        for (unsigned int i = 0; i < mt->rows; i++)
                for (unsigned int j = 0; j < mt->columns; j++)
                        mt->data[i][j] = m->data[j][i];
        return mt;
}

Matrix *matrix_mul(Matrix *a, Matrix *b) {
        if (a->columns != b->rows) {
                return matrix_zeros(0, 0);
        }
        Matrix *c = matrix_zeros(a->rows, b->columns);
        for (unsigned int i = 0; i < c->rows; i++) {
                for (unsigned int j = 0; j < c->columns; j++) {
                        c->data[i][j] = 0;
                        for (unsigned int k = 0; k < a->columns; k++) {
                                c->data[i][j] += a->data[i][k] * b->data[k][j];
                        }
                }
        }
        return c;
}

void matrix_show(Matrix *m, char *format) {
        for (unsigned int i = 0; i < m->rows; i++) {
                for (unsigned int j = 0; j < m->columns; j++) {
                        printf(format, m->data[i][j]);
                }
                printf("\n");
        }
}

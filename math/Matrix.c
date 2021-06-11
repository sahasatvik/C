#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Matrix.h"

Matrix *matrix_zeros(unsigned int rows, unsigned int columns) {
        Matrix *m = malloc(sizeof(Matrix));
        m->rows = rows;
        m->columns = columns;
        m->data = calloc(rows, sizeof(double *));
        for (unsigned int i = 0; i < rows; i++)
                m->data[i] = calloc(columns, sizeof(double));
        return m;
}

Matrix *matrix_formula(unsigned int rows, unsigned int columns, double (*f)(unsigned int, unsigned int)) {
        Matrix *m = matrix_zeros(rows, columns);
        for (unsigned int i = 0; i < rows; i++)
                for (unsigned int j = 0; j < columns; j++)
                        m->data[i][j] = f(i, j);
        return m;
}

Matrix *matrix_identity(unsigned int n) {
        Matrix *m = matrix_zeros(n, n);
        for (unsigned int i = 0; i < m->rows; i++)
                m->data[i][i] = 1;
        return m;
}

void matrix_free(Matrix *m) {
        for (unsigned int i = 0; i < m->rows; i++)
                free(m->data[i]);
        free(m->data);
        free(m);
}

Matrix *matrix_transpose(Matrix *m) {
        Matrix *mt = matrix_zeros(m->columns, m->rows);
        for (unsigned int i = 0; i < mt->rows; i++)
                for (unsigned int j = 0; j < mt->columns; j++)
                        mt->data[i][j] = m->data[j][i];
        return mt;
}

Matrix *matrix_mul(Matrix *a, Matrix *b) {
        if (a->columns != b->rows)
                return NULL;
        Matrix *c = matrix_zeros(a->rows, b->columns);
        for (unsigned int i = 0; i < c->rows; i++) {
                for (unsigned int j = 0; j < c->columns; j++) {
                        /* The entry c[i, j] is the dot product of the ith row of a, and the jth column of b. */
                        c->data[i][j] = 0;
                        for (unsigned int k = 0; k < a->columns; k++) {
                                c->data[i][j] += a->data[i][k] * b->data[k][j];
                        }
                }
        }
        return c;
}

Matrix *matrix_copy(Matrix *m) {
        Matrix *mc = matrix_zeros(m->rows, m->columns);
        for (unsigned int i = 0; i < mc->rows; i++)
                for (unsigned int j = 0; j < mc->columns; j++)
                        mc->data[i][j] = m->data[i][j];
        return mc;
}

Matrix *matrix_submatrix(Matrix *m, unsigned int i0, unsigned int j0, unsigned int i1, unsigned int j1) {
        if (i0 < 0 || j0 < 0 || i0 >= m->rows || j0 >= m->columns)
                return NULL;
        if (i1 < 1 || j1 < 1 || i1 >= m->rows || j1 >= m->columns)
                return NULL;
        if (i1 <= i0 || j1 <= j0)
                return NULL;
        Matrix *mc = matrix_zeros(i1 - i0, j1 - j0);
        for (unsigned int i = i0; i < i1; i++)
                for (unsigned int j = j0; j < j1; j++)
                        mc->data[i - i0][j - j0] = m->data[i][j];
        return mc;
}

void matrix_sum(Matrix *a, Matrix *b) {
        if (a->rows != b->rows || a->columns != b->columns)
                return;
        for (unsigned int i = 0; i < a->rows; i++) {
                for (unsigned int j = 0; j < a->columns; j++) {
                        a->data[i][j] += b->data[i][j];
                }
        }
}

double matrix_sum_elem(Matrix *m) {
        double sum = 0.0;
        for (unsigned int i = 0; i < m->rows; i++)
                for (unsigned int j = 0; j < m->columns; j++)
                        sum += m->data[i][j];
        return sum;
}

void matrix_row_swap(Matrix *m, unsigned int x, unsigned int y) {
        if (x < 0 || y < 0 || x >= m->rows || y >= m->rows)
                return;
        double *temp = m->data[x];
        m->data[x] = m->data[y];
        m->data[y] = temp;
}

void matrix_row_scale(Matrix *m, unsigned int x, double c) {
        if (x < 0 || x >= m->rows)
                return;
        for (unsigned int j = 0; j < m->columns; j++)
                m->data[x][j] *= c;
}

void matrix_row_add_scaled(Matrix *m, unsigned int x, unsigned int y, double c) {
        if (x < 0 || y < 0 || x >= m->rows || y >= m->rows)
                return;
        for (unsigned int j = 0; j < m->columns; j++)
                m->data[x][j] += c * m->data[y][j];
}

void matrix_scale(Matrix *m, double c) {
        for (unsigned int i = 0; i < m->rows; i++)
                for (unsigned int j = 0; j < m->columns; j++)
                        m->data[i][j] *= c;
}

void matrix_map(Matrix *m, double (*f)(double, unsigned int, unsigned int)) {
        for (unsigned int i = 0; i < m->rows; i++)
                for (unsigned int j = 0; j < m->columns; j++)
                        m->data[i][j] = f(m->data[i][j], i, j);
}

double matrix_det(Matrix *m) {
        /* Ensure that the matrix is square */
        if (m->rows != m->columns)
                return 0.0;
        Matrix *mc = matrix_copy(m);
        double det = 1.0;
        for (unsigned int i = 0; i < mc->rows; i++) {
                unsigned int k = i;
                /* Skip ahead until the m[k, i] entry is non-zero */
                for (; k < mc->rows && fabs(mc->data[k][i]) < MATRIX_EPSILON; k++);
                /* All m[k, i] are zero, which means that the matrix is singular */
                if (k >= mc->rows)
                        return 0.0;
                /* Swap the non-zero row into place */
                matrix_row_swap(mc, i, k);
                /* Scale the determinant up, and scale the leading element m[i, i] in the row down to one.
                   If there was a swap, the determinant also changes sign */
                det *= mc->data[i][i] * ((i == k)? 1.0 : -1.0);
                matrix_row_scale(mc, i, 1.0 / mc->data[i][i]);
                /* Eliminate all m[k, i] entries in the rows below */
                for (k = i + 1; k < mc->rows; k++)
                        matrix_row_add_scaled(mc, k, i, -mc->data[k][i]);
        }
        return det;
}

Matrix *matrix_inv(Matrix *m) {
        /* Ensure that the matrix is square */
        if (m->rows != m->columns)
                return NULL;
        /* Perform elimination on a copy of m as well as on an identity matrix */
        Matrix *mc = matrix_copy(m);
        Matrix *inv = matrix_identity(m->rows);
        for (unsigned int i = 0; i < mc->rows; i++) {
                unsigned int k = i;
                for (; k < mc->rows && fabs(mc->data[k][i]) < MATRIX_EPSILON; k++);
                if (k >= mc->rows)
                        return NULL;
                matrix_row_swap(inv, i, k);
                matrix_row_swap(mc, i, k);
                matrix_row_scale(inv, i, 1.0 / mc->data[i][i]);
                matrix_row_scale(mc, i, 1.0 / mc->data[i][i]);
                for (k = i + 1; k < mc->rows; k++) {
                        matrix_row_add_scaled(inv, k, i, -mc->data[k][i]);
                        matrix_row_add_scaled(mc, k, i, -mc->data[k][i]);
                }
        }
        /* The original matrix is now upper triangular, with 1's on the diagonal.
           Perform back-substitution to transform it into an identity matrix */
        for (unsigned int i = m->rows - 1; i > 0; i--)
                for (unsigned int k = 0; k < i; k++)
                        matrix_row_add_scaled(inv, k, i, -mc->data[k][i]);
        return inv;
}

void matrix_show(Matrix *m, char *format) {
        for (unsigned int i = 0; i < m->rows; i++) {
                for (unsigned int j = 0; j < m->columns; j++) {
                        printf(format, m->data[i][j]);
                }
                printf("\n");
        }
}

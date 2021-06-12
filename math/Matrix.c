#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Matrix.h"

Matrix *matrix_zeros(int rows, int columns) {
        if (rows <= 0 || columns <= 0)
                return NULL;
        Matrix *m = malloc(sizeof(Matrix));
        m->rows = rows;
        m->columns = columns;
        m->data = calloc(rows, sizeof(double *));
        for (int i = 0; i < rows; i++)
                m->data[i] = calloc(columns, sizeof(double));
        return m;
}

Matrix *matrix_formula(int rows, int columns, double (*f)(int, int)) {
        Matrix *m = matrix_zeros(rows, columns);
        for (int i = 0; i < rows; i++)
                for (int j = 0; j < columns; j++)
                        m->data[i][j] = f(i, j);
        return m;
}

Matrix *matrix_identity(int n) {
        Matrix *m = matrix_zeros(n, n);
        for (int i = 0; i < m->rows; i++)
                m->data[i][i] = 1;
        return m;
}

void matrix_free(Matrix *m) {
        if (m == NULL)
                return;
        for (int i = 0; i < m->rows; i++)
                free(m->data[i]);
        free(m->data);
        free(m);
}

Matrix *matrix_transpose(Matrix *m) {
        if (m == NULL)
                return NULL;
        Matrix *mt = matrix_zeros(m->columns, m->rows);
        for (int i = 0; i < mt->rows; i++)
                for (int j = 0; j < mt->columns; j++)
                        mt->data[i][j] = m->data[j][i];
        return mt;
}

Matrix *matrix_mul(Matrix *a, Matrix *b) {
        if (a == NULL || b == NULL)
                return NULL;
        if (a->columns != b->rows)
                return NULL;
        Matrix *c = matrix_zeros(a->rows, b->columns);
        for (int i = 0; i < c->rows; i++) {
                for (int j = 0; j < c->columns; j++) {
                        /* The entry c[i, j] is the dot product of the ith row of a, and the jth column of b. */
                        c->data[i][j] = 0;
                        for (int k = 0; k < a->columns; k++) {
                                c->data[i][j] += a->data[i][k] * b->data[k][j];
                        }
                }
        }
        return c;
}

Matrix *matrix_copy(Matrix *m) {
        if (m == NULL)
                return NULL;
        Matrix *mc = matrix_zeros(m->rows, m->columns);
        for (int i = 0; i < mc->rows; i++)
                for (int j = 0; j < mc->columns; j++)
                        mc->data[i][j] = m->data[i][j];
        return mc;
}

Matrix *matrix_submatrix(Matrix *m, int i0, int j0, int i1, int j1) {
        if (m == NULL)
                return NULL;
        if (i0 < 0 || j0 < 0 || i0 >= m->rows || j0 >= m->columns)
                return NULL;
        if (i1 < 1 || j1 < 1 || i1 >= m->rows || j1 >= m->columns)
                return NULL;
        if (i1 <= i0 || j1 <= j0)
                return NULL;
        Matrix *mc = matrix_zeros(i1 - i0, j1 - j0);
        for (int i = i0; i < i1; i++)
                for (int j = j0; j < j1; j++)
                        mc->data[i - i0][j - j0] = m->data[i][j];
        return mc;
}

void matrix_sum(Matrix *a, Matrix *b) {
        if (a == NULL || b == NULL)
                return;
        if (a->rows != b->rows || a->columns != b->columns)
                return;
        for (int i = 0; i < a->rows; i++) {
                for (int j = 0; j < a->columns; j++) {
                        a->data[i][j] += b->data[i][j];
                }
        }
}

double matrix_sum_elem(Matrix *m) {
        if (m == NULL)
                return 0.0;
        double sum = 0.0;
        for (int i = 0; i < m->rows; i++)
                for (int j = 0; j < m->columns; j++)
                        sum += m->data[i][j];
        return sum;
}

void matrix_row_swap(Matrix *m, int x, int y) {
        if (m == NULL)
                return;
        if (x < 0 || y < 0 || x >= m->rows || y >= m->rows)
                return;
        double *temp = m->data[x];
        m->data[x] = m->data[y];
        m->data[y] = temp;
}

void matrix_row_scale(Matrix *m, int x, double c) {
        if (m == NULL)
                return;
        if (x < 0 || x >= m->rows)
                return;
        for (int j = 0; j < m->columns; j++)
                m->data[x][j] *= c;
}

void matrix_row_add_scaled(Matrix *m, int x, int y, double c) {
        if (m == NULL)
                return;
        if (x < 0 || y < 0 || x >= m->rows || y >= m->rows)
                return;
        for (int j = 0; j < m->columns; j++)
                m->data[x][j] += c * m->data[y][j];
}

void matrix_scale(Matrix *m, double c) {
        if (m == NULL)
                return;
        for (int i = 0; i < m->rows; i++)
                for (int j = 0; j < m->columns; j++)
                        m->data[i][j] *= c;
}

void matrix_map(Matrix *m, double (*f)(double, int, int)) {
        if (m == NULL)
                return;
        for (int i = 0; i < m->rows; i++)
                for (int j = 0; j < m->columns; j++)
                        m->data[i][j] = f(m->data[i][j], i, j);
}

double matrix_det(Matrix *m) {
        if (m == NULL)
                return 0.0;
        /* Ensure that the matrix is square */
        if (m->rows != m->columns)
                return 0.0;
        Matrix *mc = matrix_copy(m);
        double det = 1.0;
        for (int i = 0; i < mc->rows; i++) {
                int k = i;
                /* Skip ahead until the m[k, i] entry is non-zero */
                for (; k < mc->rows && fabs(mc->data[k][i]) < MATRIX_EPSILON; k++);
                /* All m[k, i] are zero, which means that the matrix is singular */
                if (k >= mc->rows) {
                        matrix_free(mc);
                        return 0.0;
                }
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
        matrix_free(mc);
        return det;
}

int matrix_elim_aug(Matrix *m, Matrix *aug) {
        if (m == NULL || aug == NULL)
                return 0;
        /* Ensure that the matrix is square, and that the matrix to be augmented has the same number of rows */
        if (m->rows != m->columns || m->rows != aug->rows)
                return 0;
        /* Perform elimination on m, and perform the same operations on aug */
        for (int i = 0; i < m->rows; i++) {
                int k = i;
                for (; k < m->rows && fabs(m->data[k][i]) < MATRIX_EPSILON; k++);
                if (k >= m->rows)
                        return 0;
                matrix_row_swap(aug, i, k);
                matrix_row_swap(m, i, k);
                matrix_row_scale(aug, i, 1.0 / m->data[i][i]);
                matrix_row_scale(m, i, 1.0 / m->data[i][i]);
                for (k = i + 1; k < m->rows; k++) {
                        matrix_row_add_scaled(aug, k, i, -m->data[k][i]);
                        matrix_row_add_scaled(m, k, i, -m->data[k][i]);
                }
        }
        /* The original matrix is now upper triangular, with 1's on the diagonal.
           Perform back-substitution to transform it into an identity matrix */
        for (int i = m->rows - 1; i > 0; i--) {
                for (int k = 0; k < i; k++) {
                        matrix_row_add_scaled(aug, k, i, -m->data[k][i]);
                        matrix_row_add_scaled(m, k, i, -m->data[k][i]);
                }
        }
        return 1;
}

Matrix *matrix_inv(Matrix *m) {
        if (m == NULL)
                return NULL;
        /* Finding the inverse is the same as performing elimination on m augmented
           with an identity matrix */
        Matrix *mc = matrix_copy(m);
        Matrix *idt = matrix_identity(m->rows);
        int singular = !matrix_elim_aug(mc, idt);
        matrix_free(mc);
        if (singular)
                return NULL;
        return idt;
}

void matrix_show(Matrix *m, char *format) {
        if (m == NULL) {
                printf("NULL\n");
                return;
        }
        for (int i = 0; i < m->rows; i++) {
                for (int j = 0; j < m->columns; j++) {
                        printf(format, m->data[i][j]);
                }
                printf("\n");
        }
}

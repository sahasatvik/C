#ifndef _MATRIX_H
#define _MATRIX_H

/* A 2D matrix of doubles */
typedef struct {
        unsigned int rows;
        unsigned int columns;
        double **data;
} Matrix;

/* Create a matrix of given size filled with zeros */
Matrix *matrix_zeros(unsigned int, unsigned int);
/* Create a matrix of given size with the (i, j)th entry filled as f(i, j) */
Matrix *matrix_formula(unsigned int, unsigned int, double (*)(unsigned int, unsigned int));

/* Free the memory used by a matrix */
void matrix_free(Matrix *);

/* Get a copy of a matrix */
Matrix *matrix_copy(Matrix *);
/* Get a submatrix of a matrix */
Matrix *matrix_submatrix(Matrix *, unsigned int, unsigned int, unsigned int, unsigned int);
/* Get the transpose of a matrix */
Matrix *matrix_transpose(Matrix *);
/* Get the product of two matrices */
Matrix *matrix_mul(Matrix *, Matrix *);

/* Swap two rows */
void matrix_row_swap(Matrix *, unsigned int, unsigned int);
/* Scale a row */
void matrix_row_scale(Matrix *, unsigned int, double);
/* Add a scaled copy of another row */
void matrix_row_add_scaled(Matrix *, unsigned int, unsigned int, double);

/* Display the elements of a matrix */
void matrix_show(Matrix *, char *);

#endif

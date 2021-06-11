#ifndef _MATRIX_H
#define _MATRIX_H

#define MATRIX_EPSILON 1e-12

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
/* Create an identity square matrix of given size */
Matrix *matrix_identity(unsigned int);

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

/* Calculate the sum of two matrices, store in the first */
void matrix_sum(Matrix *, Matrix *);

/* Get the sum of all elements in a matrix */
double matrix_sum_elem(Matrix *);

/* Swap two rows in place */
void matrix_row_swap(Matrix *, unsigned int, unsigned int);
/* Scale a row in place */
void matrix_row_scale(Matrix *, unsigned int, double);
/* Add a scaled copy of another row in place */
void matrix_row_add_scaled(Matrix *, unsigned int, unsigned int, double);
/* Scale all elements of a matrix in place */
void matrix_scale(Matrix *, double);
/* Map all elements of a matrix in place */
void matrix_map(Matrix *, double (*)(double, unsigned int, unsigned int));

/* Get the determinant of a square matrix */
double matrix_det(Matrix *);

/* Display the elements of a matrix */
void matrix_show(Matrix *, char *);

#endif

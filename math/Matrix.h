#ifndef _MATRIX_H
#define _MATRIX_H

#define MATRIX_EPSILON 1e-12

/* A 2D matrix of doubles */
typedef struct {
        int rows;
        int columns;
        double **data;
} Matrix;

/* Create a matrix of given size filled with zeros */
Matrix *matrix_zeros(int, int);
/* Create a matrix of given size with the (i, j)th entry filled as f(i, j) */
Matrix *matrix_formula(int, int, double (*)(int, int));
/* Create an identity square matrix of given size */
Matrix *matrix_identity(int);

/* Free the memory used by a matrix */
void matrix_free(Matrix *);

/* Get a copy of a matrix */
Matrix *matrix_copy(Matrix *);
/* Get a submatrix of a matrix */
Matrix *matrix_submatrix(Matrix *, int, int, int, int);
/* Get the transpose of a matrix */
Matrix *matrix_transpose(Matrix *);
/* Get the product of two matrices */
Matrix *matrix_mul(Matrix *, Matrix *);

/* Calculate the sum of two matrices, store in the first */
void matrix_sum(Matrix *, Matrix *);

/* Get the sum of all elements in a matrix */
double matrix_sum_elem(Matrix *);

/* Swap two rows in place */
void matrix_row_swap(Matrix *, int, int);
/* Scale a row in place */
void matrix_row_scale(Matrix *, int, double);
/* Add a scaled copy of another row in place */
void matrix_row_add_scaled(Matrix *, int, int, double);
/* Scale all elements of a matrix in place */
void matrix_scale(Matrix *, double);
/* Map all elements of a matrix in place */
void matrix_map(Matrix *, double (*)(double, int, int));

/* Get the determinant of a square matrix */
double matrix_det(Matrix *);
/* Perform Gauss Jordan elimination in place on a square matrix, augmented with a secondary matrix
   with the same number of rows. Return 0 if the first matrix is singular, or not square, or the two
   matrices have a different number of rows. */
int matrix_elim_aug(Matrix *, Matrix *);
/* Get the inverse of a square matrix */
Matrix *matrix_inv(Matrix *);

/* Display the elements of a matrix */
void matrix_show(Matrix *, const char *);

#endif

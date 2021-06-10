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

/* Take the transpose of a matrix */
Matrix *matrix_transpose(Matrix *);

/* Multiply two matrices */
Matrix *matrix_mul(Matrix *, Matrix *);

/* Display the elements of a matrix */
void matrix_show(Matrix *, char *);

#endif

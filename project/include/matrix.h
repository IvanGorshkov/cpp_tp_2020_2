//
//  matrix.h
//  DZ1
//
//  Created by Ivan Gorshkov on 02.10.2020.
//

#ifndef PROJECT_INCLUDE_MATRIX_H_
#define PROJECT_INCLUDE_MATRIX_H_

#include <stdio.h>


typedef struct Matrix {
    size_t rows;
    size_t cols;
    double *matrix;
} Matrix;


Matrix* create_empty_matrix(size_t rows, size_t cols);
Matrix* generate_adjacency(double *old_matrix, size_t array_rows, size_t array_cols);
int print_matrix(Matrix *matrix);
int free_matrix(Matrix* matrix);

#endif  // PROJECT_INCLUDE_MATRIX_H_

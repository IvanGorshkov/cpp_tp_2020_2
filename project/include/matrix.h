//
//  matrix.h
//  DZ1
//
//  Created by Ivan Gorshkov on 02.10.2020.
//

#ifndef PROJECT_INCLUDE_MATRIX_H_
#define PROJECT_INCLUDE_MATRIX_H_

#include <stdio.h>


typedef struct matrix {
    size_t rows;
    size_t cols;
    double *matrix;
} matrix;


matrix* create_empty_matrix(size_t rows, size_t cols);
matrix* generate_adjacency(double *old_matrix, size_t array_rows, size_t array_cols);
int print_matrix(matrix *matrix);
int free_matrix(matrix* matrix);

#endif  // PROJECT_INCLUDE_MATRIX_H_

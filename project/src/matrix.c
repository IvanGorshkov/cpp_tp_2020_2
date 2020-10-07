//
//  matrix.c
//  DZ1
//
//  Created by Ivan Gorshkov on 02.10.2020.
//

#include <malloc/_malloc.h>
#include <stdio.h>
#include "matrix.h"
#include <stdlib.h>

Matrix* create_empty_matrix(size_t rows, size_t cols) {
    if (rows == 0 || cols == 0) {
        return NULL;
    }

    Matrix *matrix = calloc(1, sizeof(Matrix));

    if (matrix == NULL) {
        return NULL;
    }

    matrix->rows = rows;
    matrix->cols = cols;
    matrix->matrix = calloc(rows * cols, sizeof(double));

    if (matrix->matrix == NULL) {
        free_matrix(matrix);
        return NULL;
    }

    return matrix;
}

Matrix* generate_adjacency(double *old_matrix, size_t array_rows, size_t array_cols) {
    Matrix *new_matrix = create_empty_matrix(array_rows, array_cols);
    if (new_matrix == NULL) {
        return NULL;
    }

    for (size_t rows = 0; rows < array_rows; ++rows) {
        double sum = 0;
        int middle = 0;
        for (size_t cols = 0; cols < array_cols; ++cols) {
            if (cols < (array_cols - 1) && cols > 0) {
                sum += old_matrix[new_matrix->rows * (cols + 1) + rows];
                sum += old_matrix[new_matrix->rows * (cols - 1) + rows];
                middle += 2;
            }

            if (rows < (array_rows- 1) && rows > 0) {
                sum += old_matrix[new_matrix->rows * cols + (rows - 1)];
                sum += old_matrix[new_matrix->rows * cols + (rows + 1)];
                middle += 2;
            }

            if (rows == 0 && array_rows != 1) {
                sum += old_matrix[new_matrix->rows * cols + (rows + 1)];
                ++middle;
            }

            if (rows == (array_rows - 1) && rows != 0) {
                sum += old_matrix[new_matrix->rows * cols + (rows - 1)];
                ++middle;
            }

            if (cols == 0 && array_cols != 1) {
                sum += old_matrix[new_matrix->rows * (cols + 1) + rows];
                ++middle;
            }

            if (cols == (array_cols - 1) && cols != 0) {
                sum += old_matrix[new_matrix->rows * (cols - 1) + rows];
                ++middle;
            }

            if (cols != (array_cols - 1) && rows != (array_rows - 1)) {
                sum += old_matrix[new_matrix->rows * (cols + 1) + (rows + 1)];
                ++middle;
            }

            if (cols != 0 && rows != 0) {
                sum += old_matrix[new_matrix->rows * (cols - 1) + (rows - 1)];
                ++middle;
            }

            if (rows != 0 && cols != (array_cols - 1)) {
                sum += old_matrix[new_matrix->rows * (cols + 1) + (rows - 1)];
                ++middle;
            }

            if (rows != (array_rows - 1) && cols != 0) {
                sum += old_matrix[new_matrix->rows * (cols - 1) + (rows + 1)];
                ++middle;
            }

            new_matrix->matrix[new_matrix->rows * cols + rows] = sum / middle;
            sum = 0;
            middle = 0;
        }
    }

    return new_matrix;
}

int print_matrix(Matrix *matrix) {
    if (matrix == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t rows = 0; rows < matrix->rows; ++rows) {
        for (size_t cols = 0; cols < matrix->cols; ++cols) {
            printf("%f ", matrix->matrix[matrix->cols * rows + cols]);
        }
        printf("\n");
    }

    return EXIT_SUCCESS;
}

int free_matrix(Matrix *matrix) {
    if (matrix == NULL) {
        return EXIT_FAILURE;
    }

    if (matrix->matrix == NULL) {
        free(matrix);
        return EXIT_FAILURE;
    }

    free(matrix->matrix);
    free(matrix);

    return EXIT_SUCCESS;
}

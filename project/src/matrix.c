//
//  matrix.c
//  DZ1
//
//  Created by Ivan Gorshkov on 02.10.2020.
//

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

matrix* create_empty_matrix(size_t rows, size_t cols) {
    if (rows == 0 || cols == 0) {
        return NULL;
    }

    matrix *matrix = calloc(1, sizeof(matrix));

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

matrix* generate_adjacency(double *old_matrix, size_t array_rows, size_t array_cols) {
  matrix *new_matrix = create_empty_matrix(array_rows, array_cols);
  if (new_matrix == NULL) {
    return NULL;
  }
  int dir[][8] = {
      {1, 0},  {1, 1}, {0, 1}, {-1, 1},
      {-1, 0}, {-1, -1}, {0, -1}, {1, -1}
  };
  for (size_t rows = 0; rows < array_rows; ++rows) {
    double sum = 0;
    int middle = 0;

    for (size_t cols = 0; cols < array_cols; ++cols) {
      for (int dir_k = 0; dir_k < 8; ++dir_k) {
        size_t y  = cols + dir[dir_k][0];
        size_t x  = rows + dir[dir_k][1];
        if (x < 0 || x > array_rows - 1 || y < 0 || y > array_cols - 1) {
          continue;
        }
        int xas = old_matrix[new_matrix->rows * y + x];
          if (xas != 0) {

          }
        sum += old_matrix[new_matrix->rows * y + x];
        ++middle;
      }

      new_matrix->matrix[new_matrix->rows * cols + rows] = sum / middle;
      sum = 0;
      middle = 0;
    }
  }

  return new_matrix;
}

int print_matrix(matrix *matrix) {
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

int free_matrix(matrix *matrix) {
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

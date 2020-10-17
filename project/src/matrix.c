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

    matrix *new_matrix = calloc(1, sizeof(matrix));

    if (new_matrix == NULL) {
        return NULL;
    }

  new_matrix->rows = rows;
  new_matrix->cols = cols;
  new_matrix->matrix = calloc(rows * cols, sizeof(double));

    if (new_matrix->matrix == NULL) {
        free_matrix(new_matrix);
        return NULL;
    }

    return new_matrix;
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
    for (size_t cols = 0; cols < array_cols; ++cols) {
      double sum = 0;
      int middle = 0;
      for (int dir_k = 0; dir_k < 8; ++dir_k) {
        size_t y  = cols + dir[dir_k][0];
        size_t x  = rows + dir[dir_k][1];
        if (x < 0 || x >= array_rows || y < 0 || y >= array_cols)
          continue;
        sum += old_matrix[new_matrix->rows * y + x];
        ++middle;
      }
      new_matrix->matrix[new_matrix->rows * cols + rows] = sum / middle;
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

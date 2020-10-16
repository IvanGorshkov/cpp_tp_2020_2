//
// Created by Ivan Gorshkov on 08.10.2020.
//

#include <math.h>
#include "gtest/gtest.h"

extern "C" {
  #include "matrix.h"
}

TEST(MatrixTest, IsPrint) {
  double listArray[9] = {1,2,3,4,5,6,7,8,9};
  matrix *matrix = generate_adjacency(listArray, 3, 3);
  ASSERT_EQ(print_matrix(matrix), 0);
  free_matrix(matrix);
}

TEST(MatrixTest, Free) {
  double listArray[9] = {1,2,3,4,5,6,7,8,9};
  matrix *matrix = generate_adjacency(listArray, 3, 3);
  ASSERT_EQ(free_matrix(matrix), 0);
}

TEST(MatrixTest, MatrixNineValues) {
  double listArray[9] = {1,2,3,4,5,6,7,8,9};
  double expected[9] = {3.666667, 3.800000, 4.333333, 4.600000, 5.000000, 5.400000, 5.666667, 6.200000, 6.333333};
  matrix *matrix = generate_adjacency(listArray, 3, 3);
  for (int kI = 0; kI < 9; ++kI) {
    ASSERT_DOUBLE_EQ(floor(expected[kI]*10000 )/10000, floor( matrix->matrix[kI]*10000 )/10000);
  }
  free_matrix(matrix);
}

TEST(MatrixTest, MatrixFourValues) {
  double listArray[4] = {1,1,1,1};
  double expected[4] = {1,1,1,1};
  matrix *matrix = generate_adjacency(listArray, 2, 2);
  for (int kI = 0; kI < 4; ++kI) {
    ASSERT_DOUBLE_EQ(expected[kI], matrix->matrix[kI]);
  }
  free_matrix(matrix);
}

TEST(MatrixTest, MatrixTwoValues) {
  double listArray[2] = {2,2};
  double expected[2] = {2,2};
  matrix *matrix = generate_adjacency(listArray, 1, 2);
  for (int kI = 0; kI < 2; ++kI) {
    ASSERT_DOUBLE_EQ(expected[kI], matrix->matrix[kI]);
  }
  free_matrix(matrix);
}
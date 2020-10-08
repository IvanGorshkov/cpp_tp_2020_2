//
// Created by Ivan Gorshkov on 08.10.2020.
//

#include "gtest/gtest.h"

extern "C" {
  #include "utils.h"
}

TEST(UtilesTest, BaseValue) {
  double* array = NULL;
  int correct = convert_str_to_arr("1 2 3 4 5 6 7 8 9", 9, &array);
  ASSERT_EQ(correct, 0);
  double res[9] = {1,2,3,4,5,6,7,8,9};
  for (int elem = 0; elem < 9; ++elem) {
    ASSERT_EQ(array[elem], res[elem]);
  }
  free(array);
}

TEST(UtilesTest, StringValue) {
  double* array = NULL;
  int correct = convert_str_to_arr("q w e r t y u i 3", 9, &array);
  ASSERT_EQ(correct, 1);
  free(array);
}

TEST(UtilesTest, EmptyCols) {
  double* array = NULL;
  int correct = check_empty_value("1 2 3 4 5 6 7 8 9",3,0);
  ASSERT_EQ(correct, 1);
}

TEST(UtilesTest, EmptyRows) {
  double* array = NULL;
  int correct = check_empty_value("1 2 3 4 5 6 7 8 9",0,2);
  ASSERT_EQ(correct, 1);
}

TEST(UtilesTest, EmptyStr) {
  double* array = NULL;
  int correct = check_empty_value("",2,2);
  ASSERT_EQ(correct, 1);
}

TEST(UtilesTest, AllEmptyValue) {
  double* array = NULL;
  int correct = check_empty_value("",0,0);
  ASSERT_EQ(correct, 1);
}

TEST(UtilesTest, NegativeSize) {
  double* array = NULL;
  int correct = convert_str_to_arr("1 2 3 4 5 6 7 8 9", -1, &array);
  ASSERT_EQ(correct, 1);
}

TEST(UtilesTest, LessSizeThenArray) {
  double* array = NULL;
  int correct = convert_str_to_arr("1 2 3 4 5 6 7 8 9", 3, &array);
  ASSERT_EQ(correct, 1);
}

TEST(UtilesTest, BiggerSizeThenArray) {
  double* array = NULL;
  int correct = convert_str_to_arr("1 2 3 4 5 6 7 8 9", 23, &array);
  ASSERT_EQ(correct, 1);
}

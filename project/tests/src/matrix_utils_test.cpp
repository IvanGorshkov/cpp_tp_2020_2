//
//  matrix_utils.cpp
//  DZ1
//
//  Created by Ivan Gorshkov on 08.10.2020.
//

#include "matrix_utils.hpp"
#include <gtest/gtest.h>
#include "utils.h"

TEST(MatrixOperationsTest, Det) {
    std::ifstream in((matrixDataPath / fs::path("in")).c_str());
    size_t row = 0;
    size_t col = 0;
    std::cin >> size;
    char str[1024] = {0};
    std::cin >> str;
    double* array = NULL;
    convert_str_to_arr(str, row * col, array);
    Matrix* mat = generate_adjacency(array, row, col);
    in.close();
    std::ifstream out((matrixDataPath / fs::path("out")).c_str());
    std::string out = f.rdbuf();
    ASSERT_EQ(print_matrix(mat), std::cout << out);
}

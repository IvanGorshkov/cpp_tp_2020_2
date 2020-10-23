//
// Created by Ivan Gorshkov on 21.10.2020.
//

#include "utils.h"
#include <string>
extern "C" {
  #include "libstat.h"
}


TEST(StaticLib, GetLineSizeFromFileStat) {
  for (int kI = 0; kI < number_of_files; ++kI) {
    std::cout << glob_test_dir << std::endl;
    std::string path = glob_test_dir;
    path += "/out_" + std::to_string(kI + 1) + ".txt";
    std::ifstream is(path);
    int expected = 0;
    is >> expected;
    is.close();
    path = glob_test_dir;
    path += "/in_" + std::to_string(kI + 1) + ".txt";
    std::cout << path << std::endl;
    ASSERT_EQ(expected, sequential_get_size_of_lines(path.c_str()));
  }
}

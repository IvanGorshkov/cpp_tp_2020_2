#include "test_utils.h"
#include <string>
extern "C" {
  #include "parallel_alg.h"
}

TEST(Parallel, GetLineSizeFromFileParallel) {
  for (int kI = 0; kI < number_of_files; ++kI) {
    std::string path = glob_test_dir;
    path += "/out_" + std::to_string(kI + 1) + ".txt";
    std::ifstream is(path);
    int expected = 0;
    is >> expected;
    is.close();
    path = glob_test_dir;
    path += "/in_" + std::to_string(kI + 1) + ".txt";
    ASSERT_EQ(expected, parallel_get_size_of_lines(path.c_str()));
  }
}

TEST(Parallel, WrongPath) {
  std::string path = glob_test_dir;
  path += "/in_wrong.txt";
  ASSERT_EQ(-1, parallel_get_size_of_lines(path.c_str()));
}
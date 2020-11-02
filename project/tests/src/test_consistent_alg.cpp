#include "test_utils.h"
extern "C" {
  #include "consistent_alg.h"
}

TEST(Consistent, GetLineSizeFromFileConsistent) {
  for (int kI = 0; kI < number_of_files; ++kI) {
    std::string path = glob_test_dir;
    path += "/out_" + std::to_string(kI + 1) + ".txt";
    std::ifstream is(path);
    int expected = 0;
    is >> expected;
    is.close();
    path = glob_test_dir;
    path += "/in_" + std::to_string(kI + 1) + ".txt";
    ASSERT_EQ(expected, sequential_get_size_of_lines(path.c_str()));
  }
}

TEST(Consistent, WrongPath) {
    std::string path = glob_test_dir;
    path += "/in_wrong.txt";
    ASSERT_EQ(-1, sequential_get_size_of_lines(path.c_str()));
}

TEST(Consistent, FileIsEmpty) {
  std::ofstream myfile;
  myfile.open (glob_test_dir + "/empty.txt");
  myfile.close();
  std::string path = glob_test_dir;
  path += "/empty.txt";
  ASSERT_EQ(-1, sequential_get_size_of_lines(path.c_str()));
}

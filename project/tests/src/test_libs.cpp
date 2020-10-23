//
// Created by Ivan Gorshkov on 22.10.2020.
//

#include "utils.h"
#include <string>
extern "C" {
  #include "libdyn.h"
  #include "libstat.h"
}

TEST(Libs, EqualResOfTwoLibs) {
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
    ASSERT_EQ(sequential_get_size_of_lines(path.c_str()), parallel_get_size_of_lines(path.c_str()));
  }
}

TEST(Libs, Time) {
  startClock();
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
    parallel_get_size_of_lines(path.c_str());
  }
  double  parall = stopClock();
  std::cout << parall << std::endl;
  resetClock();

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
    sequential_get_size_of_lines(path.c_str());
  }
  double  sequential = stopClock();
  std::cout << sequential << std::endl;
  ASSERT_LE(parall, sequential);
}

TEST(Libs, StressTest) {
  generateFile();
  std::cout << glob_test_dir << std::endl;
  std::string path = glob_test_dir;
  path += "/stress_test.txt";
  std::cout << path << std::endl;
  ASSERT_EQ(sequential_get_size_of_lines(path.c_str()), parallel_get_size_of_lines(path.c_str()));
}
#include "test_utils.h"
#include <string>
extern "C" {
  #include "parallel_alg.h"
  #include "consistent_alg.h"
}

TEST(Libs, EqualResOfTwoLibs) {
  void *library;
  int (*parallel_func)(const char *);
  library = dlopen("../../libparallellib.so", RTLD_NOW);
  if(!library){
    GTEST_FATAL_FAILURE_(dlerror());
  }
  parallel_func = (int (*)(const char *))dlsym(library, "parallel_get_size_of_lines");
  for (int kI = 0; kI < number_of_files; ++kI) {
    std::string path = glob_test_dir;
    path += "/out_" + std::to_string(kI + 1) + ".txt";
    std::ifstream is(path);
    int expected = 0;
    is >> expected;
    is.close();
    path = glob_test_dir;
    path += "/in_" + std::to_string(kI + 1) + ".txt";
    ASSERT_EQ(sequential_get_size_of_lines(path.c_str()), (*parallel_func)(path.c_str()));
  }
  dlclose(library);
}

TEST(Libs, Time) {
  void *library;
  int (*parallel_func)(const char *);
  library = dlopen("../../libparallellib.so", RTLD_NOW);
  if(!library){
    GTEST_FATAL_FAILURE_(dlerror());
  }
  parallel_func = (int (*)(const char *))dlsym(library, "parallel_get_size_of_lines");

  startClock();
  for (int kI = 0; kI < number_of_files; ++kI) {
    std::string path = glob_test_dir;
    path += "/out_" + std::to_string(kI + 1) + ".txt";
    std::ifstream is(path);
    int expected = 0;
    is >> expected;
    is.close();
    path = glob_test_dir;
    path += "/in_" + std::to_string(kI + 1) + ".txt";
    (*parallel_func)(path.c_str());
  }
  double  parall = stopClock();
  dlclose(library);
  std::cout << parall << std::endl;
  resetClock();

  for (int kI = 0; kI < number_of_files; ++kI) {
    std::string path = glob_test_dir;
    path += "/out_" + std::to_string(kI + 1) + ".txt";
    std::ifstream is(path);
    int expected = 0;
    is >> expected;
    is.close();
    path = glob_test_dir;
    path += "/in_" + std::to_string(kI + 1) + ".txt";
    sequential_get_size_of_lines(path.c_str());
  }

  double  sequential = stopClock();
  std::cout << sequential << std::endl;
  ASSERT_LE(parall, sequential);
}

TEST(Libs, StressTest) {
  generateFile();
  std::string path = glob_test_dir;
  path += "/stress_test.txt";
  void *library;
  int (*parallel_func)(const char *);
  library = dlopen("../../libparallellib.so", RTLD_NOW);
  if(!library){
    GTEST_FATAL_FAILURE_(dlerror());
  }
  parallel_func = (int (*)(const char *))dlsym(library, "parallel_get_size_of_lines");

  ASSERT_EQ(sequential_get_size_of_lines(path.c_str()), (*parallel_func)(path.c_str()));
  dlclose(library);
}
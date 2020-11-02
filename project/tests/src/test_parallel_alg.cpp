#include "test_utils.h"
#include <string>
extern "C" {
  #include "parallel_alg.h"
}

TEST(Parallel, GetLineSizeFromFileParallel) {
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
    ASSERT_EQ(expected, (*parallel_func)(path.c_str()));
  }
  dlclose(library);
}

TEST(Parallel, WrongPath) {
  void *library;
  int (*parallel_func)(const char *);
  library = dlopen("../../libparallellib.so", RTLD_NOW);
  if(!library){
    GTEST_FATAL_FAILURE_(dlerror());
  }
  parallel_func = (int (*)(const char *))dlsym(library, "parallel_get_size_of_lines");

  std::string path = glob_test_dir;
  path += "/in_wrong.txt";
  ASSERT_EQ(-1, (*parallel_func)(path.c_str()));
  dlclose(library);
}
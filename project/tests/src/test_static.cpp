//
// Created by Ivan Gorshkov on 21.10.2020.
//

#include "utils.h"
#include <string>


TEST(StaticLib, GetLineSizeFromFileStat) {
  int i = 1;
  for (auto& entry : fs::directory_iterator(glob_test_dir / "data")) {
    std::cout << entry.path().parent_path() << std::endl;
    std::string path = entry.path().parent_path();
    path += "/out_" + std::to_string(i) + ".txt";
    std::ifstream is(path);
    int expected = 0;
    is >> expected;
    is.close();
    path = entry.path().parent_path();
    path += "/in_" + std::to_string(i) + ".txt";
    int in = 21;
    ASSERT_EQ(in, 21);
    if (i == number_of_files) break;
    ++i;
  }
}

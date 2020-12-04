#include <fstream>
#include <random>
#include "test_utils.h"
static double start_time = 0;

void startClock() {
  start_time = clock();
}

double stopClock() {
  return (clock() - start_time) / CLOCKS_PER_SEC;
}

void resetClock() {
  start_time = 0;
}

void generateFile() {
  std::ofstream myfile;
  myfile.open (glob_test_dir + "/stress_test.txt");
  for (int i = 0; i < 50000; ++i) {
    if (i != 4999) {
      myfile << rand() % 1000 + 1 << " ";
    } else {
      myfile << rand() % 1000 + 1;
    }
  }
  myfile.close();
}
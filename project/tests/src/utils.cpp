//
// Created by Ivan Gorshkov on 22.10.2020.
//

#include <fstream>
#include <random>
#include "utils.h"
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
  myfile.open (glob_test_dir + "stress_test.txt");
  std::random_device rd;
  std::mt19937 gen(rd());
  for (int i = 0; i < 5000; ++i) {
    if (i != 5000) {
      std::cout << gen() << " ";
    } else {
      std::cout << gen();
    }
  }
  myfile.close();
}
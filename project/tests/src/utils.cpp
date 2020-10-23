//
// Created by Ivan Gorshkov on 22.10.2020.
//

#include <fstream>
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
  myfile << "34 45 56 67 78 89 80 456 345 345 567 345 567 678 456 345 456 567\n";
  myfile.close();
}
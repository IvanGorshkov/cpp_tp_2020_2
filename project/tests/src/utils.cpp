//
// Created by Ivan Gorshkov on 22.10.2020.
//

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

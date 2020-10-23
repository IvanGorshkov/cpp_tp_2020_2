//
// Created by Ivan Gorshkov on 21.10.2020.
//

#pragma once

#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include <ctime>

extern std::string glob_test_dir;
const int number_of_files = 2;
void startClock();
double stopClock();
void resetClock();
void generateFile();
void resetClock();
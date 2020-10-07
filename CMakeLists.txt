cmake_minimum_required(VERSION 3.16)
project(iz1 C)

set(CMAKE_C_STANDARD 99)

add_executable(iz1 project/include/matrix.h project/include/utils.h  project/src/main.c project/src/matrix.c project/src/utils.c) 
cmake_minimum_required(VERSION 3.13.4)
project(iz1 C)

set(CMAKE_C_STANDARD 99)
INCLUDE_DIRECTORIES(project/include)

add_executable(iz1 project/src/main.c project/src/matrix.c project/src/utils.c) 
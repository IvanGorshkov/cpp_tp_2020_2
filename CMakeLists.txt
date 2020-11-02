cmake_minimum_required(VERSION 3.13.4)
project(iz2)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -Wall -Werror -Wpedantic -pthread -lm")

include_directories(project/static/include
                    project/dynamic/include/)
ENABLE_TESTING()

add_executable(${PROJECT_NAME}
        project/main.c
        project/dynamic/src/parallel_alg.c
        project/static/src/consistent_alg.c)

ADD_SUBDIRECTORY(project/tests/)

ADD_LIBRARY(parallellib STATIC
        project/static/src/consistent_alg.c)

ADD_LIBRARY(consistentlib STATIC
        project/dynamic/src/parallel_alg.c)
cmake_minimum_required(VERSION 3.13.4)
project(iz2)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror  -pthread")

include_directories(project/static/include
                    project/dynamic/include/)
ENABLE_TESTING()

ADD_SUBDIRECTORY(project/tests/)

ADD_LIBRARY(libstat STATIC
        project/static/src/libstat.c)

ADD_LIBRARY(libdyn SHARED
        project/dynamic/src/libdyn.c)

target_link_libraries(${PROJECT_NAME} m)
cmake_minimum_required(VERSION 3.13.4)
project(iz2)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror  -pthread")

include_directories(project/static/include project/dynamic/include/)


add_executable(${PROJECT_NAME}
        project/main.c
        project/dynamic/src/libdyn.c
        project/static/src/libstat.c)

target_link_libraries(${PROJECT_NAME} m)
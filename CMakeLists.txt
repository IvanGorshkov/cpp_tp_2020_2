cmake_minimum_required(VERSION 3.13.4)
project(iz1)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")

include_directories(project/include)

enable_testing()

add_subdirectory(project)

add_executable(${PROJECT_NAME}
        project/src/main.c 
	project/src/matrix.c 
	project/src/utils.c)

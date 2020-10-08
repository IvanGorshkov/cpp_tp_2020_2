CMAKE_MINIMUM_REQUIRED(VERSION 3.10.2)
project(test)
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
ENABLE_TESTING()

FIND_PACKAGE(GTest REQUIRED)
INCLUDE_DIRECTORIES("${GTEST_INCLUDE_DIRS}")

FIND_PACKAGE(Threads REQUIRED)

INCLUDE_DIRECTORIES(include/)
ADD_EXECUTABLE( matrix_testing
                src/main.cpp
                src/matrix_utils_test.cpp
        )

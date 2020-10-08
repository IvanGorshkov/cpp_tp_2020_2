find_package(GTest REQUIRED)
FIND_PACKAGE(Threads REQUIRED)
include_directories("${GTEST_INCLUDE_DIRS}")

project(tests)
set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(${PROJECT_NAME} src/main.cpp src/UtilsTest.cpp)

target_link_libraries(${PROJECT_NAME} ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} libiz1)

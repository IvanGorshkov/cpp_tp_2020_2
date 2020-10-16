INCLUDE_DIRECTORIES(include)
ADD_LIBRARY(libiz1 STATIC src/matrix.c src/utils.c )

ADD_SUBDIRECTORY(tests)

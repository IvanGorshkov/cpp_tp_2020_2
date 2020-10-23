#include <stdio.h>
#include "libstat.h"
#include "libdyn.h"

int main(int argc, char** argv) {
  printf("%d\n", parallel_get_size_of_lines(argv[1]));
  printf("%d\n", sequential_get_size_of_lines(argv[1]));
  return 0;
}

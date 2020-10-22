#include <stdio.h>
#include <stddef.h>
#include "libstat.h"
#include <sys/time.h>
#include "libdyn.h"

int main() {
  struct timeval start, stop;
  double secs = 0;
  gettimeofday(&start, NULL);
  printf("%d\n", parallel_get_size_of_lines("./project/tests/data/in_1.txt"));
  gettimeofday(&stop, NULL);
  secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
  printf("time taken %f\n", secs);

  struct timeval start2, stop2;
  double secs2 = 0;
  gettimeofday(&start2, NULL);
  printf("%d\n", sequential_get_size_of_lines("./project/tests/data/in_1.txt"));
  gettimeofday(&stop2, NULL);
  secs2 = (double)(stop2.tv_usec - start2.tv_usec) / 1000000 + (double)(stop2.tv_sec - start2.tv_sec);
  printf("time taken %f\n", secs2);

  return 0;
}

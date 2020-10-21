//
// Created by Ivan Gorshkov on 20.10.2020.
//

#include "libstat.h"
#include <stdio.h>
#include <math.h>

static int calc_all_line_size(int32_t *array, size_t count) {
  int res = 0;
  for (size_t kI = 0; kI < count; ++kI) {
    u_int32_t x = array[kI];
    char coordinates[4];

    for (int i = 0; i < 4; ++i) {
      coordinates[3 - i] = (x >> (8 * i)) & 0xff;
    }

    res += sqrt(pow(coordinates[3] - coordinates[1], 2) - pow(coordinates[2] - coordinates[0], 2));
  }

  return res;
}

int sequential_get_size_of_lines(const char *path) {
  FILE *file = fopen(path, "rb");
  if (!file) {
    fprintf(stderr, "Failed to open file for read\n");
    return -1;
  }
  u_int32_t count_of_num = 0;
  while (!feof(file)) {
    char char_file = fgetc(file);
    if (char_file == ' ') {
      ++count_of_num;
    }
  }

  ++count_of_num;
  int32_t* array = calloc(count_of_num, sizeof(int32_t));
  fseek(file, 0, SEEK_SET);

  for (size_t i = 0; i < count_of_num; i++) {
    fscanf(file, "%d", &array[i]);
  }

  fclose(file);
  int result = calc_all_line_size(array, count_of_num);
  free(array);
  return result;
}

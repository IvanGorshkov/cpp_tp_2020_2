#include "consistent_alg.h"
#include "utils.h"
#include <stdio.h>

int sequential_get_size_of_lines(const char *path) {
  u_int32_t *array = NULL;
  size_t count_of_num = 0;

  if (read_from_file(path, &count_of_num, &array) == -1) {
    return -1;
  }

  meta* info = calloc(1, sizeof(meta));
  info->begin = 0;
  info->size_ = count_of_num;
  info->array = array;
  int result = calculation(info);
  if (result == -1) {
    free(array);
    free(info);
    return -1;
  }
  free(array);
  free(info);

  return result;
}

#ifndef PROJECT_ALL_INCLUDE_UTILS_H_
#define PROJECT_ALL_INCLUDE_UTILS_H_
#include <stdlib.h>

typedef struct {
  size_t begin;
  size_t size_;
  u_int32_t *array;
  int res;
} meta;

int read_from_file(const char *path, size_t *count_of_num, u_int32_t **array);
int calculation(meta *info);

#endif  // PROJECT_ALL_INCLUDE_UTILS_H_

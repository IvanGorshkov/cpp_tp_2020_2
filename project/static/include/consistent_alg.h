#ifndef PROJECT_STATIC_INCLUDE_CONSISTENT_ALG_H_
#define PROJECT_STATIC_INCLUDE_CONSISTENT_ALG_H_
#include <stdlib.h>

typedef struct {
  size_t begin;
  size_t size_;
  u_int32_t *array;
  int res;
} meta;

int calculation(meta *info);
int sequential_get_size_of_lines(const char *path);

#endif  // PROJECT_STATIC_INCLUDE_CONSISTENT_ALG_H_

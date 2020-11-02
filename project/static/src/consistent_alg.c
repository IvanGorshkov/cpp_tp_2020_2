#include "consistent_alg.h"
#include <stdio.h>
#include <math.h>

int calculation(meta *info) {
  if (info == NULL) {
    return -1;
  }

  int res = 0;
  for (size_t i = info->begin; i < info->begin + info->size_; ++i) {
    u_int32_t number = info->array[i];
    char coordinates[4];
    for (int byte = 0; byte < 4; ++byte) {
      coordinates[3 - byte] = (number >> (8 * byte)) & 0xff;
    }
    res  += sqrt(pow(coordinates[3] - coordinates[1], 2) - pow(coordinates[2] - coordinates[0], 2));
  }
  return res;
}
int read_from_file(const char *path, size_t *count_of_num, u_int32_t **array) {
  FILE *file = fopen(path, "r");
  if (!file) {
    fprintf(stderr, "Failed to open file for read\n");
    return -1;
  }

  while (!feof(file)) {
    char char_file = fgetc(file);
    if (char_file == ' ') {
      ++(*count_of_num);
    }
  }

  ++(*count_of_num);
  u_int32_t* arr = calloc(*count_of_num, sizeof(u_int32_t));

  if (arr == NULL) {
    if (fclose(file)) {
      fprintf(stderr, "Failed to close file\n");
    }
    return -1;
  }

  fseek(file, 0, SEEK_SET);
  for (size_t i = 0; i < *count_of_num; i++) {
    if (fscanf(file, "%u", &arr[i]) != 1) {
      free(arr);
      if (fclose(file)) {
        fprintf(stderr, "Failed to close file\n");
      }
      return -1;
    }
  }

  if (fclose(file)) {
    free(arr);
    fprintf(stderr, "Failed to close file\n");
    return -1;
  }
  *array = arr;
  return EXIT_SUCCESS;
}

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

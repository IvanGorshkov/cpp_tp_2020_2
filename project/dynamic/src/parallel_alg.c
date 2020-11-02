#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include "parallel_alg.h"
#include "consistent_alg.h"

static void *thread_run(void *arg) {
  meta* info = (meta*)arg;
  if (info == NULL) {
    return NULL;
  }
  info->res = calculation(info);
  return NULL;
}

static int creat_threads(u_int32_t *array, size_t count_of_num) {
  long number_of_thread = sysconf(_SC_NPROCESSORS_ONLN);
  if ((size_t)number_of_thread > count_of_num) {
    number_of_thread = count_of_num;
  }

  pthread_t* ths = calloc(number_of_thread, sizeof(pthread_t));
  if (ths == NULL) {
    return -1;
  }

  meta* info =  calloc(number_of_thread, sizeof(meta));
  if (info == NULL) {
    free(ths);
    return -1;
  }

  for (int kI = 0; kI < number_of_thread; ++kI) {
    info[kI].begin = kI * count_of_num / number_of_thread;
    if (kI == number_of_thread - 1) {
      info[kI].size_ = count_of_num - info[kI].begin;
    } else {
      info[kI].size_ = ((kI + 1) * count_of_num / number_of_thread) - info[kI].begin;
    }
    info[kI].array = array;
    pthread_create(&ths[kI], NULL, thread_run, &info[kI]);
  }

  int result = 0;
  for (int index_thread = 0; index_thread < number_of_thread; ++index_thread) {
    int errflag = pthread_join(ths[index_thread], NULL);
    result += info[index_thread].res;
    if (errflag != 0) {
      fprintf(stderr, "Failed to close thread\n");
      free(info);
      free(ths);
      return -1;
    }
  }

  free(info);
  free(ths);
  return result;
}

int parallel_get_size_of_lines(const char *path) {
  FILE *file = fopen(path, "r");
  if (!file) {
    fprintf(stderr, "Failed to open file for read\n");
    return -1;
  }

  size_t count_of_num = 0;
  while (!feof(file)) {
    char char_file = fgetc(file);
    if (char_file == ' ') {
      ++count_of_num;
    }
  }

  ++count_of_num;
  u_int32_t* array = calloc(count_of_num, sizeof(u_int32_t));

  if (array == NULL) {
    if (fclose(file)) {
      fprintf(stderr, "Failed to close file\n");
    }
    return -1;
  }

  fseek(file, 0, SEEK_SET);
  for (size_t i = 0; i < count_of_num; i++) {
    if (fscanf(file, "%u", &array[i]) != 1) {
      free(array);
      if (fclose(file)) {
        fprintf(stderr, "Failed to close file\n");
      }
      return -1;
    }
  }

  if (fclose(file)) {
    free(array);
    fprintf(stderr, "Failed to close file\n");
    return -1;
  }

  int result = creat_threads(array, count_of_num);
  if (result == -1) {
    free(array);
    return -1;
  }
  free(array);
  return result;
}

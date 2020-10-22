//
// Created by Ivan Gorshkov on 16.10.2020.
//

#include "libdyn.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>

typedef struct {
  int value;
  pthread_mutex_t mutex;
} data_t;

typedef struct {
  size_t begin;
  size_t size_;
  u_int32_t *array;
} meta;

data_t data = {0, PTHREAD_MUTEX_INITIALIZER};

static int calculation(meta *info) {
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

static void *thread_run(void *arg) {
  pthread_mutex_t *mutex = &data.mutex;

  meta* info = (meta*)arg;
  if (info == NULL) {
    return NULL;
  }
  int res = calculation(info);

  int err_flag = 0;
  err_flag = pthread_mutex_lock(mutex);
  if (err_flag != 0) {
    fprintf(stderr, "Failed to lock mutex\n");
    return NULL;
  }

  data.value += res;
  err_flag = pthread_mutex_unlock(mutex);
  if (err_flag != 0) {
    fprintf(stderr, "Failed to unlock mutex\n");
    return NULL;
  }

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

  for (int index_thread = 0; index_thread < number_of_thread; ++index_thread) {
    int errflag = pthread_join(ths[index_thread], NULL);
    if (errflag != 0) {
      fprintf(stderr, "Failed to close thread\n");
      free(info);
      free(ths);
      return -1;
    }
  }

  free(info);
  free(ths);
  return data.value;
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
    fscanf(file, "%d", &array[i]);
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
  data.value = 0;
  return result;
}

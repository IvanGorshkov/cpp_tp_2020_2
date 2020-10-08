//
//  utils.c
//  DZ1
//
//  Created by Ivan Gorshkov on 02.10.2020.
//

#include <stdlib.h>
#include <string.h>
#include "utils.h"

int check_empty_value(const char* str, const size_t rows, const size_t cols) {
  if (rows == 0 || cols == 0 || !strcmp(str, "")) {
    return 1;
  }
  return 0;
}

int convert_str_to_arr(const char* str, const size_t size, double **linematrix) {
    double* arr = calloc(size, sizeof(double));
    if (arr == NULL) {
        return EXIT_FAILURE;
    }

    size_t num_array = 0;
    for (int num_letter = 0; str[num_letter] != '\0'; ++num_letter) {
        if (str[num_letter] != ' ') {
            if (str[num_letter] < '0' || str[num_letter] > '9') {
                free(arr);
                arr = NULL;
                return EXIT_FAILURE;
            }

            if (num_array < size) {
                arr[num_array] = arr[num_array] * 10 + (str[num_letter] - 48);
            } else {
                free(arr);
                arr = NULL;
            }
        } else {
            num_array++;
        }
    }

    if (arr != NULL && (size > ++num_array)) {
       free(arr);
       arr = NULL;
     }

    if (arr == NULL) {
        return EXIT_FAILURE;
    }

    *linematrix = arr;
    return EXIT_SUCCESS;
}

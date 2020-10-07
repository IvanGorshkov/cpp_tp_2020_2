//
//  utils.c
//  DZ1
//
//  Created by Ivan Gorshkov on 02.10.2020.
//

#include <stdlib.h>
#include <string.h>
#include "utils.h"

int convert_str_to_arr(const char* str, const int size, double **linematrix) {
    double* arr = calloc(size, sizeof(double));
    if (arr == NULL) {
        return EXIT_FAILURE;
    }

    int num_array = 0;
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

    if (arr == NULL) {
        return EXIT_FAILURE;
    }

    *linematrix = arr;
    return EXIT_SUCCESS;
}

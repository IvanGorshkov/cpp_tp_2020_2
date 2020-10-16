//
//  main.c
//  DZ1
//
//  Created by Ivan Gorshkov on 01.10.2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "matrix.h"

int main() {
    size_t rows = 0;
    size_t cols = 0;
    char str[1024] = {0};
    if (!scanf("%zu %zu %1023[^\t\n]s", &rows, &cols, str)) {
      return EXIT_FAILURE;
    }

    if (check_empty_value(str, rows, cols)) {
      printf("Oh... Error values\n");
      return EXIT_FAILURE;
    }

    double* array = NULL;
    if (!convert_str_to_arr(str, rows * cols, &array)) {
        matrix* new_matrix = generate_adjacency(array, rows, cols);
        if (new_matrix == NULL) {
            printf("Oh... Could not to creat matrix\n");
            free(array);
            return EXIT_FAILURE;
        }

        if (print_matrix(new_matrix)) {
            printf("Oh... Matrix is NULL\n");
            free(array);
            free_matrix(new_matrix);
            return EXIT_FAILURE;
        }

        free_matrix(new_matrix);
    }

    if (array == NULL) {
        printf("Oh... Error values\n");
    }

    free(array);
    return 0;
}

//
//  main.c
//  DZ1
//
//  Created by Ivan Gorshkov on 01.10.2020.
//

#include <malloc/_malloc.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "matrix.h"


int main(int argc, const char * argv[]) {
    size_t rows = 0;
    size_t cols = 0;
    char str[1024] = {0};
    scanf("%zd %zd %[^\t\n]s", &rows, &cols, str);
    
    if (rows == 0 || cols == 0 || !strcmp(str, "")) {
        printf("Oh... Error values\n");
        return 0;
    }
    
    double* array = NULL;
    if (!convert_str_to_arr(str, rows * cols, &array)) {
        Matrix* new_matrix = generate_adjacency(array, rows, cols);
        if (new_matrix == NULL) {
            printf("Oh... Could not to creat matrix\n");
            free(array);
            array = NULL;
        }
        
        if (print_matrix(new_matrix)) {
            printf("Oh... Matrix is NULL\n");
            free(array);
            array = NULL;
            free_matrix(new_matrix);
            new_matrix = NULL;
        }
        
        free_matrix(new_matrix);
        
    }
    
    if (array == NULL) {
        printf("Oh... Error values\n");
    }
    
    free(array);
    return 0;
}

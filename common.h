#include <stdio.h>  
#include <stdlib.h> 
#include <string.h> 

char** copyCharArray(char** original, size_t rows, size_t cols) {
    char** copy = (char**)malloc(rows * sizeof(char*));
    if (copy == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < rows; ++i) {
        size_t length = strlen(original[i]);
        copy[i] = (char*)malloc((length + 1) * sizeof(char));
        if (copy[i] == NULL) {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }
        strcpy(copy[i], original[i]);
    }

    return copy;
}

void freeCharArray(char** array, size_t rows) {
    for (size_t i = 0; i < rows; ++i) {
        free(array[i]);
    }
    free(array);
}

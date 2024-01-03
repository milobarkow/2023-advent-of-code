#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

void dayOne(char **lines, size_t lineCount);
void dayTwo(char **lines, size_t lineCount);
void dayThree(char **lines, size_t lineCount);
void dayFour(char **lines, size_t lineCount);
void dayFive(char **lines, size_t lineCount);
void daySix(char **lines, size_t lineCount);
void daySeven(char **lines, size_t lineCount);
void dayEight(char **lines, size_t lineCount);
void dayNine(char **lines, size_t lineCount);
void dayTen(char **lines, size_t lineCount);

// http://nothings.org/stb_ds/
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

// taken from Tsoding
// https://github.com/tsoding
#define DA_INIT_CAP 256
#define da_append(da, item)                                                          \
    do {                                                                             \
        if ((da)->count >= (da)->capacity) {                                         \
            (da)->capacity = (da)->capacity == 0 ? DA_INIT_CAP : (da)->capacity*2;   \
            (da)->items = realloc((da)->items, (da)->capacity*sizeof(*(da)->items)); \
            assert((da)->items != NULL && "Buy more RAM lol");                       \
        }                                                                            \
                                                                                     \
        (da)->items[(da)->count++] = (item);                                         \
    } while (0)
    
char** copyCharArray(char** original, size_t rows) {
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

#endif

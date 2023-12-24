#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "day_9.h"

#define MAX_LINE_LENGTH 1000

int main(void) {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1; 
    }
    char **lines = NULL;
    size_t lineCount = 0;
    char buffer[MAX_LINE_LENGTH];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        char *line = strdup(buffer);
        lines = realloc(lines, (lineCount + 1) * sizeof(char *));
        if (line == NULL || lines == NULL) {
            perror("Error allocating memory");
            return 1; 
        }
        lines[lineCount++] = line;
    }
    fclose(file);

    partTwo(lines, lineCount);

    freeCharArray(lines, lineCount);
    return 0; 
}


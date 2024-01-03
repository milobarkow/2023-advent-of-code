#include "common.h"

#define MAX_LINE_LENGTH 1000

int main(int argc, char **argv) {
    void partOne(char **data, size_t data_size);
    void partTwo(char **data, size_t data_size);
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

    switch (atoi(argv[1])) {
#ifdef DAY_1
    case 1: dayOne(lines, lineCount); break;
#endif
#ifdef DAY_2
    case 2: dayTwo(lines, lineCount); break;
#endif
#ifdef DAY_3
    case 3: dayThree(lines, lineCount); break;
#endif
#ifdef DAY_4
    case 4: dayFour(lines, lineCount); break;
#endif
#ifdef DAY_5
    case 5: dayFive(lines, lineCount); break;
#endif
#ifdef DAY_6
    case 6: daySix(lines, lineCount); break;
#endif
#ifdef DAY_7
    case 7: daySeven(lines, lineCount); break;
#endif
#ifdef DAY_8
    case 8: dayEight(lines, lineCount); break;
#endif
#ifdef DAY_9
    case 9: dayNine(lines, lineCount); break;
#endif
#ifdef DAY_10
    case 10: dayTen(lines, lineCount); break;
#endif
    default: printf("Invalid day number"); break;
    }

    freeCharArray(lines, lineCount);
    return 0;
}


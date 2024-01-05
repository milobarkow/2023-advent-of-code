#include "common.h"

#include <time.h>

#include "day_1.h"
#include "day_2.h"
#include "day_3.h"
#include "day_4.h"
#include "day_5.h"
#include "day_6.h"
#include "day_7.h"
#include "day_8.h"
#include "day_9.h"
#include "day_10.h"
#include "day_11.h"
#include "day_12.h"

#define MAX_LINE_LENGTH 1000

int main(int argc, char **argv) {
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

    clock_t start_time, end_time;
    double cpu_time_used;
    start_time = clock();

    switch (atoi(argv[1])) {
    case 1: dayOne(lines, lineCount); break;
    case 2: dayTwo(lines, lineCount); break;
    case 3: dayThree(lines, lineCount); break;
    case 4: dayFour(lines, lineCount); break;
    case 5: dayFive(lines, lineCount); break;
    case 6: daySix(lines, lineCount); break;
    case 7: daySeven(lines, lineCount); break;
    case 8: dayEight(lines, lineCount); break;
    case 9: dayNine(lines, lineCount); break;
    case 10: dayTen(lines, lineCount); break;
    case 11: dayElleven(lines, lineCount); break;
    case 12: dayTwelve(lines, lineCount); break;
    default: printf("No day provided\n"); break;
    }

    end_time = clock();
    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    if (cpu_time_used > 0.0) {
        printf("Time: %f seconds\n", cpu_time_used);
    }

    freeCharArray(lines, lineCount);
    return 0;
}


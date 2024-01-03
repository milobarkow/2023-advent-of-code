#ifndef DAY_3
#define DAY_3

#include "common.h"

int numPlaces (int n) {
    if (n < 0) return numPlaces ((n == INT_MIN) ? INT_MAX : -n);
    if (n < 10) return 1;
    return 1 + numPlaces (n / 10);
}

void partOne3(char **data, size_t data_size) {
    const char *dels_1 = ".+*#$!@%^&()-_=[]{}/\\<>";
    const char *dels_2 = "+*#$!@%^&()-_=[]{}/\\<>";
    int count = 0;
    int line_length = 140;

    char** data_copy = copyCharArray(data, data_size);

    for (int i = 0; i < data_size; i++) {
        char *line = data[i];

        char * pch;
        pch = strtok (line, dels_1);
        int index, digits;
        while (pch != NULL)
        {
            int n = atoi(pch);
            index = pch - line;
            digits = numPlaces(n);

            int found = 0;
            for (int y = i - 1; (y < i + 2) && (found == 0); y++) {
                for (int x = index - 1; (x < index + digits + 1) && (found == 0); x++) {
                    if ((x >= 0) && (x < line_length) && (y >= 0) && (y < data_size)) {
                        char *check = data_copy[y] + x;
                        if ((strchr(dels_2, *check) != NULL)) {
                            found = 1;
                        }
                    }
                }
            }
            if (found == 1) count += n;
            pch = strtok(NULL, dels_1);
        }
    }
    printf("Part 1 Answer: %i\n", count);
}


void partTwo3(char **data, size_t data_size) {
    const char *dels_1 = ".+*#$!@%^&()-_=[]{}/\\<>";
    const char *dels_2 = "+*#$!@%^&()-_=[]{}/\\<>";
    int count = 0;
    int line_length = 140;

    char** data_copy = copyCharArray(data, data_size);

    int tracker_data_size = 4;
    int tracker[data_size][line_length][tracker_data_size];
    for (size_t i = 0; i < data_size; i++) {
        for (size_t j = 0; j < line_length; j++) {
            for (size_t k = 0; k < tracker_data_size; k++) {
                tracker[i][j][k] = 0;
            }
        }
    }
    for (int i = 0; i < data_size; i++) {
        char *line = data[i];

        char * pch;
        pch = strtok (line, dels_1);
        int index, digits;
        while (pch != NULL)
        {
            int n = atoi(pch);
            index = pch - line;
            digits = numPlaces(n);

            for (int y = i - 1; (y < i + 2); y++) {
                for (int x = index - 1; (x < index + digits + 1); x++) {
                    if ((x >= 0) && (x < line_length) && (y >= 0) && (y < data_size)) {
                        char *check = &data_copy[y][x];
                        if ((strchr(dels_2, *check) != NULL)) {
                            if (*check == '*') {
                                tracker[y][x][0]++;
                                if (tracker[y][x][1] == 0) tracker[y][x][1] = n;
                                else if (tracker[y][x][2] == 0) tracker[y][x][2] = n;
                                else if (tracker[y][x][3] == 0) tracker[y][x][3] = n;
                            }
                        }
                    }
                }
            }
            pch = strtok(NULL, dels_1);
        }
    }
    for (size_t i = 0; i < data_size; i++) {
        for (size_t j = 0; j < line_length; j++) {
            if ((tracker[i][j][3] != -1) && (tracker[i][j][0] == 2)) {
                count += tracker[i][j][1] * tracker[i][j][2];
            }
        }
    }
    printf("Part 2 Answer: %i\n", count);
}

void dayThree(char **data, size_t data_size) {
    partOne3(data, data_size);
    partTwo3(data, data_size);
}

#endif // DAY_3
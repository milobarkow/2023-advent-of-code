#ifndef DAY_6
#define DAY_6

#include "common.h"

#define INFO_ROWS 2
#define INFO_COLS 1

void partOne6(char **data, size_t data_size) {
    int count = 1;
    int info[INFO_ROWS][INFO_COLS];
    char *dels = " ";

    for (int i = 0; i < INFO_ROWS; i++) {
        char * line = strchr(data[i], ' ');
        char * pch;
        int size = 0;
        pch = strtok (line, dels);
        while (pch != NULL)
        {
            info[i][size] = atoi(pch);
            pch = strtok(NULL, dels);
            size++;
        }
    }
    for (int i = 0; i < INFO_COLS; i++) {
        int time = info[0][i];
        int distance = info[1][i];
        int curr = 0;
        for (int j = 0; j <= time; j++) {
            int a = j * (time - j);
            if (a > distance) curr++;
        }
        count *= curr;
    }
    printf("Part 1 Answer: %i\n", count);
}

void append(char* s, char* c)
{
    size_t len_s = strlen(s);
    size_t len_c = strlen(c);
    char *temp = malloc(len_s + len_c + 1);
    if (temp == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    strcpy(temp, s);
    strcat(temp, c);
    strcpy(s, temp);
    free(temp);
}

void partTwo6(char **data, size_t data_size) {
    char time[100] = "";
    char distance[100] = "";
    char *dels = " ";

    for (int i = 0; i < INFO_ROWS; i++) {
        char *line = strchr(strdup(data[i]), ' ');
        char * pch;
        pch = strtok (line, dels);
        while (pch != NULL)
        {
            if (i == 0) append(time, pch);
            else append(distance, pch);
            pch = strtok(NULL, dels);
        }
    }

    long long int time_n = atoll(time);
    long long int distance_n = atoll(distance);
    int count = 0;
    for (long long int j = 0; j <= time_n; j++) {
        long long int a = j * (time_n - j);
        if (a > distance_n) count++;
    }
    printf("Part 2 Answer: %i\n", count);
}

void daySix(char **data, size_t data_size) {
    partOne6(data, data_size);
    partTwo6(data, data_size);
}

#endif // DAY_6

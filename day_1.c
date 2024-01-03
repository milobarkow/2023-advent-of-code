#include <stdio.h>
#include <ctype.h>

void partOne1(char **data, size_t data_size) {
    int count = 0;
    for (size_t i = 0; i < data_size; i++) {
        char *c = data[i];
        char vals[strlen(c)];
        int vals_size = 0;
        while (*c != '\0') {
            if (isdigit(*c)) {
                vals[vals_size] = *c;
                vals_size++;
            }
            c++;
        }
        char num[3] = {vals[0], vals[vals_size - 1], '\0'};
        count += atoi(num);
    }
    printf("Part 1 Answer: %i\n", count);
}

void partTwo1(char **data, size_t data_size) {
    int count = 0;
    char nums[10][10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    for (size_t i = 0; i < data_size; i++) {
        char *c = data[i];
        char num[3] = {'\0', '\0', '\0'};
        while (*c != '\0') {
            if (isdigit(*c)) {
                if (num[0] == '\0') num[0] = *c;
                else num[1] = *c;
            } else {
                int found = 0;
                int x = 3;
                while ((x <= 5) && found == 0) {
                    char* comp = (char*)malloc(x + 1);
                    strncpy(comp, c, x);
                    comp[x] = '\0';
                    for (int j = 0; j < 10; j++) {
                        if (strcmp(comp, nums[j]) == 0) {
                            if (num[0] == '\0') num[0] = j + '0';
                            else num[1] = j + '0';
                            found = 1;
                            break;
                        }
                    }
                    x++;
                }
            }
            c++;
        }
        if (num[1] == '\0') num[1] = num[0];
        count += atoi(num);
    }
    printf("Part 2 Answer: %i\n", count);
}

void dayOne(char **data, size_t data_size) {
    partOne1(data, data_size);
    partTwo1(data, data_size);
}

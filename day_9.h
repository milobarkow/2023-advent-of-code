#include "common.h"

// http://nothings.org/stb_ds/
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

void parseLine(int **nums, char* line) {
    const char dels[] = " \n";
    char *token;
    token = strtok(line, dels);
    while ( token != NULL ) {
        int n = atoi(token);
        arrput(*nums, n);
        token = strtok(NULL, dels);
    }
}

size_t allSame(int *nums, size_t nums_len) {
    int n = nums[0];
    n = 0;
    for (size_t i = 0; i < nums_len; i++) {
        if (nums[i] != n) return 0;
    }
    return 1;
}

int getNext(int *nums, size_t nums_len, size_t part) {
    if (allSame(nums, nums_len) == 1) {
        return nums[0];
    } else {
        int *new_nums = NULL;
        for (size_t i = 0; i < nums_len - 1; i++) {
            arrput(new_nums, nums[i + 1] - nums[i]);
        }
        int ret;
        if (part == 1) {
            ret = nums[nums_len - 1] + getNext(new_nums, nums_len - 1, 1);
        }
        else {
            ret = nums[0] - getNext(new_nums, nums_len - 1, part);
        }
        arrfree(new_nums);
        return ret;
    }
}

void partOne(char **data, size_t data_size) {
    long long int count = 0;
    int *nums = NULL;
    for (size_t i = 0; i < data_size; i++) {
        parseLine(&nums, data[i]);
        count += (long long int)getNext(nums, arrlen(nums), 1);
        nums = NULL;
    }
    printf("Part 1 Answer: %lli\n", count);
}

void partTwo(char **data, size_t data_size) {
    long long int count = 0;
    int *nums = NULL;
    for (size_t i = 0; i < data_size; i++) {
        parseLine(&nums, data[i]);
        count += (long long int)getNext(nums, arrlen(nums), 2);
        nums = NULL;
    }
    printf("Part 2 Answer: %lli\n", count);
}

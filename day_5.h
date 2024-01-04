#ifndef DAY_5
#define DAY_5

#include "common.h"

#include <inttypes.h>

typedef struct {
    size_t *items;
    size_t count;
    size_t capacity;
} DA_UI;

void parseNums(DA_UI *nums, char* line, const char dels[]) {
    char *token;
    token = strtok(line, dels);
    while ( token != NULL ) {
        // printf("%s\n", token);
        size_t n = atoi(token);
        da_append(nums, n);
        token = strtok(NULL, dels);
    }
    free(token);
}

typedef struct Map {
    size_t start_index;
    size_t line_count;
} Map;

typedef struct {
    Map *items;
    size_t count;
    size_t capacity;
} DA_MAP;

void printMapLine(int* ml) {
    printf("%i %i %i\n", ml[0], ml[1], ml[2]);
}

void getMapLine(DA_UI map_nums, Map map, size_t line, int *nums) {
    assert(line < map.line_count);
    size_t s = map.start_index + 3 * line;
    *(nums + 0) = map_nums.items[s];
    *(nums + 1) = map_nums.items[s + 1];
    *(nums + 2) = map_nums.items[s + 2];
}

void partOne5(char **data, size_t data_size) {
    DA_UI seeds = {0};
    parseNums(&seeds, data[0], "seeds: \n");

    DA_UI map_nums = {0};
    DA_MAP maps = {0};
    size_t i = 1;

    while (i < data_size) {
        if (strlen(data[i]) > 0 && data[i][strlen(data[i]) - 1] == ':') {
            Map map = {.start_index = map_nums.count, .line_count = 0, };
            i++;
            while (strlen(data[i]) != 0) {
                parseNums(&map_nums, data[i], " \n");
                map.line_count++;
                i++;
            }
            da_append(&maps, map);
        } else i++;
    }

    size_t seed;
    size_t min_seed;
    int curr_line[3] = {0};
    size_t x, y, z;
    for (size_t i = 0; i < seeds.count; i++) {
        seed = seeds.items[i];
        for (size_t j = 0; j < maps.count; j++) {
            for (size_t k = 0; k < maps.items[j].line_count; k++) {
                getMapLine(map_nums, maps.items[j], k, curr_line);
                x = curr_line[0]; y = curr_line[1]; z = curr_line[2];
                if (seed >= y && seed <= y + z - 1) {
                    seed = x + (seed - y);
                    break;
                }
            }
        }
        if (seed < min_seed) min_seed = seed;
    }

    printf("Part 1 Answer: %i\n", min_seed);
}

void partTwo5(char **data, size_t data_size) {
    // int64_t n = 3890048781;
    // printf("%"PRId64 "\n", n);
    // return;
    DA_UI seed_pairs = {0};
    parseNums(&seed_pairs, data[0], "seeds: \n");

    DA_UI map_nums = {0};
    DA_MAP maps = {0};
    size_t i = 1;

    while (i < data_size) {
        if (strlen(data[i]) > 0 && data[i][strlen(data[i]) - 1] == ':') {
            Map map = {.start_index = map_nums.count, .line_count = 0, };
            i++;
            while (strlen(data[i]) != 0) {
                parseNums(&map_nums, data[i], " \n");
                map.line_count++;
                i++;
            }
            da_append(&maps, map);
        } else i++;
    }

    int64_t seed;
    int64_t s;
    int64_t min_seed;
    int64_t check_range_b = INT64_MAX;
    int64_t check_range_t = INT64_MIN;
    int64_t range_b, range_t;
    size_t index;
    size_t x, y, z;
    for (size_t i = 0; i < seed_pairs.count; i += 2) {
        range_b = seed_pairs.items[i];
        range_t = seed_pairs.items[i] + seed_pairs.items[i + 1];
        s = range_b;
        while (s < range_t) {
            seed = s;
            for (size_t j = 0; j < maps.count; j++) {
                for (size_t k = 0; k < maps.items[j].line_count; k++) {
                    index = maps.items[j].start_index + 3 * k;
                    x = map_nums.items[index];
                    y = map_nums.items[index + 1];
                    z = map_nums.items[index + 2];
                    if (seed >= y && seed <= y + z - 1) {
                        seed = x + (seed - y);
                        break;
                    }
                }
            }
            if (seed < min_seed) min_seed = seed;
            s++;
        }
        if (range_b < check_range_b) check_range_b = range_b;
        if (range_t > check_range_t) check_range_t = range_t;
    }

    printf("Part 2 Answer: %i\n", min_seed);
}

void dayFive(char **data, size_t data_size) {
    partOne5(data, data_size);
    partTwo5(data, data_size);
}

#endif // DAY_5

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void partOne(char **data, size_t data_size) {
    int count = 0;
    for (size_t i = 0; i < data_size; i++) {
        char *line = data[i];

        int win_len = strchr(line, '|') - strchr(line, ':');
        char win[win_len];
        strncpy(win, strchr(line, ':'), win_len);

        line = strchr(line, ':');

        int winners[10];
        for (size_t j = 0; j < 10; j++) {
            while (!isdigit(*line)) line++;
            int num_len = strchr(line, ' ') - line;
            char num_str[num_len];
            strncpy(num_str, line, num_len);
            winners[j] = atoi(num_str);
            line += num_len + 1;
        }

        int my_nums[25];
        for (size_t j = 0; j < 25; j++) {
            while (!isdigit(*line)) line++;
            int my_num_len = strchr(line, ' ') - line;
            char my_num_str[my_num_len];
            strncpy(my_num_str, line, my_num_len);
            my_nums[j] = atoi(my_num_str);
            line += my_num_len + 1;
        }

        int score = 0;
        for (size_t x = 0; x < 25; x++) {
            for (size_t y = 0; y < 10; y++) {
                if (my_nums[x] == winners[y]) {
                    score = score == 0 ? 1 : score * 2;
                }
            }
        }
        count += score;

    }
    printf("Part 1 Answer: %i\n", count);
}


void partTwo(char **data, size_t data_size) {
    int card_count[data_size];
    for (size_t i = 0; i < data_size; i++) {
        card_count[i] = 1;
    }

#define WL 10
#define NL 25
    size_t matches;
    for (size_t i = 0; i < data_size; i++) {
        char *line = data[i];

        int win_len = strchr(line, '|') - strchr(line, ':');
        char win[win_len];
        strncpy(win, strchr(line, ':'), win_len);

        line = strchr(line, ':');

        int winners[WL];
        for (size_t j = 0; j < WL; j++) {
            while (!isdigit(*line)) line++;
            int num_len = strchr(line, ' ') - line;
            char num_str[num_len];
            strncpy(num_str, line, num_len);
            winners[j] = atoi(num_str);
            line += num_len + 1;
        }

        int my_nums[NL];
        for (size_t j = 0; j < NL; j++) {
            while (!isdigit(*line)) line++;
            int my_num_len = strchr(line, ' ') - line;
            char my_num_str[my_num_len];
            strncpy(my_num_str, line, my_num_len);
            my_nums[j] = atoi(my_num_str);
            line += my_num_len + 1;
        }

        matches = 0;
        for (size_t x = 0; x < NL; x++) {
            for (size_t y = 0; y < WL; y++) {
                if (my_nums[x] == winners[y]) {
                    matches++;
                }
            }
        }
        for (size_t j = 0; j < matches; j++) {
            card_count[i + j + 1] += card_count[i];
        }
    }
    int count = 0;
    for (size_t i = 0; i < data_size; i++) {
        count += card_count[i];
    }

    printf("Part 2 Answer: %i\n", count);
}

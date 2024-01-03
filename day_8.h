#ifndef DAY_8
#define DAY_8

#include "common.h"

void parseLine(char *parsed_line[], char* line) {
    const char dels[] = " =,()\n";
    char *token;
    token = strtok(line, dels);
    size_t i = 0;
    while ( token != NULL ) {
        parsed_line[i++] = token;
        token = strtok(NULL, dels);
    }
}

typedef struct Node {
    char * val;
    size_t left_index;
    size_t right_index;
} Node;

void printNode(const Node *node) {
    printf("Value: %s, Left Index: %zu, Right Index: %zu\n",
           node->val,
           node->left_index,
           node->right_index);
}

void partOne8(char **data, size_t data_size) {
    size_t key_len = strlen(data[0]);
    size_t *key = malloc(key_len * sizeof(size_t));
    for (size_t i = 0; i < key_len; i++) {
        key[i] = data[0][i] == 'R' ? 1 : 0;
    }

    size_t line_count = data_size - 2;

    size_t curr_index;
    char *parsed_lines[line_count][3];

    Node *nodes = NULL;

    for (size_t i = 0; i < line_count; i++) {
        parseLine(parsed_lines[i], data[i + 2]);
        Node newNode = {
            .val = strdup(parsed_lines[i][0]),
            .left_index = 0,
            .right_index = 0
        };
        arrput(nodes, newNode);
        if (strcmp(parsed_lines[i][0], "AAA") == 0) {
            curr_index = i;
        }
    }

    for (size_t i = 0; i < line_count; i++) {
        for (size_t j = 0; j < line_count; j++) {
            if (j != i && parsed_lines[j][0] != NULL) {
                if (strcmp(parsed_lines[i][1], parsed_lines[j][0]) == 0) {
                    nodes[i].left_index = j;
                }
                if (strcmp(parsed_lines[i][2], parsed_lines[j][0]) == 0) {
                    nodes[i].right_index = j;
                }
            }
        }
    }

    int count = 0;
    size_t key_index = 0;
    while (strcmp(nodes[curr_index].val, "ZZZ") != 0) {
        if (key[key_index] == 0) curr_index = nodes[curr_index].left_index;
        else curr_index = nodes[curr_index].right_index;
        key_index = (key_index + 1) % key_len;
        count++;
    }

    free(key);
    arrfree(nodes);

    printf("Part 1 Answer: %i\n", count);
}

unsigned long long gcd( unsigned long long a,  unsigned long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

unsigned long long getLcm( unsigned long long a,  unsigned long long b)
{
    assert(a > 0 && b > 0);
    return a * b / gcd(a, b);
}

void partTwo8(char **data, size_t data_size) {
    size_t key_len = strlen(data[0]);
    size_t *key = malloc(key_len * sizeof(size_t));
    for (size_t i = 0; i < key_len; i++) {
        key[i] = data[0][i] == 'R' ? 1 : 0;
    }

    size_t line_count = data_size - 2;
    char *parsed_lines[line_count][3];

    size_t *indicies = NULL;
    Node *nodes = NULL;

    for (size_t i = 0; i < line_count; i++) {
        parseLine(parsed_lines[i], data[i + 2]);
        Node newNode = {
            .val = strdup(parsed_lines[i][0]),
            .left_index = 0,
            .right_index = 0
        };
        arrput(nodes, newNode);
        if (parsed_lines[i][0][2] == 'A') {
            arrput(indicies, i);
        }
    }

    for (size_t i = 0; i < line_count; i++) {
        for (size_t j = 0; j < line_count; j++) {
            if (j != i && parsed_lines[j][0] != NULL) {
                if (strcmp(parsed_lines[i][1], parsed_lines[j][0]) == 0) {
                    nodes[i].left_index = j;
                }
                if (strcmp(parsed_lines[i][2], parsed_lines[j][0]) == 0) {
                    nodes[i].right_index = j;
                }
            }
        }
    }

    unsigned long long count = 1;
    unsigned long long lcm;
    size_t key_index = 0;
    size_t curr_index;
    size_t tracker_count = (size_t)arrlen(indicies);

    for (size_t i = 0; i < tracker_count; i++) {
        key_index = 0;
        curr_index = indicies[i];
        lcm = 0;
        while ((nodes[curr_index].val)[2] != 'Z') {
            if (key[key_index] == 0) curr_index = nodes[curr_index].left_index;
            else curr_index = nodes[curr_index].right_index;
            key_index = (key_index + 1) % key_len;
            lcm++;
        }
        count = getLcm(count, lcm);
    }
    printf("Part 2 Answer: %llu\n", count);

    free(key);
    arrfree(indicies);
    arrfree(nodes);
}

void dayEight(char **data, size_t data_size) {
    partOne8(data, data_size);
    partTwo8(data, data_size);
}

#endif // DAY_8
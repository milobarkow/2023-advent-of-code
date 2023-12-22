#include <ctype.h>
#include <errno.h>

#include "common.h"

// http://nothings.org/stb_ds/
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

void parseLine(char *parsed_line[], char* line) {
    const char dels[5] = " =,()";
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

int partOne(char **data, size_t data_size) {
    size_t key_len = strlen(data[0]);
    size_t key[key_len];
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

    arrfree(nodes);
    freeCharArray(data, data_size);
    return count;
}


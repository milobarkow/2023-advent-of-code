#include "common.h"

typedef struct Node {
    char *val;
    size_t id;
    struct Node *left;
    struct Node *right;
    struct Node *up;
    struct Node *down;
    float x;
    float y;
} Node;

typedef struct {
    Node *items;
    size_t count;
    size_t capacity;
} DA_NODE;

enum DIR {
    LEFT = 0,
    RIGHT = 1,
    UP = 2,
    DOWN = 3,
    START = 4,
};

size_t isValidLeft(Node node) {
    if (node.left) {
        if (strcmp(node.left->val, "S") == 0 || strcmp(node.left->val, "-") == 0 || strcmp(node.left->val, "L") == 0 || strcmp(node.left->val, "F") == 0) {
            return 1;
        }
    }
    return 0;
}

size_t isValidRight(Node node) {
    if (node.right) {
        if (strcmp(node.right->val, "S") == 0 || strcmp(node.right->val, "-") == 0 || strcmp(node.right->val, "7") == 0 || strcmp(node.right->val, "J") == 0) {
            return 1;
        }
    }
    return 0;
}

size_t isValidUp(Node node) {
    if (node.up) {
        if (strcmp(node.up->val, "S") == 0 || strcmp(node.up->val, "|") == 0 || strcmp(node.up->val, "F") == 0 || strcmp(node.up->val, "7") == 0) {
            return 1;
        }
    }
    return 0;
}

size_t isValidDown(Node node) {
    if (node.down) {
        if (strcmp(node.down->val, "S") == 0 || strcmp(node.down->val, "|") == 0 || strcmp(node.down->val, "L") == 0 || strcmp(node.down->val, "J") == 0) {
            return 1;
        }
    }
    return 0;
}

typedef struct NextNode {
    Node *next;
    enum DIR from;
} NextNode;

NextNode getNextNode(Node node, enum DIR came_from) {
    NextNode ret = {
        .next = NULL,
        .from = START,
    };
    if (strcmp(node.val, "S") == 0) {
        if (isValidLeft(node) > 0) {
            ret.next = node.left;
            ret.from = RIGHT;
        } else if (isValidRight(node) > 0) {
            ret.next = node.right;
            ret.from = LEFT;
        } else if (isValidUp(node) > 0) {
            ret.next = node.up;
            ret.from = DOWN;
        } else if (isValidDown(node) > 0) {
            ret.next = node.down;
            ret.from = UP;
        }
    } else if (strcmp(node.val, "-") == 0) {
        if (came_from == RIGHT && isValidLeft(node) > 0) {
            ret.next = node.left;
        } else if (isValidRight(node) > 0) {
            ret.next = node.right;
        }
        ret.from = came_from;
    } else if (strcmp(node.val, "|") == 0) {
        if (came_from == DOWN && isValidUp(node) > 0) {
            ret.next = node.up;
            ret.from = DOWN;
        } else if (isValidDown(node) > 0) {
            ret.next = node.down;
            ret.from = UP;
        }
    } else if (strcmp(node.val, "L") == 0) {
        if (came_from == UP && isValidRight(node) > 0) {
            ret.next = node.right;
            ret.from = LEFT;
        } else if (isValidUp(node) > 0) {
            ret.next = node.up;
            ret.from = DOWN;
        }
    } else if (strcmp(node.val, "J") == 0) {
        if (came_from == UP && isValidLeft(node) > 0) {
            ret.next = node.left;
            ret.from = RIGHT;
        } else if (isValidUp(node) > 0) {
            ret.next = node.up;
            ret.from = DOWN;
        }
    } else if (strcmp(node.val, "7") == 0) {
        if (came_from == LEFT && isValidDown(node) > 0) {
            ret.next = node.down;
            ret.from = UP;
        } else if (isValidLeft(node) > 0) {
            ret.next = node.left;
            ret.from = RIGHT;
        }
    } else if (strcmp(node.val, "F") == 0) {
        if (came_from == RIGHT && isValidDown(node) > 0) {
            ret.next = node.down;
            ret.from = UP;
        } else if (isValidRight(node) > 0) {
            ret.next = node.right;
            ret.from = LEFT;
        }
    }
    assert(ret.next != NULL);
    return ret;
}

size_t getMax(Node *n) {
    Node node = *n;
    size_t distance = 0;
    enum DIR from = START;
    while (strcmp(node.val, "S") != 0 || distance == 0) {
        NextNode nn = getNextNode(node, from);
        node = *(nn.next);
        from = nn.from;
        distance++;
    }
    return distance / 2;
}

void partOne10(char **data, size_t data_size) {
    size_t grid_w = strlen(data[0]);
    size_t grid_h = data_size;
    size_t node_count = grid_w * grid_h;

    DA_NODE nodes = {0};
    for (size_t i = 0; i < node_count; i++) {
        Node new_node = {
            .val = NULL,
            .left = NULL,
            .right = NULL,
            .up = NULL,
            .down = NULL,
        };
        da_append(&nodes, new_node);
    }
    size_t start_index;

    for (size_t i = 0; i < grid_h; i++) {
        for (size_t j = 0; j < grid_w; j++) {
            size_t n = grid_w * i + j;
            nodes.items[n].val = (char*)malloc(2);
            nodes.items[n].val[0] = data[i][j];
            nodes.items[n].val[1] = '\0';
            nodes.items[n].id = n;
            if (strcmp(nodes.items[n].val, "S") == 0) start_index = n;
            if (j > 0) {
                nodes.items[n].left = &nodes.items[grid_w * i + j - 1];
            }
            if (j < grid_w - 1) {
                nodes.items[n].right = &nodes.items[grid_w * i + j + 1];
            }
            if (i > 0) {
                nodes.items[n].up = &nodes.items[grid_w * (i - 1) + j];
            }
            if (i < grid_h - 1) {
                nodes.items[n].down = &nodes.items[grid_w * (i + 1) + j];
            }
        }
    }
    // printNodesInfo(nodes.items, arrlen(nodes.items), 1);

    size_t max = getMax(&(nodes.items[start_index]));
    printf("Part 1 Answer: %i\n", max);
}

void getLoopNodes(Node *n, DA_NODE *loop, size_t start_id) {
    Node node = *n;
    size_t distance = 0;
    enum DIR from = START;
    while (node.id != start_id || distance == 0) {
        da_append(loop, node);
        NextNode nn = getNextNode(node, from);
        node = *(nn.next);
        from = nn.from;
        distance++;
    }
}

size_t isInLoop(Node node, DA_NODE loop) {
    for (size_t n = 0; n < loop.count; n++) {
        if (node.x == loop.items[n].x && node.y == loop.items[n].y) return 1;
    }
    return 0;
}

void printGridWithLoop(DA_NODE nodes, DA_NODE loop, size_t w, size_t h) {
    size_t t = 0;
    for (size_t i = 0; i < h; i++) {
        for (size_t j = 0; j < w; j++) {
            if (isInLoop(nodes.items[t], loop)) {
                printf("%c", nodes.items[t].val[0]);
            } else printf(".");
            t++;
        }
        printf("\n");
    }
}

char getSReplacement(DA_NODE loop) {
    char l, r, u, d;
    char ret = '|';
    for (size_t i = 0; i < loop.count; i++) {
        if (strcmp(loop.items[i].val, "S") == 0) {

            if (loop.items[i].left && loop.items[i].right) {
                l = loop.items[i].left->val[0];
                r = loop.items[i].right->val[0];
                if ((l == 'F' || l == 'L' || l == '-') && (r == '7' || r == 'J' || r == '-')) {
                    ret = '-';
                }
            } else if (loop.items[i].up && loop.items[i].down) {
                u = loop.items[i].up->val[0];
                d = loop.items[i].down->val[0];
                if ((u == 'F' || u == '7' || u == '|') && (d == 'L' || d == 'J' || d == '|')) {
                    ret = '|';
                }
            } else if (loop.items[i].left && loop.items[i].down) {
                l = loop.items[i].left->val[0];
                d = loop.items[i].down->val[0];
                if ((l == 'F' || l == 'L' || l == '-') && (d == 'L' || d == 'J' || d == '|')) {
                    ret = '7';
                }
            } else if (loop.items[i].left && loop.items[i].up) {
                l = loop.items[i].left->val[0];
                u = loop.items[i].up->val[0];
                if ((l == 'F' || l == 'L' || l == '-') && (u == 'F' || u == '7' || u == '|')) {
                    ret = 'J';
                }
            } else if (loop.items[i].right && loop.items[i].up) {
                r = loop.items[i].right->val[0];
                u = loop.items[i].up->val[0];
                if ((r == 'J' || r == '7' || r == '-') && (u == 'F' || u == '7' || u == '|')) {
                    ret = 'L';
                }
            } else if (loop.items[i].right && loop.items[i].down) {
                r = loop.items[i].right->val[0];
                d = loop.items[i].down->val[0];
                if ((r == 'J' || r == '7' || r == '-') && (d == 'L' || d == 'J' || d == '|')) {
                    ret = 'F';
                }
            }
            if (ret != ' ') break;
        }
    }
    return ret;
}

void partTwo10(char **data, size_t data_size) {
    size_t grid_w = strlen(data[0]);
    size_t grid_h = data_size;
    size_t node_count = grid_w * grid_h;

    DA_NODE nodes = {0};
    for (size_t i = 0; i < node_count; i++) {
        Node new_node = {0};
        da_append(&nodes, new_node);
    }
    size_t start_index;

    for (size_t i = 0; i < grid_h; i++) {
        for (size_t j = 0; j < grid_w; j++) {
            size_t n = grid_w * i + j;
            nodes.items[n].val = (char*)malloc(2);
            nodes.items[n].val[0] = data[i][j];
            nodes.items[n].val[1] = '\0';
            nodes.items[n].id = n;
            nodes.items[n].x = j + 1;
            nodes.items[n].y = i + 1;
            if (strcmp(nodes.items[n].val, "S") == 0) start_index = n;
            if (j > 0) nodes.items[n].left = &nodes.items[grid_w * i + j - 1];
            if (j < grid_w - 1) nodes.items[n].right = &nodes.items[grid_w * i + j + 1];
            if (i > 0) nodes.items[n].up = &nodes.items[grid_w * (i - 1) + j];
            if (i < grid_h - 1) nodes.items[n].down = &nodes.items[grid_w * (i + 1) + j];
        }
    }

    DA_NODE loop = {0};
    getLoopNodes(&nodes.items[start_index], &loop, nodes.items[start_index].id);

    size_t count = 0;
    size_t tracker = 0;
    size_t in;
    char val[2];
    for (size_t i = 0; i < grid_h; i++) {
        in = 0;
        for (size_t j = 0; j < grid_w; j++) {
            if (isInLoop(nodes.items[tracker], loop) > 0) {
                val[0] = nodes.items[tracker].val[0];
                if (val[0] == 'S') val[0] = getSReplacement(loop);
                if (val[0] == '|') {
                    in = (in == 0) ? 1 : 0;
                } else {
                    if (val[0] == 'F') {
                        j++; tracker++;
                        while (nodes.items[tracker].val[0] == '-') {
                            j++; tracker++;
                        }
                        if (nodes.items[tracker].val[0] == 'J') {
                            in = (in == 0) ? 1 : 0;
                        }
                    } else if (val[0] == 'L') {
                        j++; tracker++;
                        while (nodes.items[tracker].val[0] == '-') {
                            j++; tracker++;
                        }
                        if (nodes.items[tracker].val[0] == '7') {
                            in = (in == 0) ? 1 : 0;
                        }
                    }
                }
            } else if (in == 1) count++;
            tracker++;
        }
    }

    printf("Part 2 Answer: %i\n", count);
}

void dayTen(char **data, size_t data_size) {
    partOne10(data, data_size);
    partTwo10(data, data_size);
}

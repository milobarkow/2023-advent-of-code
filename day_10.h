#ifndef DAY_10
#define DAY_10

#include "common.h"

typedef struct Cell {
    char *val;
    size_t id;
    struct Cell *left;
    struct Cell *right;
    struct Cell *up;
    struct Cell *down;
    float x;
    float y;
} Cell;

typedef struct {
    Cell *items;
    size_t count;
    size_t capacity;
} DA_CELL;

enum DIR {
    LEFT = 0,
    RIGHT = 1,
    UP = 2,
    DOWN = 3,
    START = 4,
};

size_t isValidLeft(Cell cell) {
    if (cell.left) {
        if (strcmp(cell.left->val, "S") == 0 || strcmp(cell.left->val, "-") == 0 || strcmp(cell.left->val, "L") == 0 || strcmp(cell.left->val, "F") == 0) {
            return 1;
        }
    }
    return 0;
}

size_t isValidRight(Cell cell) {
    if (cell.right) {
        if (strcmp(cell.right->val, "S") == 0 || strcmp(cell.right->val, "-") == 0 || strcmp(cell.right->val, "7") == 0 || strcmp(cell.right->val, "J") == 0) {
            return 1;
        }
    }
    return 0;
}

size_t isValidUp(Cell cell) {
    if (cell.up) {
        if (strcmp(cell.up->val, "S") == 0 || strcmp(cell.up->val, "|") == 0 || strcmp(cell.up->val, "F") == 0 || strcmp(cell.up->val, "7") == 0) {
            return 1;
        }
    }
    return 0;
}

size_t isValidDown(Cell cell) {
    if (cell.down) {
        if (strcmp(cell.down->val, "S") == 0 || strcmp(cell.down->val, "|") == 0 || strcmp(cell.down->val, "L") == 0 || strcmp(cell.down->val, "J") == 0) {
            return 1;
        }
    }
    return 0;
}

typedef struct NextCell {
    Cell *next;
    enum DIR from;
} NextCell;

NextCell getNextCell(Cell cell, enum DIR came_from) {
    NextCell ret = {
        .next = NULL,
        .from = START,
    };
    if (strcmp(cell.val, "S") == 0) {
        if (isValidLeft(cell) > 0) {
            ret.next = cell.left;
            ret.from = RIGHT;
        } else if (isValidRight(cell) > 0) {
            ret.next = cell.right;
            ret.from = LEFT;
        } else if (isValidUp(cell) > 0) {
            ret.next = cell.up;
            ret.from = DOWN;
        } else if (isValidDown(cell) > 0) {
            ret.next = cell.down;
            ret.from = UP;
        }
    } else if (strcmp(cell.val, "-") == 0) {
        if (came_from == RIGHT && isValidLeft(cell) > 0) {
            ret.next = cell.left;
        } else if (isValidRight(cell) > 0) {
            ret.next = cell.right;
        }
        ret.from = came_from;
    } else if (strcmp(cell.val, "|") == 0) {
        if (came_from == DOWN && isValidUp(cell) > 0) {
            ret.next = cell.up;
            ret.from = DOWN;
        } else if (isValidDown(cell) > 0) {
            ret.next = cell.down;
            ret.from = UP;
        }
    } else if (strcmp(cell.val, "L") == 0) {
        if (came_from == UP && isValidRight(cell) > 0) {
            ret.next = cell.right;
            ret.from = LEFT;
        } else if (isValidUp(cell) > 0) {
            ret.next = cell.up;
            ret.from = DOWN;
        }
    } else if (strcmp(cell.val, "J") == 0) {
        if (came_from == UP && isValidLeft(cell) > 0) {
            ret.next = cell.left;
            ret.from = RIGHT;
        } else if (isValidUp(cell) > 0) {
            ret.next = cell.up;
            ret.from = DOWN;
        }
    } else if (strcmp(cell.val, "7") == 0) {
        if (came_from == LEFT && isValidDown(cell) > 0) {
            ret.next = cell.down;
            ret.from = UP;
        } else if (isValidLeft(cell) > 0) {
            ret.next = cell.left;
            ret.from = RIGHT;
        }
    } else if (strcmp(cell.val, "F") == 0) {
        if (came_from == RIGHT && isValidDown(cell) > 0) {
            ret.next = cell.down;
            ret.from = UP;
        } else if (isValidRight(cell) > 0) {
            ret.next = cell.right;
            ret.from = LEFT;
        }
    }
    assert(ret.next != NULL);
    return ret;
}

size_t getMax(Cell * n) {
    Cell cell = *n;
    size_t distance = 0;
    enum DIR from = START;
    while (strcmp(cell.val, "S") != 0 || distance == 0) {
        NextCell nn = getNextCell(cell, from);
        cell = *(nn.next);
        from = nn.from;
        distance++;
    }
    return distance / 2;
}

void partOne10(char **data, size_t data_size) {
    size_t grid_w = strlen(data[0]);
    size_t grid_h = data_size;
    size_t cell_count = grid_w * grid_h;

    DA_CELL cells = {0};
    for (size_t i = 0; i < cell_count; i++) {
        Cell new_cell = {
            .val = NULL,
            .left = NULL,
            .right = NULL,
            .up = NULL,
            .down = NULL,
        };
        da_append(&cells, new_cell);
    }
    size_t start_index;

    for (size_t i = 0; i < grid_h; i++) {
        for (size_t j = 0; j < grid_w; j++) {
            size_t n = grid_w * i + j;
            cells.items[n].val = (char*)malloc(2);
            cells.items[n].val[0] = data[i][j];
            cells.items[n].val[1] = '\0';
            cells.items[n].id = n;
            if (strcmp(cells.items[n].val, "S") == 0) start_index = n;
            if (j > 0) {
                cells.items[n].left = &cells.items[grid_w * i + j - 1];
            }
            if (j < grid_w - 1) {
                cells.items[n].right = &cells.items[grid_w * i + j + 1];
            }
            if (i > 0) {
                cells.items[n].up = &cells.items[grid_w * (i - 1) + j];
            }
            if (i < grid_h - 1) {
                cells.items[n].down = &cells.items[grid_w * (i + 1) + j];
            }
        }
    }
    // printCellsInfo(cells.items, arrlen(cells.items), 1);

    size_t max = getMax(&(cells.items[start_index]));
    printf("Part 1 Answer: %i\n", max);
}

void getLoopCells(Cell * n, DA_CELL * loop, size_t start_id) {
    Cell cell = *n;
    size_t distance = 0;
    enum DIR from = START;
    while (cell.id != start_id || distance == 0) {
        da_append(loop, cell);
        NextCell nn = getNextCell(cell, from);
        cell = *(nn.next);
        from = nn.from;
        distance++;
    }
}

size_t isInLoop(Cell cell, DA_CELL loop) {
    for (size_t n = 0; n < loop.count; n++) {
        if (cell.x == loop.items[n].x && cell.y == loop.items[n].y) return 1;
    }
    return 0;
}

void printGridWithLoop(DA_CELL cells, DA_CELL loop, size_t w, size_t h) {
    size_t t = 0;
    for (size_t i = 0; i < h; i++) {
        for (size_t j = 0; j < w; j++) {
            if (isInLoop(cells.items[t], loop)) {
                printf("%c", cells.items[t].val[0]);
            } else printf(".");
            t++;
        }
        printf("\n");
    }
}

char getSReplacement(DA_CELL loop) {
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
    size_t cell_count = grid_w * grid_h;

    DA_CELL cells = {0};
    for (size_t i = 0; i < cell_count; i++) {
        Cell new_cell = {0};
        da_append(&cells, new_cell);
    }
    size_t start_index;

    for (size_t i = 0; i < grid_h; i++) {
        for (size_t j = 0; j < grid_w; j++) {
            size_t n = grid_w * i + j;
            cells.items[n].val = (char*)malloc(2);
            cells.items[n].val[0] = data[i][j];
            cells.items[n].val[1] = '\0';
            cells.items[n].id = n;
            cells.items[n].x = j + 1;
            cells.items[n].y = i + 1;
            if (strcmp(cells.items[n].val, "S") == 0) start_index = n;
            if (j > 0) cells.items[n].left = &cells.items[grid_w * i + j - 1];
            if (j < grid_w - 1) cells.items[n].right = &cells.items[grid_w * i + j + 1];
            if (i > 0) cells.items[n].up = &cells.items[grid_w * (i - 1) + j];
            if (i < grid_h - 1) cells.items[n].down = &cells.items[grid_w * (i + 1) + j];
        }
    }

    DA_CELL loop = {0};
    getLoopCells(&cells.items[start_index], &loop, cells.items[start_index].id);

    size_t count = 0;
    size_t tracker = 0;
    size_t in;
    char val[2];
    for (size_t i = 0; i < grid_h; i++) {
        in = 0;
        for (size_t j = 0; j < grid_w; j++) {
            if (isInLoop(cells.items[tracker], loop) > 0) {
                val[0] = cells.items[tracker].val[0];
                if (val[0] == 'S') val[0] = getSReplacement(loop);
                if (val[0] == '|') {
                    in = (in == 0) ? 1 : 0;
                } else {
                    if (val[0] == 'F') {
                        j++; tracker++;
                        while (cells.items[tracker].val[0] == '-') {
                            j++; tracker++;
                        }
                        if (cells.items[tracker].val[0] == 'J') {
                            in = (in == 0) ? 1 : 0;
                        }
                    } else if (val[0] == 'L') {
                        j++; tracker++;
                        while (cells.items[tracker].val[0] == '-') {
                            j++; tracker++;
                        }
                        if (cells.items[tracker].val[0] == '7') {
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

#endif // DAY_10
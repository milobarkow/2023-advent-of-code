#ifndef DAY_11
#define DAY_11

#include "common.h"

#include <math.h>
#include <inttypes.h>

typedef struct {
    size_t *items;
    size_t count;
    size_t capacity;
} DA_UI;

typedef struct {
    char *items;
    size_t count;
    size_t capacity;
} DA_CHAR;

typedef struct Point {
    size_t x;
    size_t y;
    size_t id;
} Point;

typedef struct Pair {
    size_t index_a;
    size_t index_b;
} Pair;

size_t getDistanceBetweenPair(size_t x1, size_t y1, size_t x2, size_t y2) {
    size_t d = (size_t)((fabs(((float)x1) - ((float)x2))) + fabs(((float)y1) - ((float)y2)));
    return d;
}

void partOne11(char **data, size_t data_size) {
    size_t space_be_w = strlen(data[0]);
    size_t space_be_h = data_size;

    char space_be[space_be_h * space_be_w];
    DA_UI rows_expanded = {0};
    DA_UI cols_expanded = {0};

    size_t point_count = 0;
    size_t in_rc = 0;
    for (size_t i = 0; i < space_be_h ; i++) {
        in_rc = 0;
        for (size_t j = 0; j < space_be_w; j++) {
            space_be[i * space_be_w + j] = data[i][j];
            if (data[i][j] != '.') {
                in_rc = 1;
                point_count++;
            }
        }
        if (in_rc == 0) {
            da_append(&rows_expanded, i + rows_expanded.count);
        }
    }

    in_rc = 0;
    for (size_t i = 0; i < space_be_w; i++) {
        in_rc = 0;
        for (size_t j = 0; j < space_be_h ; j++) {
            if (data[j][i] != '.') {
                in_rc = 1;
            }
        }
        if (in_rc == 0) {
            da_append(&cols_expanded, i + cols_expanded.count);
        }
    }

    size_t space_w = space_be_w + cols_expanded.count;
    size_t space_h = space_be_h  + rows_expanded.count;
    char space[space_h][space_w];
    for (size_t i = 0; i < space_h; i++) {
        for (size_t j = 0; j < space_w; j++) {
            space[i][j] = '.';
        }
    }

    Point points[point_count];
    size_t point_tracker = 0;
    size_t tracker = 0;
    size_t expanded_row_t = 0;
    size_t expanded_col_t = 0;
    for (size_t i = 0; i < space_h; i++) {
        if (i == rows_expanded.items[expanded_row_t]) {
            expanded_row_t++;
        } else {
            expanded_col_t = 0;
            for (size_t j = 0; j < space_w; j++) {
                if (j == cols_expanded.items[expanded_col_t]) {
                    expanded_col_t++;
                    j++;
                    space[i][j] = space_be[tracker++];
                } else {
                    assert(i < space_h && j < space_w);
                    space[i][j] = space_be[tracker++];
                    if (space[i][j] == '#') {
                        struct Point p = {
                            .x = j,
                            .y = i,
                            .id = point_tracker + 1,
                        };
                        points[point_tracker++] = p;
                    }
                }
            }
        }
    }

    size_t pair_size = point_count * (point_count - 1) / 2;
    Pair pairs[pair_size];

    size_t pairs_added = 0;
    size_t in_pairs = 0;
    size_t count = 0;
    for (size_t i = 0 ; i < point_count; i++) {
        for (size_t j = 0; j < point_count; j++) {
            if (i != j) {
                in_pairs = 0;
                for (size_t k = 0; k < pairs_added; k++) {
                    if ((points[pairs[k].index_a].id == points[i].id && points[pairs[k].index_b].id == points[j].id) ||
                            (points[pairs[k].index_b].id == points[i].id && points[pairs[k].index_a].id == points[j].id)) {
                        in_pairs = 1;
                        break;
                    }
                }
                if (in_pairs == 0) {
                    pairs[pairs_added].index_a = i;
                    pairs[pairs_added].index_b = j;

                    count += getDistanceBetweenPair(points[i].x, points[i].y, points[j].x, points[j].y);
                    pairs_added++;
                }
            }
        }
    }

    printf("Part 1 Answer: %i\n", count);
}

size_t inExpanded(size_t k, DA_UI expanded) {
    for (size_t i = 0; i < expanded.count; i++) {
        if (expanded.items[i] == k) return 1;
    }
    return 0;
}

void partTwo11(char **data, size_t data_size) {
    const size_t MULT = 1000000;
    size_t space_w = strlen(data[0]);
    size_t space_h = data_size;

    DA_UI rows_expanded = {0};
    DA_UI cols_expanded = {0};

    size_t point_count = 0;
    size_t in_rc = 0;
    for (size_t i = 0; i < space_h ; i++) {
        in_rc = 0;
        for (size_t j = 0; j < space_w; j++) {
            if (data[i][j] != '.') {
                in_rc = 1;
                point_count++;
            }
        }
        if (in_rc == 0) {
            da_append(&rows_expanded, i);
        }
    }

    in_rc = 0;
    for (size_t i = 0; i < space_w; i++) {
        in_rc = 0;
        for (size_t j = 0; j < space_h ; j++) {
            if (data[j][i] != '.') {
                in_rc = 1;
            }
        }
        if (in_rc == 0) {
            da_append(&cols_expanded, i);
        }
    }

    Point points[point_count];
    size_t point_tracker = 0;
    for (size_t i = 0; i < space_h; i++) {
        for (size_t j = 0; j < space_w; j++) {
            if (data[i][j] == '#') {
                struct Point p = {
                    .x = j,
                    .y = i,
                    .id = point_tracker + 1,
                };
                points[point_tracker++] = p;
            }
        }
    }

    size_t pair_size = point_count * (point_count - 1) / 2;
    Pair pairs[pair_size];

    size_t pairs_added = 0;
    size_t in_pairs = 0;
    int64_t count = 0;
    size_t x1 = 0;
    size_t x2 = 0;
    size_t y1 = 0;
    size_t y2 = 0;
    for (size_t i = 0 ; i < point_count; i++) {
        for (size_t j = 0; j < point_count; j++) {
            if (i != j) {
                in_pairs = 0;
                for (size_t k = 0; k < pairs_added; k++) {
                    if ((points[pairs[k].index_a].id == points[i].id && points[pairs[k].index_b].id == points[j].id) ||
                            (points[pairs[k].index_b].id == points[i].id && points[pairs[k].index_a].id == points[j].id)) {
                        in_pairs = 1;
                        break;
                    }
                }
                if (in_pairs == 0) {
                    pairs[pairs_added].index_a = i;
                    pairs[pairs_added].index_b = j;
                    pairs_added++;
                    if (points[i].y < points[j].y) {
                        y1 = points[i].y;
                        y2 = points[j].y;
                    } else {
                        y1 = points[j].y;
                        y2 = points[i].y;
                    }
                    for (size_t n = y1; n < y2; n++) {
                        if (inExpanded(n, rows_expanded) > 0) {
                            count += MULT;
                        } else count++;
                    }

                    if (points[i].x < points[j].x) {
                        x1 = points[i].x;
                        x2 = points[j].x;
                    } else {
                        x1 = points[j].x;
                        x2 = points[i].x;
                    }
                    for (size_t n = x1; n < x2; n++) {
                        if (inExpanded(n, cols_expanded) > 0) {
                            count += MULT;
                        } else count++;
                    }
                }
            }
        }
    }

    printf("Part 2 Answer: %" PRIu64 "\n", count);
}

void dayElleven(char **data, size_t data_size) {
    partOne11(data, data_size);
    partTwo11(data, data_size);
}

#endif
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node {
    char val;
    size_t id;
    struct Node *left;
} Node;

typedef struct {
    Node *items;
    size_t count;
    size_t capacity;
} DA;

#define DA_INIT_CAP 256
#define da_append(da, item)                                                          \
    do {                                                                             \
        if ((da)->count >= (da)->capacity) {                                         \
            (da)->capacity = (da)->capacity == 0 ? DA_INIT_CAP : (da)->capacity*2;   \
            (da)->items = realloc((da)->items, (da)->capacity*sizeof(*(da)->items)); \
            assert((da)->items != NULL && "Buy more RAM lol");                       \
        }                                                                            \
                                                                                     \
        (da)->items[(da)->count++] = (item);                                         \
    } while (0)

int main(void) {

    DA da = {0};
    Node n1 = {
        .val = 'a',
        .id = 1,
        .left = NULL,
    };
    Node n2 = {
        .val = 'b',
        .id = 1,
        .left = NULL,
    };
    da_append(&da, n1);
    da_append(&da, n2);
    for (size_t i = 1; i < da.count; i++) {
        da.items[i].left = &da.items[i - 1];
        da.items[i].has_left = 1;
    }
    for (size_t i = 0; i < da.count; i++) {
        if (da.items[i].left != NULL) printf("%c\n", da.items[i].left->val);
        else printf("NULL\n");
    }
    printf("count=%i, cap=%i", da.count, da.capacity);

    return 1;
}
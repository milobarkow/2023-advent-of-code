#include <ctype.h>
#include <errno.h>

#include "common.h"

#define HAND_SIZE 5

enum Case {
    HIGH = 0,
    ONE_PAIR = 1,
    TWO_PAIR = 2,
    THREE_KIND = 3,
    FULL_HOUSE = 4,
    FOUR_KIND = 5,
    FIVE_KIND = 6
};

typedef struct {
    char *cards;
    enum Case c;
    int val;
} Hand;

int getCardValue(char a, size_t part) {
    if (isdigit(a)) return atoi(&a);
    else if (a == 'A') return 14;
    else if (a == 'K') return 13;
    else if (a == 'Q') return 12;
    else if (a == 'J') {
        if (part == 1) return 11;
        else if (part == 2) return 1;
    } else if (a == 'T') return 10;
    return -1;
}

void swap(Hand hands[], int j) {
    Hand temp = hands[j];
    hands[j] = hands[j + 1];
    hands[j + 1] = temp;

}

void sort(Hand hands[], int size, size_t part) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (hands[j].c > hands[j + 1].c) {
                swap(hands, j);
            } else if (hands[j].c == hands[j + 1].c) {
                int k = 0;
                while (hands[j].cards[k] == hands[j + 1].cards[k]) k++;
                if (getCardValue(hands[j].cards[k], part) >  getCardValue(hands[j + 1].cards[k], part)) {
                    swap(hands, j);
                }
            }
        }
    }
}

int checkSpecialCase(const char *hand, enum Case sc) {
    int counts[13] = {0};
    int pairCount = 0;
    int tripleCount = 0;
    for (int i = 0; i < HAND_SIZE; i++) {
        char card = hand[i];
        int rank;

        if (card >= '2' && card <= '9') {
            rank = card - '0';
        } else {
            switch (card) {
            case 'T': rank = 10; break;
            case 'J': rank = 11; break;
            case 'Q': rank = 12; break;
            case 'K': rank = 13; break;
            case 'A': rank = 14; break;
            default: return 0;
            }
        }
        counts[rank - 2]++;
        if (counts[rank - 2] == 2) {
            pairCount++;
        } else if (counts[rank - 2] == 3) {
            tripleCount++;
            pairCount--;
        }
    }

    if (sc == FULL_HOUSE) return pairCount == 1 && tripleCount == 1;
    return pairCount == 2;
}

void partOne(char **data, size_t data_size) {
    Hand tracker[data_size];
    for (size_t i = 0; i < data_size; i++) {
        tracker[i].cards = data[i];
        tracker[i].val = atoi(strchr(data[i], ' ') + 1);
        tracker[i].c = HIGH;
    }

    size_t card_count_new = 1;
    size_t card_count_old = 1;
    for (size_t i = 0; i < data_size; i++) {
        if (checkSpecialCase(tracker[i].cards, FULL_HOUSE)) tracker[i].c = FULL_HOUSE;
        else if (checkSpecialCase(tracker[i].cards, TWO_PAIR)) tracker[i].c = TWO_PAIR;
        else {
            card_count_old = 0;
            for (size_t x = 0; x < HAND_SIZE; x++) {
                card_count_new = 0;
                for (size_t y = 0; y < HAND_SIZE; y++) {
                    if (tracker[i].cards[x] == tracker[i].cards[y]) {
                        card_count_new++;
                    }
                }
                if (card_count_new > card_count_old) card_count_old = card_count_new;
            }
            if (card_count_old == 2) tracker[i].c = ONE_PAIR;
            else if (card_count_old == 3) tracker[i].c = THREE_KIND;
            else if (card_count_old == 4) tracker[i].c = FOUR_KIND;
            else if (card_count_old == 5) tracker[i].c = FIVE_KIND;
        }
    }

    sort(tracker, sizeof(tracker) / sizeof(tracker[0]), 1);

    int count = 0;
    for (size_t i = 0; i < data_size; i++) {
        count += tracker[i].val * (i + 1);
    }
    return count;
}

int getJokerCount(const char *hand) {
    int count = 0;
    for (int i = 0; i < HAND_SIZE; i++) {
        if (hand[i] == 'J') count++;
    }
    printf("Part 1 Answer: %i\n", count);
}

void partTwo(char **data, size_t data_size) {
    Hand tracker[data_size];
    for (size_t i = 0; i < data_size; i++) {
        tracker[i].cards = data[i];
        tracker[i].val = atoi(strchr(data[i], ' ') + 1);
        tracker[i].c = HIGH;
    }

    size_t card_count_new = 0;
    size_t card_count_old = 0;
    int jokerCount;
    for (size_t i = 0; i < data_size; i++) {
        jokerCount = getJokerCount(tracker[i].cards);
        if (checkSpecialCase(tracker[i].cards, FULL_HOUSE)) {
            if (jokerCount == 0) tracker[i].c = FULL_HOUSE;
            else if (jokerCount == 2 || jokerCount == 3) tracker[i].c = FIVE_KIND;
        } else if (checkSpecialCase(tracker[i].cards, TWO_PAIR)) {
            if (jokerCount == 0) tracker[i].c = TWO_PAIR;
            else if (jokerCount == 1 ) tracker[i].c = FULL_HOUSE;
            else if (jokerCount == 2) tracker[i].c = FOUR_KIND;
        } else {
            card_count_old = 0;
            for (size_t x = 0; x < HAND_SIZE; x++) {
                card_count_new = 0;
                for (size_t y = 0; y < HAND_SIZE; y++) {
                    if (tracker[i].cards[x] == tracker[i].cards[y]) {
                        card_count_new++;
                    }
                }
                if (card_count_new > card_count_old) card_count_old = card_count_new;
            }
            if (card_count_old == 1) {
                if (jokerCount == 0) tracker[i].c = HIGH;
                else if (jokerCount == 1) tracker[i].c = ONE_PAIR;
            } else if (card_count_old == 2) {
                if (jokerCount == 0) tracker[i].c = ONE_PAIR;
                else if (jokerCount == 1 || jokerCount == 2) tracker[i].c = THREE_KIND;
            } else if (card_count_old == 3) {
                if (jokerCount == 0) tracker[i].c = THREE_KIND;
                else if (jokerCount == 1 || jokerCount == 3) tracker[i].c = FOUR_KIND;
            } else if (card_count_old == 4) {
                if (jokerCount == 0) tracker[i].c = FOUR_KIND;
                else if (jokerCount == 1 || jokerCount == 4) tracker[i].c = FIVE_KIND;
            } else if (card_count_old == 5) tracker[i].c = FIVE_KIND;
        }
    }

    sort(tracker, sizeof(tracker) / sizeof(tracker[0]), 2);

    int count = 0;
    for (size_t i = 0; i < data_size; i++) {
        count += tracker[i].val * (i + 1);
        printf("hand=%s, rank=%i\n", tracker[i].cards, tracker[i].c);
    }
    printf("Part 2 Answer: %i\n", count);
}
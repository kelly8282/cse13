#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "haeisqn:p:r:"
#define SEED    13371453
#define SIZE    100
typedef enum { Insertion, Heap, Quick, Shell, Help, Nothing } Sort;

int main(int argc, char **argv) {
    Set meow = empty_set();
    int opt = 0;
    uint32_t s = SEED;
    uint32_t si = SIZE;
    uint32_t pop = SIZE;
    uint32_t temp;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        default: meow = insert_set(Nothing, meow); break;
        case 'a':
            meow = insert_set(Heap, meow);
            meow = insert_set(Quick, meow);
            meow = insert_set(Insertion, meow);
            meow = insert_set(Shell, meow);
            break;
        case 'e': meow = insert_set(Heap, meow); break;

        case 'h': meow = insert_set(Help, meow); break;
        case 'i': meow = insert_set(Insertion, meow); break;
        case 'n':
            temp = atoi(optarg);
            if (temp >= 0 && temp <= UINT_MAX) {
                pop = temp;
                break;
            } else {
                pop = SIZE;
                break;
            }
        case 'p':
            temp = atoi(optarg);
            if (temp >= 0 && temp <= UINT_MAX) {
                si = temp;
                break;
            } else {
                si = SIZE;
                break;
            }
        case 'r':
            temp = atoi(optarg);
            if (temp >= 0 && temp <= UINT_MAX) {
                s = temp;
                break;
            } else {
                s = SEED;
                break;
            }
        case 'q': meow = insert_set(Quick, meow); break;
        case 's': meow = insert_set(Shell, meow); break;
        }
    }
    srand(s);
    uint32_t bitmask = 0x3FFFFFFF;
    uint32_t *A = (uint32_t *) calloc(pop, sizeof(uint32_t));
    uint32_t *one = (uint32_t *) calloc(pop, sizeof(uint32_t));
    uint32_t *two = (uint32_t *) calloc(pop, sizeof(uint32_t));
    uint32_t *three = (uint32_t *) calloc(pop, sizeof(uint32_t));
    uint32_t *four = (uint32_t *) calloc(pop, sizeof(uint32_t));
    Stats stats;
    stats.moves = 0;
    stats.compares = 0;

    for (uint32_t i = 0; i < pop; i++) {
        A[i] = (random() & bitmask);
        one[i] = A[i];
        two[i] = A[i];
        three[i] = A[i];
        four[i] = A[i];
    }

    if (member_set(Nothing, meow) || member_set(Help, meow) || meow == empty_set()) {
        if (meow == empty_set()) {
            printf("Select at least one sort to perform.\n");
        }
        printf("SYNOPSIS\n");
        printf("   A collection of comparion-based sorting algorithms.\n\n");
        printf("USAGE\n");
        printf("   /home/kelly8282828/resources/asgn3/sorting [-haeisqn:p:r:] [-n length] [-p "
               "elements] [-r seed]\n\n");
        printf("OPTIONS\n");
        printf("   -h              display program help and usage.\n");
        printf("   -a              enable all sorts.\n");
        printf("   -e              enable Heap Sort.\n");
        printf("   -i              enable Insertion Sort.\n");
        printf("   -s              enable Shell Sort.\n");
        printf("   -q              enable Quick Sort.\n");
        printf("   -n length       specify number of array elements (default: 100).\n");
        printf("   -p elements     specify number of elements to print (default: 100).\n");
        printf("   -r seed         specify random seed (default: 13371453).\n");
    }

    if (member_set(Heap, meow)) {
        reset(&stats);
        heap_sort(&stats, one, pop);
        printf(
            "Heap Sort, %u elements, %lu moves, %lu compares\n", pop, stats.moves, stats.compares);
        uint32_t tem = 0;
        uint32_t gr = si;
        if (gr > pop) {
            gr = pop;
        }
        for (uint32_t i = 0; i < gr; i++) {
            printf("%13" PRIu32, one[i]);
            tem = tem + 1;
            if (tem % 5 == 0) {
                printf("\n");
                tem = 0;
            }
        }
    }
    free(one);
    if (member_set(Shell, meow)) {
        reset(&stats);
        shell_sort(&stats, two, pop);
        printf(
            "Shell Sort, %u elements, %lu moves, %lu compares\n", pop, stats.moves, stats.compares);
        uint32_t tem = 0;
        uint32_t gr = si;
        if (gr > pop) {
            gr = pop;
        }
        for (uint32_t i = 0; i < gr; i++) {
            printf("%13" PRIu32, two[i]);
            tem = tem + 1;
            if (tem % 5 == 0) {
                printf("\n");
                tem = 0;
            }
        }
    }
    free(two);
    if (member_set(Insertion, meow)) {
        reset(&stats);
        insertion_sort(&stats, three, pop);
        printf("Insertion Sort, %u elements, %lu moves, %lu compares\n", pop, stats.moves,
            stats.compares);
        uint32_t tem = 0;
        uint32_t gr = si;
        if (gr > pop) {
            gr = pop;
        }
        for (uint32_t i = 0; i < gr; i++) {
            printf("%13" PRIu32, three[i]);
            tem = tem + 1;
            if (tem % 5 == 0) {
                printf("\n");
                tem = 0;
            }
        }
    }
    free(three);
    if (member_set(Quick, meow)) {
        reset(&stats);
        quick_sort(&stats, four, pop);
        printf(
            "Quick Sort, %u elements, %lu moves, %lu compares\n", pop, stats.moves, stats.compares);
        uint32_t tem = 0;
        uint32_t gr = si;
        if (gr > pop) {
            gr = pop;
        }
        for (uint32_t i = 0; i < gr; i++) {
            printf("%13" PRIu32, four[i]);
            tem = tem + 1;
            if (tem % 5 == 0) {
                printf("\n");
                tem = 0;
            }
        }
    }
    free(four);
    free(A);
    return 0;
}

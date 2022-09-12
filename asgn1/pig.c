#include "names.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    typedef enum { SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER } Position;
    const Position pig[7] = { SIDE, SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER, JOWLER };
    int players = 0;
    int64_t seed = 0;
    printf("How many players? ");
    if (scanf("%d", &players) <= 0) {
        fprintf(stderr, "Invalid numbers of players. Using 2 instead. \n");
        players = 2;
    }
    if (players < 2 || players > 10) {
        fprintf(stderr, "Invalid numbers of players. Using 2 instead. \n");
        players = 2;
    }
    printf("Random seed: ");
    if (scanf("%ld", &seed) <= 0) {
        seed = 2021;
        fprintf(stderr, "Invalid random seed. Using 2021 instead. \n");
    }
    if (seed < 0 || seed > RAND_MAX) {
        fprintf(stderr, "Invalid random seed. Using 2021 instead. \n");
        seed = 2021;
    }
    srandom(seed);
    int points[players];
    for (int i = 0; i < players; i++) {
        int zero = 0;
        points[i] = zero;
    }
    int top = 0;
    int winner = 0;
    int stop = 0;
    while (top < 100) {
        for (int i = 0; i < players; i++) {
            int cont = 0;
            printf("%s rolls the pig...", names[i]);
            while (cont != 1) {
                int dice = rand();
                dice = dice % 7;
                if (pig[dice] == SIDE) {
                    printf(" pig lands on side");
                    cont = 1;
                }
                if (pig[dice] == RAZORBACK) {
                    printf(" pig lands on back");
                    points[i] = points[i] + 10;
                }
                if (pig[dice] == TROTTER) {
                    printf(" pig lands upright");
                    points[i] = points[i] + 10;
                }
                if (pig[dice] == SNOUTER) {
                    printf(" pig lands on snout");
                    points[i] = points[i] + 15;
                }
                if (pig[dice] == JOWLER) {
                    printf(" pig lands on ear");
                    points[i] = points[i] + 5;
                }
                if (points[i] >= 100) {
                    winner = i;
                    stop = 1;
                    break;
                }
            }
            printf("\n");
            if (stop == 1) {
                break;
            }
        }
        for (int i = 0; i < players; i++) {
            if (points[i] > top) {
                top = points[i];
                winner = i;
            }
        }
    }
    fprintf(stdout, "%s wins with %d points!\n", names[winner], top);
    return 0;
}

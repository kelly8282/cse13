#include "mathlib.h"

#include <stdio.h>

static int counter = 0;

double pi_bbp(void) {
    counter = 0;
    double total = 0;
    double start = 0;
    double hold = 0;
    int run = 0;
    while (run == 0) {
        double right = (start * (120 * start + 151) + 47)
                       / (start * (start * (start * (512 * start + 1024) + 712) + 194) + 15);
        double left = 16;
        if (start == 0) {
            left = 1;
        } else {
            for (int i = 0; i < start - 1; i++) {
                left = left * 16;
            }
        }
        double temp = right * (1 / left);
        if (absolute(temp - hold) < EPSILON) {
            run = 1;
        } else {
            total = total + temp;
            start = start + 1;
            counter = counter + 1;
            hold = temp;
        }
    }
    return total;
}

int pi_bbp_terms(void) {
    return counter;
}

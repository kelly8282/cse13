#include "mathlib.h"

#include <stdio.h>

static int counter = 0;

double pi_euler(void) {
    counter = 0;
    double total = 0;
    double start = 1;
    double hold = 0;
    int run = 0;
    while (run == 0) {
        double temp = 1 / (start * start);
        if (temp < EPSILON) {
            run = 1;
        } else {
            hold = temp;
            total = total + temp;
            start = start + 1;
            counter = counter + 1;
        }
    }
    total = sqrt_newton(6 * total);
    return total;
}

int pi_euler_terms(void) {
    return counter;
}

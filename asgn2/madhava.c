#include "mathlib.h"

#include <stdio.h>

static int counter = 0;

double pi_madhava(void) {
    counter = 0;
    double total = 0;
    double start = 0;
    int run = 0;
    double hold = 0;
    while (run == 0) {
        double top = -3;
        if (start == 0) {
            top = 1;
        } else {
            for (int i = 0; i < start - 1; i++) {
                top = top * -3;
            }
        }
        double temp = (1 / (top * (2 * start + 1)));
        if (absolute(temp - hold) < EPSILON) {
            run = 1;
        } else {
            hold = temp;
            total = total + temp;
            counter = counter + 1;
            start = start + 1;
        }
    }
    double a = sqrt_newton(12);
    return a * total;
}

int pi_madhava_terms(void) {
    return counter;
}

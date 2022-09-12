#include "mathlib.h"

#include <stdio.h>

static int counter = 1;

double pi_viete(void) {
    counter = 0;
    double total = sqrt_newton(2) / 2;
    double old = sqrt_newton(2);
    int run = 0;
    while (run == 0) {
        double new = sqrt_newton(old + 2);
        if (absolute(new - old) < EPSILON) {
            run = 1;
        } else {
            total = total * (new / 2);
            old = new;
            counter = counter + 1;
        }
    }
    total = 2 / total;
    return total;
}

int pi_viete_factors(void) {
    return counter;
}

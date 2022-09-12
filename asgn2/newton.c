#include "mathlib.h"

#include <stdio.h>

static int counter = 0;

double sqrt_newton(double x) {
    counter = 0;
    double z = 0.0;
    double y = 1.0;
    while (absolute(y - z) > EPSILON) {
        z = y;
        y = .5 * (z + x / z);
        counter = counter + 1;
    }
    return y;
}

int sqrt_newton_iters(void) {
    return counter;
}

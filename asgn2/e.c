#include "mathlib.h"

#include <stdio.h>

static int counter = 0;

double e(void) {
    counter = 0;
    double total = 0;
    double start = 0;
    int run = 0;
    double hold = 0;
    while (run == 0) {
        double temp = 1;
        if (start == 0) {
            temp = 1;
        } else {
            for (int i = 1; i < start + 1; i++) {
                temp = temp * i;
            }
        }
        double calculate = 1 / temp;
        if (absolute(calculate - hold) < EPSILON && (calculate - hold) != 0) {
            run = 1;
        } else {
            hold = calculate;
            total = total + calculate;
            counter = counter + 1;
            start = start + 1;
        }
    }
    return total;
}

int e_terms(void) {
    return counter;
}

//int main(){
//	printf("%f\n", e());
//	printf("%d", e_terms());
//}

#include "shell.h"

#include "set.h"
#include "stats.h"

#include <inttypes.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

void shell_sort(Stats *stats, uint32_t *A, uint32_t n) {
    for (uint32_t i = log(3 + 2 * n) / log(3); i > 0; i--) {
        uint32_t gap = floor((pow(3, i) - 1) / 2);
        for (uint32_t j = gap; j < n; j++) {
            uint32_t k = j;
            uint32_t temp = move(stats, A[j]);
            while (k >= gap && cmp(stats, temp, A[k - gap]) == -1) {
                A[k] = move(stats, A[k - gap]);
                k = k - gap;
            }
            A[k] = move(stats, temp);
        }
    }
}

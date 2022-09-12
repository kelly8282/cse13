#include "mathlib.h"

#include <math.h>
#include <stdio.h>
#include <unistd.h>

#define OPTIONS "aebmrvnsh"

int main(int argc, char **argv) {
    int opt = 0;
    int h, s, r, z, m, a, b, v, n = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        default: h = 1; break;
        case 'h': h = 1; break;
        case 's': s = 1; break;
        case 'r': r = 1; break;
        case 'e': z = 1; break;
        case 'm': m = 1; break;
        case 'a': a = 1; break;
        case 'b': b = 1; break;
        case 'v': v = 1; break;
        case 'n': n = 1; break;
        }
    }
    if (h == 1) {
        printf("SYNOPSIS\n   A test harness for the small numerical library.\n\nUSAGE\n   "
               "./mathlib-test [-aebmrvnsh]\n\nOPTIONS\n  -a   Runs all tests.\n  -e   Runs e "
               "test.\n  -b   Runs BBP pi test.\n  -m   Runs Madhava pi test.\n  -r   Runs Euler "
               "pi test.\n  -v   Runs Viete pi test.\n  -n   Runs Newton square root tests.\n  -s  "
               " Print verbose statistics.\n  -h   Display program synopsis and usage.");
    }
    if (z == 1 || a == 1) {
        printf("e() = %16.15lf, M_E = %16.14lf, diff = %16.15lf\n", e(), M_E, absolute(e() - M_E));
        if (s == 1) {
            printf("e() terms = %d\n", e_terms());
        }
    }

    if (r == 1 || a == 1) {
        printf("pi_euler() = %16.15lf, M_PI = %16.15lf, diff = %16.16lf\n", pi_euler(), M_PI,
            absolute(pi_euler() - M_PI));
        if (s == 1) {
            printf("pi_euler() terms = %d\n", pi_euler_terms());
        }
    }
    if (b == 1 || a == 1) {
        printf("pi_bbp() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_bbp(), M_PI,
            absolute(pi_bbp() - M_PI));
        if (s == 1) {
            printf("pi_bbp() terms = %d\n", pi_bbp_terms());
        }
    }
    if (m == 1 || a == 1) {
        printf("pi_madhava() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_madhava(), M_PI,
            absolute(pi_madhava() - M_PI));
        if (s == 1) {
            printf("pi_madhava() terms = %d\n", pi_madhava_terms());
        }
    }

    if (v == 1 || a == 1) {
        printf("pi_viete() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_viete(), M_PI,
            absolute(pi_viete() - M_PI));
        if (s == 1) {
            printf("pi_viete() terms = %d\n", pi_viete_factors());
        }
    }
    if (n == 1 || a == 1) {
        for (double i = 0; i < 10; i += .1) {
            printf("sqrt_newton(%lf) = %16.15lf, sqrt(%lf) = %16.15lf, diff = %16.15lf\n", i,
                sqrt_newton(i), i, sqrt(i), absolute(sqrt_newton(i) - sqrt(i)));
            if (s == 1) {
                printf("sqrt_newton() terms = %d\n", sqrt_newton_iters());
            }
        }
    }
}

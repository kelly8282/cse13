#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include "randstate.h"
#include <gmp.h>

gmp_randstate_t state; //creating our state
void randstate_init(uint64_t seed) { //initializing state
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, seed);
}

void randstate_clear(void) { //clearing state function
    gmp_randclear(state);
}

//end of randstate

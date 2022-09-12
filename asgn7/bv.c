#include "bv.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <assert.h>

struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

BitVector *bv_create(uint32_t length) { //given in our code comment repo
    BitVector *bv = (BitVector *) malloc(sizeof(BitVector));
    if (bv != NULL) {
        uint32_t temp = length / 8 + (length % 8 ? 1 : 0);
        bv->vector = (uint8_t *) calloc(temp, sizeof(uint8_t));
        bv->length = length;
        return bv;
    } else {
        return NULL;
    }
}

void bv_print(BitVector *bv) {
    for (uint32_t i = 0; i < bv->length; i++) { //print statement for debugging
        printf("%" PRIu8 ",", bv_get_bit(bv, i));
    }
}

void bv_delete(BitVector **bv) { //free everything
    if (*bv && (*bv)->vector) {
        free((*bv)->vector);
        free(*bv);
        *bv = NULL;
    }
}
uint32_t bv_length(BitVector *bv) {
    return bv->length;
}
bool bv_set_bit(BitVector *bv, uint32_t i) {
    if (i < 0 || i > bv->length - 1) {
        return false;
    }
    uint32_t byte = (i / 8);
    uint32_t specific = i % 8;
    uint8_t new = 1;
    new = new << specific;
    bv->vector[byte] = bv->vector[byte] | new;
    return true;
}
bool bv_clr_bit(BitVector *bv, uint32_t i) {
    if (i < 0 || i > bv->length - 1) {
        return false;
    }
    uint32_t byte = (i / 8); //bit math below
    uint32_t specific = i % 8;
    uint8_t new = 1;
    new = new << specific;
    new = ~(new);
    bv->vector[byte] = bv->vector[byte] & new;
    return true;
}
bool bv_get_bit(BitVector *bv, uint32_t i) {
    if (i < 0 || i > bv->length - 1) {
        return false;
    }
    uint32_t byte = (i / 8); //bit math below
    uint32_t specific = i % 8;
    uint8_t new = 1;
    uint8_t temp = bv->vector[byte];

    temp = temp >> specific;
    temp = temp & new;

    if (temp == 1) {
        return true;
    }
    return false;
}

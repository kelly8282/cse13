#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include "code.h"
#include "defines.h"

Code code_init(void) {
    Code code;
    code.top = 0;
    for (uint8_t i = 0; i < MAX_CODE_SIZE; i++) { //setting all code to 0
        code.bits[i] = 0;
    }
    return code;
}

uint32_t code_size(Code *c) {
    return c->top;
}

bool code_empty(Code *c) {
    if (c->top == 0) {
        return true;
    } else {
        return false;
    }
}

bool code_full(Code *c) {
    if (c->top == ALPHABET) {
        return true;
    } else {
        return false;
    }
}

bool code_set_bit(Code *c, uint32_t i) {
    if (i < 0 || i > ALPHABET - 1) {
        return false;
    }
    uint32_t byte = (i / 8); //bit math below
    uint32_t specific = i % 8;
    uint8_t new = 1;
    new = new << specific;
    c->bits[byte] = c->bits[byte] | new;
    return true;
}

bool code_clr_bit(Code *c, uint32_t i) {
    if (i < 0 || i > ALPHABET - 1) {
        return false;
    }
    uint32_t byte = (i / 8); //bit math below
    uint32_t specific = i % 8;
    uint8_t new = 1;
    new = new << specific;
    new = ~(new);
    c->bits[byte] = c->bits[byte] & new;
    return true;
}

bool code_get_bit(Code *c, uint32_t i) {
    if (i < 0 || i > ALPHABET - 1) {
        return false;
    }
    uint32_t byte = (i / 8); //bit math below
    uint32_t specific = i % 8;
    uint8_t new = 1;
    uint8_t temp = c->bits[byte];

    temp = temp >> specific;
    temp = temp & new;

    if (temp == 1) {
        return true;
    }
    return false;
}

bool code_push_bit(Code *c, uint8_t bit) {
    if (code_full(c)) {
        return false;
    }
    if (bit == 1) {
        code_set_bit(c, c->top);
    }
    if (bit == 0) {
        code_clr_bit(c, c->top);
    }
    c->top = c->top + 1;
    return true;
}

bool code_pop_bit(Code *c, uint8_t *bit) {
    if (code_empty(c) == true) {
        return false;
    }
    c->top = c->top - 1;
    *bit = code_get_bit(c, c->top); //setting our bit
    return true;
}

void code_print(Code *c) {
    printf("Code size: %d\n", c->top);
}

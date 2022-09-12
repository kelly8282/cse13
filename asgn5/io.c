#include "io.h"
#include "defines.h"
#include "code.h"

#include <fcntl.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

uint32_t c_pos = 0;
uint8_t buffer[BLOCK];
uint64_t bytes_read = 0;
uint64_t bytes_written = 0;

int read_bytes(int infile, uint8_t *buf, int nbytes) {
    int count = 0;
    while (nbytes > 0) {
        int temp = read(infile, buf + count,
            nbytes); //buf plus count to read in the middle buffer so I don't write what I did before
        if (temp <= 0) {
            break;
        }
        bytes_read = bytes_read + temp;
        count = count + temp;
        nbytes = nbytes - temp;
    }
    return count;
}

int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    int count = 0;
    while (nbytes > 0) {
        int temp
            = write(outfile, buf + count, nbytes); //buf plus count because of same reasoning above
        if (temp <= 0) {
            break;
        }
        bytes_written = bytes_written + temp;
        count = count + temp;
        nbytes = nbytes - temp;
    }
    return count;
}

bool read_bit(int infile, uint8_t *bit) {
    static uint8_t buf[BLOCK];
    static uint32_t top = 0;
    static uint32_t pos = 0;

    if (pos == top * 8) {
        top = read_bytes(infile, buf, BLOCK);
        pos = 0;
        if (top <= 0) {
            return false;
        }
    }
    uint8_t val = buf[pos / 8]; //bit math below
    uint8_t new = 0;
    new = pos % 8;
    new = val >> new;
    new = new & 1;
    *bit = new;
    pos = pos + 1;
    return true;
}

void write_code(int outfile, Code *c) {
    for (uint32_t i = 0; i < c->top; i++) {
        uint8_t val = c->bits[i / 8] & (1 << i % 8); //bit math below
        val = val >> (i % 8);
        buffer[c_pos / 8] = buffer[c_pos / 8] | (val << c_pos % 8);
        c_pos = c_pos + 1; //incrementing c_pos
        if (c_pos / 8 == BLOCK) {
            flush_codes(outfile);
        }
    }
}

void flush_codes(int outfile) {
    if (c_pos % 8 == 0) {
        write_bytes(outfile, buffer, c_pos / 8);
    } else if (c_pos % 8 > 0) {
        write_bytes(outfile, buffer, (c_pos / 8) + 1);
    }
    memset(buffer, 0, BLOCK);
    c_pos = 0;
}


#include "bv.h"
#include "salts.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "bf.h"
#include "speck.h"

struct BloomFilter {
    uint64_t primary[2];
    uint64_t secondary[2];
    uint64_t tertiary[2];
    BitVector *filter;
};

BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter)); //initialize everything
    bf->filter = bv_create(size);
    bf->primary[0] = SALT_PRIMARY_LO;
    bf->primary[1] = SALT_PRIMARY_HI;
    bf->secondary[0] = SALT_SECONDARY_LO;
    bf->secondary[1] = SALT_SECONDARY_HI;
    bf->tertiary[0] = SALT_TERTIARY_LO;
    bf->tertiary[1] = SALT_TERTIARY_HI;
    return bf;
}
void bf_delete(BloomFilter **bf) {
    bv_delete(&(*bf)->filter); //delete and free everything
    free(*bf);
    *bf = NULL;
}
uint32_t bf_size(BloomFilter *bf) {
    return bv_length(bf->filter);
}
void bf_insert(BloomFilter *bf, char *oldspeak) {
    uint32_t primary = hash(bf->primary, oldspeak); //hash the oldspeak with the primary
    primary
        = primary
          % bv_length(bf->filter); //set the primary index to the hash by the length of the filter
    uint32_t secondary = hash(bf->secondary, oldspeak); //hash the oldspeak with the secondary
    secondary
        = secondary
          % bv_length(bf->filter); //set the secondary index to the hash by the length of the filter
    uint32_t tertiary = hash(bf->tertiary, oldspeak); //hash the oldspeak with the tertiary
    tertiary
        = tertiary
          % bv_length(bf->filter); //set the tertiary index to the hash by the length of the filter
    bv_set_bit(bf->filter, primary); //set the primary index
    bv_set_bit(bf->filter, secondary); //set the secondary index
    bv_set_bit(bf->filter, tertiary); //set the tertiary index
}

bool bf_probe(BloomFilter *bf, char *oldspeak) {
    uint32_t primary = hash(bf->primary, oldspeak); //same reasoning as above
    primary = primary % bv_length(bf->filter);
    uint32_t secondary = hash(bf->secondary, oldspeak);
    secondary = secondary % bv_length(bf->filter);
    uint32_t tertiary = hash(bf->tertiary, oldspeak);
    tertiary = tertiary % bv_length(bf->filter);
    if (bv_get_bit(bf->filter, primary) == 1 && bv_get_bit(bf->filter, secondary) == 1
        && bv_get_bit(bf->filter, tertiary)
               == 1) { //check if every bit at those indexes are one if so return true
        return true;
    }
    return false;
}
uint32_t bf_count(BloomFilter *bf) {
    uint32_t total = 0;
    for (uint32_t i = 0; i < bv_length(bf->filter);
         i++) { //count up every bit that is one by interating through my bloom filter
        if (bv_get_bit(bf->filter, i) == 1) {
            total = total + 1;
        }
    }
    return total;
}
void bf_print(BloomFilter *bf) {
    bv_print(bf->filter);
}

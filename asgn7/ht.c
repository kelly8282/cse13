#include <stdlib.h>
#include "ht.h"
#include <stdio.h>
#include <inttypes.h>
#include "bst.h"
#include "speck.h"
#include <stdint.h>
#include "salts.h"

uint64_t lookups;

struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    Node **trees;
};

HashTable *ht_create(uint32_t size) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable)); //initialize everything
    ht->size = size;
    ht->trees = (Node **) calloc(size, sizeof(Node *));
    ht->salt[0] = SALT_HASHTABLE_LO;
    ht->salt[1] = SALT_HASHTABLE_HI;
    return ht;
}

void ht_print(HashTable *ht) {
    for (uint32_t i = 0; i < ht->size; i++) { //print statement for debug purposes
        bst_print(ht->trees[i]);
    }
}

void ht_delete(HashTable **ht) {
    if (*ht) { //if ht exists
        for (uint32_t i = 0; i < (*ht)->size; i++) { //traverse through individual trees and free
            bst_delete(&(*ht)->trees[i]);
        }
        free((*ht)->trees); //free everything else
        free(*ht);
        *ht = NULL;
    }
}
uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

Node *ht_lookup(HashTable *ht, char *oldspeak) {
    lookups = lookups + 1;
    uint32_t iter = 0;
    iter = hash(ht->salt, oldspeak); //hash the oldspeak using the salt
    iter = iter % ht->size; //mod it by the size to get the index
    Node *look = ht->trees[iter];
    if (look == NULL) { //if our node doesn't exist return null
        return NULL;
    } else { //else return our node
        return bst_find(look, oldspeak);
    }
}

void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    lookups = lookups + 1;
    uint32_t iter = 0;
    iter = hash(ht->salt, oldspeak); //hash the oldspeak using the salt
    iter = iter % ht->size; //mod it by the size to get the index
    ht->trees[iter] = bst_insert(
        ht->trees[iter], oldspeak, newspeak); //insert the node into our tree at that index
}

uint32_t ht_count(HashTable *ht) {
    uint32_t total = 0;
    for (uint32_t i = 0; i < ht->size;
         i++) { //use a for loop to see if the BST exists in our hash table
        if (ht->trees[i] != NULL) {
            total = total + 1;
        }
    }
    return total;
}

double ht_avg_bst_size(HashTable *ht) {
    uint32_t total = 0;
    for (uint32_t i = 0; i < ht->size; i++) { //use a for loop to check each individual bst tree
        total = total + bst_size(ht->trees[i]); //total = total + size of each tree
    }
    double final = total / (double) ht_count(ht);
    return final;
}

double ht_avg_bst_height(HashTable *ht) {
    uint32_t total = 0;
    for (uint32_t i = 0; i < ht->size; i++) { //usd a for loop to check each individual bst tree
        total = total + bst_height(ht->trees[i]); //total = toal + height of each tree
    }
    double final = total / (double) ht_count(ht);
    return final;
}

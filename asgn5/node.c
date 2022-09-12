#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include "node.h"

Node *node_create(uint8_t symbol, uint64_t frequency) { //creating my constructor for my node
    Node *n = (Node *) malloc(sizeof(Node));
    n->left = NULL;
    n->right = NULL;
    n->symbol = symbol;
    n->frequency = frequency;
    return n;
}

void node_delete(Node **n) {
    free(*n); //freeing everything
    *n = NULL;
}

Node *node_join(Node *left, Node *right) {
    Node *parent = node_create('$', left->frequency + right->frequency); //creating a parent node
    parent->left = left; //setting parent left node
    parent->right = right; //setting parent right node
    return parent;
}

void node_print(Node *n) {
    printf("%lu", n->frequency);
}

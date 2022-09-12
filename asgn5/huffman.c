#include "huffman.h"
#include "node.h"
#include "pq.h"
#include "stack.h"
#include "io.h"
#include "code.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

Node *build_tree(uint64_t hist[]) { //building tree off of psuedocode in assignment document
    PriorityQueue *q = pq_create(ALPHABET);
    for (uint64_t i = 0; i < ALPHABET; i++) {
        if (hist[i] > 0) {
            Node *new = node_create(i, hist[i]);
            enqueue(q, new);
        }
    }

    while (pq_size(q) >= 2) {
        Node *left = NULL;
        Node *right = NULL;
        dequeue(q, &left);
        dequeue(q, &right);
        Node *parent = node_join(left, right);
        enqueue(q, parent);
    }
    Node *root = NULL;
    dequeue(q, &root); //clearing things
    pq_delete(&q);
    return root;
}

void build_code(
    Code c, Node *root, Code table[]) { //building code based off of pseudocode in assignment doc
    if (root != NULL) {
        if (root->left == NULL && root->right == NULL) {
            table[root->symbol] = c;
        }
    }
    if (root == NULL) {
        return;
    } else {
        uint8_t temp = 0;
        code_push_bit(&c, 0);
        build_code(c, root->left, table);
        code_pop_bit(&c, &temp);

        code_push_bit(&c, 1);
        build_code(c, root->right, table);
        code_pop_bit(&c, &temp);
    }
}
void build_codes(Node *root,
    Code table
        [static ALPHABET]) { //creating this function so c doesn't clear when build_code is ran recursively
    Code c = code_init();
    build_code(c, root, table);
}

void dump_tree(int outfile, Node *root) {
    if (root != NULL) {
        dump_tree(outfile, root->left);
        dump_tree(outfile, root->right);
        if (root->left == NULL && root->right == NULL) {
            uint8_t pot = 'L'; //making my uint8 so I can make it a pointer
            write_bytes(outfile, &pot, 1);
            write_bytes(outfile, &root->symbol, 1);
        } else {
            uint8_t top = 'I'; //making my uint8 so I can make it a pointer
            write_bytes(outfile, &top, 1);
        }
    }
}

Node *rebuild_tree(
    uint16_t nbytes, uint8_t tree_dump[]) { //creating rebuilding tree based off of assignment doc
    Stack *s = stack_create(ALPHABET);
    Node *parent;
    for (uint16_t i = 0; i < nbytes; i++) {
        if (tree_dump[i] == 'L') {
            Node *temp = node_create(tree_dump[i + 1], 0);
            stack_push(s, temp);
        }
        if (tree_dump[i] == 'I') {
            Node *left = NULL;
            Node *right = NULL;
            stack_pop(s, &left);
            stack_pop(s, &right);
            parent = node_join(left, right);
            stack_push(s, parent);
        }
    }
    stack_pop(s, &parent);
    stack_delete(&s); //freeing stuff
    return parent;
}

void delete_tree(Node **root) {
    if (*root != NULL) { //deleting tree but checking if it's not null
        if ((*root)->left != NULL) {
            delete_tree(&(*root)->left);
        }
        if ((*root)->right != NULL) {
            delete_tree(&(*root)->right);
        }
        node_delete(root);
    }
}

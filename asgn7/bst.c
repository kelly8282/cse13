#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "node.h"
#include <stdbool.h>
#include <stdint.h>

uint64_t branches;

Node *bst_create(void) {
    return NULL;
}

uint32_t bst_height(Node *root) {
    if (root == NULL) { //check if root is null
        return 0;
    }
    //recursively find the height
    uint32_t left = bst_height(root->left);
    uint32_t right = bst_height(root->right);
    if (left > right) {
        return left + 1;
    } else {
        return right + 1;
    }
}

uint32_t bst_size(Node *root) {
    if (root == NULL) { //check if root is null
        return 0;
    }
    //recursively find the height similar to bst_height
    uint32_t left = bst_size(root->left);
    uint32_t right = bst_size(root->right);
    uint32_t total = right + left + 1;
    return total;
}
Node *bst_find(Node *root, char *oldspeak) {
    if (root == NULL) { //check if root is null
        return NULL;
    }
    if (strcmp(root->oldspeak, oldspeak) == 0) { //if they are equal return root
        return root;
    }
    branches = branches + 1;
    if (strcmp(oldspeak, root->oldspeak)
        < 0) { //if oldspeak  is less than recursively traverse left
        return bst_find(root->left, oldspeak);
    } else { //else recursively go right
        return bst_find(root->right, oldspeak);
    }
}
Node *bst_insert(Node *root, char *oldspeak, char *newspeak) {
    if (root == NULL) { //check if root is null if it is create a node
        root = node_create(oldspeak, newspeak);
        return root;
    }

    if (strcmp(oldspeak, root->oldspeak) < 0) { //if oldspeak is less than recursively go left
        branches = branches + 1;
        root->left = bst_insert(root->left, oldspeak, newspeak);
    }
    if (strcmp(oldspeak, root->oldspeak) > 0) { //if oldspeak is more than recursively go right
        branches = branches + 1;
        root->right = bst_insert(root->right, oldspeak, newspeak);
    }
    return root; //else return root
}
void bst_print(Node *root) {
    if (root == NULL) { //if root is null exit
        return;
    }

    bst_print(root->left);
    node_print(root);
    bst_print(root->right);
}
void bst_delete(Node **root) {
    if (root == NULL || *root == NULL) { //check if root exists
        return;
    }
    bst_delete(&(*root)->left);
    bst_delete(&(*root)->right);
    node_delete(root);
}

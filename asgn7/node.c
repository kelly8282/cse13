#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node Node;

struct Node {
    char *oldspeak;
    char *newspeak;
    Node *left;
    Node *right;
};

Node *node_create(char *oldspeak, char *newspeak) {
    char *new;
    char *old;

    if (newspeak != NULL) { //if newspeak isnt null create a copy
        new = strdup(newspeak);
    } else {
        new = NULL;
    }
    if (oldspeak != NULL) { //if oldspeak isnt null create a copy
        old = strdup(oldspeak);
    } else {
        old = NULL;
    }

    Node *n = (Node *) malloc(sizeof(Node)); //initialize everything
    n->oldspeak = old;
    n->newspeak = new;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void node_delete(Node **n) { //free everything
    if (*n != NULL) {
        free((*n)->oldspeak);
        free((*n)->newspeak);
        free(*n);
        *n = NULL;
    }
}
void node_print(Node *n) { //print like how the assignment document said
    if (n->oldspeak != NULL && n->newspeak != NULL) {
        printf("%s -> %s\n", n->oldspeak, n->newspeak);
    }
    if (n->oldspeak != NULL && n->newspeak == NULL) {
        printf("%s\n", n->oldspeak);
    }
}

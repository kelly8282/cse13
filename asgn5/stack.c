#include "stack.h"
#include "node.h"
#include "huffman.h"
#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//including all files above
struct Stack { //creting my struct for my Stack
    uint32_t top; //creating my top
    uint32_t capacity; //creating my variable
    Node **items; //creating my itmes stack
};

Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack)); //allocating memory into my stack
    if (s) { //if s is true
        s->top = 0; //initialize top
        s->capacity = capacity; //initialize capacity
        s->items = (Node **) calloc(capacity, sizeof(Node *)); //initializing my items
    }
    return s; //returning our stack
}

void stack_delete(Stack **s) {
    if (*s && (*s)->items) { //checking if our stack works properly
        for (uint32_t counter = 0; counter < (*s)->top; counter++) { // test
            delete_tree(&(*s)->items[counter]);
        }
        free((*s)->items); //freeing up memory
        free(*s); //freeing up memory
        *s = NULL; //setting s to null
    }
    return;
}

bool stack_empty(Stack *s) {
    if (s->top == 0) { //checking if our stack is empty
        return true; //return true if empty
    }
    return false; //return false if not empty
}

bool stack_full(Stack *s) {
    if (s->capacity == s->top) { //checking my capacity is where my top counter is at
        return true; //return true if so
    }
    return false; //return false if not
}

uint32_t stack_size(Stack *s) {
    return s->top; //returning my stack size
}

bool stack_push(Stack *s, Node *x) {
    if (stack_full(s) == true) { //making sure our stack isn't full
        return false; //return false as function didn't run
    } else {
        s->items[s->top] = x; //pyshing value x onto our stack
        s->top = s->top + 1; //incrementing our top variable
        return true; //retun true as my function ran correctly
    }
}

bool stack_pop(Stack *s, Node **x) {
    if (stack_empty(s) == true) { //making sure our stack isn't empty
        return false; //return false as function didn't run
    } else {
        s->top = s->top - 1; //decrementing our top variable
        *x = s->items[s->top]; //setting our pointer variable to the item that we are popping
        return true; //return true as fuction ran correctly
    }
}

void stack_print(Stack *s) {
    for (uint32_t i = 0; i < s->top; i++) { //printing our stack
        node_print(s->items[i]);
    }
}

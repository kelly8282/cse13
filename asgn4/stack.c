#include "stack.h"

#include "vertices.h"

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
    uint32_t *items; //creating my itmes stack
};

Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack)); //allocating memory into my stack
    if (s) { //if s is true
        s->top = 0; //initialize top
        s->capacity = capacity; //initialize capacity
        s->items = (uint32_t *) calloc(capacity, sizeof(uint32_t)); //initializing my items
        if (!s->items) { //checking if s isn't equal to my items
            free(s); //freeing up memory
            s = NULL; //setting s to null
        }
    }
    return s; //returning our stack
}

void stack_delete(Stack **s) {
    if (*s && (*s)->items) { //checking if our stack works properly
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

bool stack_push(Stack *s, uint32_t x) {
    if (stack_full(s) == true) { //making sure our stack isn't full
        return false; //return false as function didn't run
    } else {
        s->items[s->top] = x; //pyshing value x onto our stack
        s->top = s->top + 1; //incrementing our top variable
        return true; //retun true as my function ran correctly
    }
}

bool stack_pop(Stack *s, uint32_t *x) {
    if (stack_empty(s) == true) { //making sure our stack isn't empty
        return false; //return false as function didn't run
    } else {
        s->top = s->top - 1; //decrementing our top variable
        *x = s->items[s->top]; //setting our pointer variable to the item that we are popping
        return true; //return true as fuction ran correctly
    }
}

bool stack_peek(Stack *s, uint32_t *x) {
    if (stack_empty(s) == true) { //making sure our stack isn't empty
        return false; //return faalse if function didn't run
    }
    uint32_t temp = 0; //setting a temp variable
    stack_pop(s, &temp); //popping our value to set temp
    *x = temp; //setting pointer to temp
    stack_push(s, temp); //pushing temp back to stack
    return true; //return true as function ran correctly
}

void stack_copy(Stack *dst, Stack *src) {
    free(dst->items); //freeing dst so we can copy our src items into
    dst->items = (uint32_t *) calloc(
        src->capacity, sizeof(uint32_t)); //allocating memory for our dst items stack
    memcpy(dst->items, src->items,
        sizeof(uint32_t) * (src->capacity)); //copying our src stack into our dst stack
    dst->capacity = src->capacity; //copying our capacity variables
    dst->top = src->top; //copying our top variables
}

void stack_print(Stack *s, FILE *outfile, char *cities[]) {
    for (uint32_t i = 0; i < s->top; i++) { //printing our stack into outfile, function was provided
        fprintf(outfile, "%s", cities[s->items[i]]);
        if (i + 1 != s->top) {
            fprintf(outfile, " -> ");
        }
    }
    fprintf(outfile, "\n");
}

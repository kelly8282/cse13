#include "path.h"

#include "graph.h"
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

struct Path { //creting struct for my Path
    Stack *vertices; //creating my stack of vertices using a pointer
    uint32_t length; //creating a length value
};

Path *path_create(void) {
    Path *path = (Path *) malloc(sizeof(Path)); //allocating memory to my path
    path->vertices = stack_create(VERTICES); //initializing my stack
    path->length = 0; //initializing my length
    return path; //returning path
}

void path_delete(Path **p) {
    stack_delete(&(*p)->vertices);

    free(*p); //freeing up memory
    *p = NULL; //setting *p to null
}

bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    if (stack_full(p->vertices) == true) { //checking if my stack is full already
        return false; //if so return false
    } else { //else run through my function

        uint32_t temp = 0; //setting a temporary value
        stack_peek(p->vertices, &temp); //peeking in to set my cat to my last value in my stack
        if (stack_empty(p->vertices)
            == true) { //checking if it is empty as that would mean by length wouldn't change
            stack_push(p->vertices, v); //pushing my value on my stack
            return true; //returning true because the function ran
        }
        stack_push(p->vertices, v); //pushing my value on my stack
        p->length = p->length + graph_edge_weight(G, temp, v); //incrementing my length appropritely
        return true; //returning true because the function ran
    }
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    if (stack_empty(p->vertices) == true) { //checking if my stack is empty already
        return false; //if so return false
    } else {
        uint32_t temp = 0; //setting a temporary value
        stack_pop(p->vertices, v); //popping my value
        if (stack_peek(p->vertices, &temp) == true) { //checking if stack peek runs correctly
            p->length
                = p->length - graph_edge_weight(G, temp, *v); //changing my length appropriately
        }
        return true; //returning true if ran correctly
    }
}

uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices); //returning the stack size of vertices
}

uint32_t path_length(Path *p) {
    return p->length; //returning the path length
}

void path_copy(Path *dst, Path *src) {
    stack_copy(dst->vertices, src->vertices); //coping src vertices to dst vertices
    dst->length = src->length; //coping dst length into src length
}

void path_print(Path *p, FILE *outfile, char *cities[]) {
    fprintf(outfile, "Path length: %u\nPath: ", path_length(p)); //printing to outfile
    stack_print(p->vertices, outfile, cities); //using print function in stack to print
}

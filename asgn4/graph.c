#include "graph.h"

#include "vertices.h"

#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//including all files bove

struct Graph { //making my structure for my graph
    uint32_t vertices; //defining vertices
    bool undirected; //defining directed
    bool visited[VERTICES]; //defining my visited array
    uint32_t matrix[VERTICES][VERTICES]; //defining my matrix for my graph
};

Graph *graph_create(uint32_t vertices, bool undirected) { //creating my constructor
    Graph *G = (Graph *) calloc(1, sizeof(Graph)); //allocating memory in my graog
    G->vertices = vertices; //initializing vertices
    G->undirected = undirected; //initilizing undirected
    for (uint32_t i = 0; i < G->vertices;
         i++) { //using  for loop to ensure that all values in the matrix is zero
        G->visited[i] = false; //making sure that all of my vaalues in visited array is false
        for (uint32_t j = 0; j < G->vertices; j++) {
            G->matrix[i][j] = 0;
        }
    }
    return G;
}

void graph_delete(Graph **G) {
    free(*G); //freeing up  memory
    *G = NULL; //setting G to null
}

uint32_t graph_vertices(Graph *G) {
    return G->vertices; //returning vertices
}

bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    if (i < G->vertices && j < G->vertices && i >= 0
        && j >= 0) { //checking if i aand j are in bounds
        G->matrix[i][j] = k; // adding weight to matrix[i][j]
        if (G->undirected == true) { //checking if it is undirected
            G->matrix[j][i] = k; //if undirected add weight to matrix[j][i]
        }
    } else {
        return false; //return false if the function didn't run as intended
    }
    return true; //retrun true if function ran as intended
}

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    if (i < G->vertices && j < G->vertices && i >= 0 && j >= 0) {
        return G->matrix[i][j];
    } else {
        return 0;
    }
}

bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    if (i < G->vertices && j < G->vertices && i >= 0 && j >= 0) { //checking if i nd j are in bounds
        if (G->matrix[i][j] > 0) { //checking if there is an edge
            return true; //return true if there's an edge
        }
    }
    return false; //return false if there's no edge
}

bool graph_visited(Graph *G, uint32_t v) {
    if (G->visited[v] == true) { //checking if the vertex v is visited
        return true; //return true if visited
    }
    return false; //return false if not visited
}

void graph_mark_visited(Graph *G, uint32_t v) {
    if (v < G->vertices && v >= 0) { //checking if v is in bounds
        G->visited[v] = true; //marking vertex v as visited
    }
}

void graph_mark_unvisited(Graph *G, uint32_t v) {
    if (v < G->vertices && v >= 0) { //marking if v is in bounds
        G->visited[v] = false; //marking vertex v as unvisited
    }
}

void graph_print(Graph *G) { //printing graph
    for (uint32_t i = 0; i < G->vertices; i++) {
        for (uint32_t j = 0; j < G->vertices; j++) {
            printf("%2u ", G->matrix[i][j]);
        }
        printf("\n");
    }
}

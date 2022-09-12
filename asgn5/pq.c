#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "pq.h"
#include "defines.h"
#include "huffman.h"

struct PriorityQueue { //making my structure for my PriorityQueue
    Node **heap;
    uint32_t top;
    uint32_t capacity;
};

PriorityQueue *pq_create(uint32_t capacity) { //creating my constructor
    PriorityQueue *pq = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    pq->capacity = capacity;
    pq->top = 0;
    pq->heap = (Node **) calloc(capacity, sizeof(Node *));
    return pq;
}

void pq_delete(PriorityQueue **q) {
    if (*q) {
        for (uint32_t i = 0; i < (*q)->top; i++) {
            delete_tree(&(*q)->heap[i]); //freeing everything in my heap
        }
        free((*q)->heap); //freeing everything else
        free(*q);
        *q = NULL;
    }
}

bool pq_empty(PriorityQueue *q) {
    if (q->top == 0) { //checking if it's empty
        return true;
    }
    return false;
}

bool pq_full(PriorityQueue *q) {
    if (q->top == q->capacity) { //checking if it's full
        return true;
    }
    return false;
}

uint32_t pq_size(PriorityQueue *q) {
    return q->top; //return our top which is our size
}

void heapify(PriorityQueue *q, uint32_t i) {
    uint32_t left_child = i * 2 + 1; //setting left child
    uint32_t right_child = i * 2 + 2; //setting right child
    uint32_t smallest = i; //making a smallest child
    if (left_child < q->top
        && q->heap[left_child]->frequency
               < q->heap[i]
                     ->frequency) { //checking if the left child is smaller than our size and checking if the frequency is smaller than the frequency of the i passed in
        smallest = left_child;
    }
    if (right_child < q->top
        && q->heap[right_child]->frequency
               < q->heap[smallest]
                     ->frequency) { //checking if the right child is smaller than our size and checking if the frequency is smaller than the frequency of the i passed in
        smallest = right_child;
    }
    if (smallest != i) { //checking if the smallest is our i or not
        Node *temp = NULL; //creating a temp
        temp = q->heap[smallest]; //setting our temp
        q->heap[smallest] = q->heap[i]; //swapping our values
        q->heap[i] = temp;
        heapify(q, smallest); //recursively calling heap
    }
}

bool enqueue(PriorityQueue *q, Node *n) {
    if (q != NULL) { //checking if it's not null
        if (pq_full(q)) { //checking if it's full
            return false;
        }
        q->heap[q->top] = n; //adding our node
        q->top = q->top + 1; //incrementing our top
        uint32_t i = q->top - 1; //setting a top - 1
        while (i != 0
               && q->heap[(i - 1) / 2]->frequency
                      > q->heap[i]->frequency) { //sorting our node passed in
            Node *temp = q->heap[i];
            q->heap[i] = q->heap[(i - 1) / 2];
            q->heap[(i - 1) / 2] = temp;
            i = (i - 1) / 2;
        }
        return true;
    }
    return false;
}

bool dequeue(PriorityQueue *q, Node **n) {
    if (q != NULL) { //checking if it's not null
        if (pq_empty(q)) { //checking if it's empty
            return false;
        }
        if (q->top == 1) { //checking test case if our top is 1
            q->top = q->top - 1;
            *n = q->heap[0];
            return true;
        }
        *n = q->heap[0];
        q->heap[0] = q->heap[q->top - 1];
        q->top = q->top - 1; //decrementing our top
        heapify(q, 0); //sorting
        return true;
    }
    return false;
}

void pq_print(PriorityQueue *q) {
    printf("%u", q->top);
}

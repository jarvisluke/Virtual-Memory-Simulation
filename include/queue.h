#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

// Define structures
typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
} Queue;

// Function declarations
void push(Queue* q, int data);
int pop(Queue* q);
int in_queue(Queue *q, int data);

#endif // QUEUE_H
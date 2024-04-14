#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

// Define structures
typedef struct Node 
{
    int data;
    struct Node* next;
    int referenced;
} Node;

typedef struct 
{
    Node* head;
    Node* tail;
} Queue;

// Function declarations
void queue_push(Queue* q, int data);
void queue_pop(Queue* q);
int queue_check(Queue* q, int data);
void queue_mark(Queue* q, int data);
void queue_second_chance(Queue* q);
void queue_clear_all_marks(Queue* q);
void print_queue(Queue* q);

#endif // QUEUE_H
#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

// Define structures
typedef struct Node 
{
    int page;
    struct Node* next;
    int mark;
} Node;

typedef struct 
{
    Node* head;
    Node* tail;
} Queue;

typedef struct
{
    int page;
    int mark;
} CircularArrayEle;

typedef struct
{
    CircularArrayEle* arr;
    int arr_size;
    int i;
} CircularArray;

// Function declarations
void queue_add(Queue* q, int page);
void queue_remove(Queue* q);
int queue_contains(Queue* q, int page);
void queue_mark(Queue* q, int page);
void queue_second_chance(Queue* q);
void queue_print(Queue* q);

void circ_add(CircularArray* c, int page);
void circ_remove(CircularArray* c);
int circ_contains(CircularArray* c, int page);
void circ_mark(CircularArray* c, int page);
void circ_second_chance(CircularArray* c, int page);
void circ_print(CircularArray* c);

#endif // QUEUE_H
#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <stdlib.h>

// Define structures
typedef struct node
{
    int page;
    struct node* next;
    int mark;
} Node;

typedef struct 
{
    Node* head;
    Node* tail;
} List;

typedef struct
{
    int page;
    int mark;
    unsigned int counter;
} ArrayNode;

typedef struct
{
    ArrayNode* arr; // Array defined as a pointer so its size can be adjusted dynamically
    int arr_size;
    int i;
} CircularArray;

// Function declarations
void queue_push(List* q, int page);
void queue_pop(List* q);
int queue_contains(List* q, int page);
void queue_mark(List* q, int page);
void queue_second_chance(List* q);
void queue_move_to_tail(List* q, int page);
void queue_print(List* q);

int arr_contains(int arr[], int arr_size, int page);
int arr_contains_node(ArrayNode* arr, int arr_size, int page);
void arr_replace_lowest(ArrayNode* arr, int arr_size, int page);
void arr_replace_furthest(int arr[], int arr_size, int pages[], int pages_size, int index);
void arr_increment_marked(ArrayNode* arr, int arr_size);
void arr_age_marked(ArrayNode* arr, int arr_size, int clock);

int circ_contains(CircularArray* c, int page);
void circ_mark(CircularArray* c, int page);
void circ_second_chance(CircularArray* c, int page);
void circ_print(CircularArray* c);

#endif // DATA_STRUCT_H
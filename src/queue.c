#include <stdio.h>
#include "queue.h"

// Adds node to tail
void queue_push(Queue* q, int data)
{
    // Creates new Node
    Node* new_node = malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    new_node->referenced = 0;

    // Adds new_node to the queue
    if (q->head == NULL)
    {
        q->head = q->tail = new_node;
    }
    else 
    {
        q->tail->next = new_node;
        q->tail = new_node;
    }
}

// Removes node at head
void queue_pop(Queue* q)
{
    if (q->head == NULL)
    {
        return;
    }
    Node* next = q->head->next;
    free(q->head);
    q->head = next;
}

// Checks if data is in queue
int queue_check(Queue *q, int data)
{
    Node* i = q->head;
    while (i != NULL)
    {
        if (i->data == data)
        {
            return 1;
        }
        i = i->next;
    }
    return 0;
}

// Marks a node referenced
void queue_mark(Queue* q, int data)
{
    Node* i = q->head;
    while (i != NULL)
    {
        if (i->data == data)
        {
            i->referenced = 1;
            return;
        }
        i = i->next;
    }
}

// Unmarks node with data, or pops it
void queue_second_chance(Queue* q)
{
    Node* i = q->head;
    while (i->referenced == 1)
    {
        i->referenced = 0;
        q->head = i->next;
        i->next = NULL;
        queue_push(q, i->data);
        i = q->head;
    }
    queue_pop(q);
}

// Sets all nodes referenced to 0
void queue_clear_all_marks(Queue* q)
{
    Node* i = q->head;
    while (i != NULL)
    {
        i->referenced = 0;
        i = i->next;
    }
}

void queue_print(Queue* q)
{
    Node* i = q->head;
    printf("Queue: ");
    while (i != NULL)
    {
        printf("%d[%d] ", i->data, i->referenced);
        i = i->next;
    }
    printf("\n");
}
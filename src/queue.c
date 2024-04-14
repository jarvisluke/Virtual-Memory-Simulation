#include <stdio.h>
#include "queue.h"

void push(Queue* q, int data)
{
    // Creates new Node
    Node* new_node = malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;

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

int pop(Queue* q)
{
    if (q->head == NULL)
    {
        return -1;
    }
    int data = q->head->data;
    Node* next = q->head->next;
    free(q->head);
    q->head = next;
    return data;
}

int in_queue(Queue *q, int data)
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
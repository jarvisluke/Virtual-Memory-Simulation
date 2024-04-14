#include <stdio.h>
#include "queue.h"

/* Queue functions */

// Adds node to tail
void queue_add(Queue* q, int page)
{
    // Creates new Node
    Node* new_node = malloc(sizeof(Node));
    new_node->page = page;
    new_node->next = NULL;
    new_node->mark = 0;

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
void queue_remove(Queue* q)
{
    if (q->head == NULL)
    {
        return;
    }
    Node* next = q->head->next;
    free(q->head);
    q->head = next;
}

// Checks if queue contains page
int queue_contains(Queue *q, int page)
{
    Node* i = q->head;
    while (i != NULL)
    {
        if (i->page == page)
        {
            return 1;
        }
        i = i->next;
    }
    return 0;
}

// Marks a node referenced
void queue_mark(Queue* q, int page)
{
    Node* i = q->head;
    while (i != NULL)
    {
        if (i->page == page)
        {
            i->mark = 1;
            return;
        }
        i = i->next;
    }
}

// Removes head if not marked, or unmarks it and moves it to tail
void queue_second_chance(Queue* q)
{
    Node* i = q->head;
    if (q->head == NULL)
    {
        return;
    }
    while (i->mark == 1)
    {
        i->mark = 0;
        q->head = i->next;
        i->next = NULL;
        queue_add(q, i->page);
        i = q->head;
    }
    queue_remove(q);
}

void queue_print(Queue* q)
{
    Node* i = q->head;
    printf("Queue: ");
    while (i != NULL)
    {
        printf("%d[%d] ", i->page, i->mark);
        i = i->next;
    }
    printf("\n");
}

/* CircularArray functions */

// Adds node before cursor
void circ_add(CircularArray* c, int page)
{
    /* Node* new_node = malloc(sizeof(Node));
    new_node->page = page;
    new_node->mark = 0;

    if (c->cur == NULL)
    {
        c->cur = new_node;
        new_node->next = new_node;
    }
    else
    {
        Node* i = c->cur->next;
        while (i->next != c->cur)
        {
            i = i->next;
        }
        i->next = new_node;
        new_node->next = c->cur;
    } */
    c->arr[c->i].page = page;
    c->i ++;
}

// Removes node at cursor
void circ_remove(CircularArray* c)
{
    /* if (c->cur == NULL)
    {
        return;
    }
    Node* next = c->cur->next;
    Node* i = next;
    while (i->next != c->cur)
    {
        i = i->next;
    }
    i->next = next;
    free(c->cur);
    c->cur = next; */
}

// Checks if list contains page
int circ_contains(CircularArray* c, int page)
{
    /* Node* i = c->cur;
    while (i->next != c->cur)
    {
        if (i->page == page)
        {
            return 1;
        }
        i = i->next;
    }
    return 0; */
    for (int i = 0; i < c->arr_size; i ++)
    {
        if (c->arr[i].page == page)
        {
            return 1;
        }
    }
    return 0;
}

// Marks a node as referenced
void circ_mark(CircularArray* c, int page)
{
    /* Node* i = c->cur;
    while (i->next != c->cur)
    {
        if (i->page == page)
        {
            i->mark = 1;
            return;
        }
        i = i->next;
    } */
    for (int i = 0; i < c->arr_size; i ++)
    {
        if (c->arr[i].page == page)
        {
            c->arr[i].mark = 1;
        }
    }
}

// Removes node at cursor if not marked, or unmarks it and iterates cursor
void circ_second_chance(CircularArray* c, int page)
{
    /* if (c->cur == NULL)
    {
        return;
    }
    while (c->cur->mark == 1)
    {
        c->cur->mark = 0;
        c->cur = c->cur->next;
    }
    circ_remove(c); */
    while (c->arr[c->i].mark == 1)
    {
        c->arr[c->i].mark = 0;
        c->i ++;
        c->i = c->i % c->arr_size;
    }
    c->arr[c->i].page = page;
}

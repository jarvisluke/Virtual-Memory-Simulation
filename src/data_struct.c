#include <stdio.h>
#include "data_struct.h"

/* List functions */

// Adds node to tail
void queue_push(List *q, int page)
{
    // Creates new Node
    Node *new_node = malloc(sizeof(Node));
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
void queue_pop(List *q)
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
int queue_contains(List *q, int page)
{
    Node *i = q->head;
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
void queue_mark(List *q, int page)
{
    Node *i = q->head;
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
void queue_second_chance(List *q)
{
    Node *i = q->head;
    if (q->head == NULL)
    {
        return;
    }
    while (i->mark == 1)
    {
        i->mark = 0;
        q->head = i->next;
        i->next = NULL;
        queue_push(q, i->page);
        i = q->head;
    }
    queue_pop(q);
}

// Prints all nodes in the queue
void queue_print(List *q)
{
    Node *i = q->head;
    printf("Head -> ");
    while (i != NULL)
    {
        printf("%d[%d] ", i->page, i->mark);
        i = i->next;
    }
    printf("<- Tail\n");
}

// Moves node with page to tail
void queue_move_to_tail(List *q, int page)
{
    Node* i = q->head;

    // Check if page is at head
    if (i->page == page)
    {
        if (i->next != NULL)
        {
            queue_push(q, i->page);
            q->head = i->next;
        }
        return;
    }

    // Iterate through rest of list
    while (i->next != NULL)
    {
        if (i->next->page == page)
        {
            Node *j = i->next;

            queue_push(q, j->page);
            i->next = j->next;
            free(j);
            return;
        }
        i = i->next;
    }
}

/* Array functions */

// Returns index of ArrayNode with page, or -1 if the array does not contain it
int arr_contains(ArrayNode* arr, int arr_size, int page)
{
    for (int i = 0; i < arr_size; i ++)
    {
        if (arr[i].page == page)
        {
            return i;
        }
    }
    return -1;
}

// Replace the ArrayNode with the lowest counter with the new page
void arr_replace_lowest(ArrayNode* arr, int arr_size, int page)
{
    int index = 0;
    int lowest = arr[0].counter;

    for (int i = 1; i < arr_size; i ++)
    {
        if (arr[i].mark > lowest)
        {
            index = i;
            lowest = arr[i].counter; 
        }
    }

    // Insert "new" ArrayNode at index with a reset counter
    arr[index].page = page;
    arr[index].mark = 0;
    arr[index].counter = 0;
}

// Replaces page with furthest next reference in page sequence
void arr_replace_furthest(int[] arr, int arr_size, int[] pages, int pages_size, int index)
{
    int furthest_index = index + 1;

    // Finds candidate for replacement
    for (int i = 0; i < arr_size; i ++)
    {
        int first_index = -1;
        for (int j = furthest_index; j < pages_size; j ++)
        {
            if arr[i] == pages[j]
            {
                first_index = j;
            }
        }

        // If arr[i] no longer occurs in pages, it is the ideal candidate
        if (first_index == -1)
        {
            arr[first_index] = pages[index];
            return;
        }
        // Set furthest_index to first index of arr[i] if it is the furthest from index
        else
        {
            if (first_index > furthest_index)
            {
                furthest_index = first_index;
            }
        }
    }

    arr[furthest_index] = pages[index];
}

// Increment the counter of all ArrayNodes with mark
void arr_increment_marked(ArrayNode* arr, int arr_size)
{
    for (int i = 1; i < arr_size; i ++)
    {
        if (arr[i].mark)
        {
            arr[i].counter ++;
            arr[i].mark = 0;
        }
    }
}

// Increment and age counters of all ArrayNodes with mark
void arr_age_marked(ArrayNode* arr, int arr_size, int clock)
{
    for (int i = 1; i < arr_size; i ++)
    {
        if (arr[i].mark)
        {
            arr[i].counter = arr[i].counter >> 1; // bit shift right
            arr[i].counter |= (1 << clock); // bitwise or assignment
            arr[i].mark = 0;
        }
    }
}

/* CircularArray functions */

// Checks if list contains page
int circ_contains(CircularArray *c, int page)
{
    for (int i = 0; i < c->arr_size; i++)
    {
        if (c->arr[i].page == page)
        {
            return 1;
        }
    }
    return 0;
}

// Marks a node as referenced
void circ_mark(CircularArray *c, int page)
{
    for (int i = 0; i < c->arr_size; i++)
    {
        if (c->arr[i].page == page)
        {
            c->arr[i].mark = 1;
        }
    }
}

// Removes node at cursor if not marked, or unmarks it and iterates cursor
void circ_second_chance(CircularArray *c, int page)
{
    while (c->arr[c->i].mark == 1)
    {
        c->arr[c->i].mark = 0;
        c->i = (c->i + 1) % c->arr_size;
    }
    c->arr[c->i].page = page;
}

void circ_print(CircularArray *c)
{
    printf("\tArray: {");
    for (int i = 0; i < c->arr_size; i++)
    {
        printf("%d, ", c->arr[i].page);
    }
    printf("}\ti: %d\n", c->i);
}
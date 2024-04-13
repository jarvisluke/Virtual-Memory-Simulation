#include <stdio.h>

typedef struct
{
    int data;
    struct node* next;
} Node;

typedef struct
{
    Node* head;
    Node* tail;
} Queue;

// Adds a data to the queue
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

// Removes the node at the front of the queue, returns its data
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

// Checks if a Queue contains the data
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

// Simulates first-in, first-out page replacement algorithm
int sim_fifo(int mem_size, int data[], int data_size) {
    int page_faults = 0;
    Queue* q = malloc(sizeof(Queue));
    int queue_size;

    for (int i = 0; i < data_size; i ++) {
        if (in_queue(q, data[i]))
        {
            continue;
        }
        else
        {
            page_faults ++;
            if (queue_size == mem_size)
            {
                pop(q);
            }
            else
            {
                queue_size ++;
            }
            push(q, data[i]);
        }
    }

    return page_faults;
}


// Main function
int main() {
    return 0;
}
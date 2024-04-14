#include <stdio.h>
#include "queue.h"

// Simulates first in, first out algorithm
int sim_fifo(int mem_size, int pages[], int pages_size)
{
    int page_faults = 0;
    Queue* q = malloc(sizeof(Queue));
    q->head = NULL;
    q->tail = NULL;
    int queue_size = 0;

    for (int i = 0; i < pages_size; i ++)
    {   
        if (!queue_contains(q, pages[i]))
        {
            page_faults ++;
            if (queue_size == mem_size)
            {
                queue_remove(q);
            }
            else
            {
                queue_size ++;
            }
            queue_add(q, pages[i]);
        }
    }

    return page_faults;
}

// Simulates second chance algorithm
int sim_second_chance(int mem_size, int pages[], int pages_size)
{
    int page_faults = 0;
    Queue* q = malloc(sizeof(Queue));
    q->head = NULL;
    q->tail = NULL;
    int queue_size = 0;

    for (int i = 0; i < pages_size; i ++)
    {
        if (queue_contains(q, pages[i]))
        {
            queue_mark(q, pages[i]);
        }
        else
        {
            page_faults ++;
            if (queue_size == mem_size)
            {
                queue_second_chance(q);
            }
            else
            {
                queue_size ++;
            }
            queue_add(q, pages[i]);
        }
    }

    return page_faults;
}

// Simulates clock algorithm
int sim_clock(int mem_size, int pages[], int pages_size)
{
    int page_faults = 0;
    CircularArrayEle arr[mem_size];
    for (int i = 0; i < mem_size; i ++)
    {
        arr[i].page = 0;
        arr[i].mark = 0;
    }

    CircularArray* c = malloc(sizeof(CircularArray));
    c->arr = arr;
    c->arr_size = mem_size;
    c->i = 0;
    circ_print(c);

    for (int i = 0; i < pages_size; i++)
    {
        if (circ_contains(c, pages[i]))
        {
            circ_mark(c, pages[i]);
        }
        else
        {
            page_faults ++;
            circ_second_chance(c, pages[i]);
            c->i = (c->i + 1) % c->arr_size;
        }
        printf("Page: %d\t", pages[i]);
        circ_print(c);
    }
    return page_faults;
}

int main() {
    int arr[] = {1, 1, 3, 4, 1, 2, 5, 1};
    int arr_size = sizeof(arr)/sizeof(arr[0]);

    int fifo_results = sim_fifo(3, arr, arr_size);
    int second_chance_results = sim_second_chance(3, arr, arr_size);
    int clock_results = sim_clock(3, arr, arr_size);

    printf("FIFO produced %d page faults\n", fifo_results);
    printf("Second chance produced %d page faults\n", second_chance_results);
    printf("Clock produced %d page faults\n", clock_results);

    return 0;
}
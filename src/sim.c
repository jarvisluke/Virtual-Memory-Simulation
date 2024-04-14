#include <stdio.h>
#include "queue.h"

// Simulates first in, first out algorithm
int sim_fifo(int mem_size, int data[], int data_size)
{
    int page_faults = 0;
    Queue* q = malloc(sizeof(Queue));
    q->head = NULL;
    q->tail = NULL;
    queue_clear_all_marks(q);
    int queue_size = 0;

    for (int i = 0; i < data_size; i ++)
    {   
        if (!queue_check(q, data[i]))
        {
            page_faults ++;
            if (queue_size == mem_size)
            {
                queue_pop(q);
            }
            else
            {
                queue_size ++;
            }
            queue_push(q, data[i]);
        }
    }

    return page_faults;
}

// Simulates second chance algorithm
int sim_second_chance(int mem_size, int data[], int data_size)
{
    int page_faults = 0;
    Queue* q = malloc(sizeof(Queue));
    q->head = NULL;
    q->tail = NULL;
    queue_clear_all_marks(q);
    int queue_size = 0;

    for (int i = 0; i < data_size; i ++)
    {
        if (queue_check(q, data[i]))
        {
            queue_mark(q, data[i]);
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
            queue_push(q, data[i]);
        }
        printf("Data: %d   ", data[i]);
        print_queue(q);
        
    }

    return page_faults;
}

int main() {
    int arr[] = {1, 1, 3, 4, 1, 2, 5, 1};

    int arr_size = sizeof(arr)/sizeof(arr[0]);

    int fifo_results = sim_fifo(3, arr, arr_size);
    int second_chance_results = sim_second_chance(3, arr, arr_size);


    printf("FIFO produced %d page faults\n", fifo_results);
    printf("Second chance produced %d page faults\n", second_chance_results);

    return 0;
}
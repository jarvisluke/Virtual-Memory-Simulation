#include <stdio.h>
#include "queue.h"

int sim_fifo(int mem_size, int data[], int data_size) {
    int page_faults = 0;
    Queue* q = malloc(sizeof(Queue));
    q->head = NULL;
    int queue_size = 0;

    for (int i = 0; i < data_size; i ++) {
        if (in_queue(q, data[i]) )
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

        
        printf("i: %d, Data: %d, Queue size: %d, Page faults: %d\n", i, data[i], queue_size, page_faults);
    }

    return page_faults;
}

int main() {
    int arr[] = {3, 7, 2, 5, 1, 8, 7, 2, 5, 1, 4, 0, 9, 6, 6, 3, 7, 2, 5, 1, 8, 7, 2, 5, 1, 4, 0, 9, 6, 6, 3, 11};
    int arr_size = sizeof(arr)/sizeof(arr[0]);
    int page_faults = sim_fifo(10, arr, arr_size);

    printf("FIFO produced %d page faults\n", page_faults);

    return 0;
}
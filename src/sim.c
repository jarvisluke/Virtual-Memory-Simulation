#include "queue.h"

#include <stdio.h>

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

int main() {
    return 0;
}
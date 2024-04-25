#include <stdio.h>
#include "data_struct.h"

// Simulates first in, first out algorithm
int sim_fifo(int mem_size, int pages[], int pages_size)
{
    int page_faults = 0;
    List* q = malloc(sizeof(List));
    q->head = NULL;
    q->tail = NULL;
    int q_size = 0;

    for (int i = 0; i < pages_size; i ++)
    {   
        if (!queue_contains(q, pages[i]))
        {
            page_faults ++;
            if (q_size == mem_size)
            {
                queue_pop(q);
            }
            else
            {
                q_size ++;
            }
            queue_push(q, pages[i]);
        }
    }

    return page_faults;
}

// Simulates second chance algorithm
int sim_second_chance(int mem_size, int pages[], int pages_size)
{
    int page_faults = 0;
    List* q = malloc(sizeof(List));
    q->head = NULL;
    q->tail = NULL;
    int q_size = 0;

    for (int i = 0; i < pages_size; i ++)
    {
        if (queue_contains(q, pages[i]))
        {
            queue_mark(q, pages[i]);
        }
        else
        {
            page_faults ++;
            if (q_size == mem_size)
            {
                queue_second_chance(q);
            }
            else
            {
                q_size ++;
            }
            queue_push(q, pages[i]);
        }
    }

    return page_faults;
}

// Simulates clock algorithm
int sim_clock(int mem_size, int pages[], int pages_size)
{
    int page_faults = 0;
    ArrayNode arr[mem_size];
    for (int i = 0; i < mem_size; i ++)
    {
        arr[i].page = 0;
        arr[i].mark = 0;
        arr[i].counter = 0;
    }

    CircularArray* c = malloc(sizeof(CircularArray));
    c->arr = arr;
    c->arr_size = mem_size;
    c->i = 0;

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
    }
    return page_faults;
}

// Simulates least recently used algorithm
int sim_lru(int mem_size, int pages[], int pages_size)
{
    int page_faults = 0;
    List* q = malloc(sizeof(List));
    q->head = NULL;
    q->tail = NULL;
    int q_size = 0;

    for (int i = 0; i < pages_size; i ++)
    {   
        if (queue_contains(q, pages[i]))
        {
            queue_move_to_tail(q, pages[i]);
        }
        else
        {
            page_faults ++;
            if (q_size == mem_size)
            {
                queue_pop(q);
            }
            else
            {
                q_size ++;
            }
            queue_push(q, pages[i]);
        }
    }

    return page_faults;
}

// Simulats not frequently used algorithm
int sim_nfu(int mem_size, int pages[], int pages_size, int clock)
{
    int page_faults = 0;
    int timer = 0;
    ArrayNode arr[mem_size];    
    for (int i = 0; i < mem_size; i ++)
    {
        arr[i].page = 0;
        arr[i].mark = 0;
    }
    int arr_size = 0;

    for (int i = 0; i < pages_size; i ++)
    {   
        int index = arr_contains(arr, mem_size, pages[i]);
        if (index != -1)
        {
            arr[index].mark = 1;
        }
        else
        {
            page_faults ++;
            if (arr_size == mem_size)
            {
                arr_replace_lowest(arr, mem_size, pages[i]);
            }
            else
            {
                arr[arr_size++].page = pages[i];
            }
        }

        if (timer == clock)
        {
            arr_increment_marked(arr, mem_size);
            timer = 0;
        }
        else
        {
            timer ++;
        }
    }

    return page_faults;
}

// Simulates NFU algorithm with aging
int sim_aging(int mem_size, int pages[], int pages_size, int clock)
{
    int page_faults = 0;
    int timer = 0;
    ArrayNode arr[mem_size];    
    for (int i = 0; i < mem_size; i ++)
    {
        arr[i].page = 0;
        arr[i].mark = 0;
    }
    int arr_size = 0;

    for (int i = 0; i < pages_size; i ++)
    {   
        int index = arr_contains(arr, mem_size, pages[i]);
        if (index != -1)
        {
            arr[index].mark = 1;
        }
        else
        {
            page_faults ++;
            if (arr_size == mem_size)
            {
                arr_replace_lowest(arr, mem_size, pages[i]);
            }
            else
            {
                arr[arr_size++].page = pages[i];
            }
        }

        if (timer == clock)
        {
            arr_age_marked(arr, mem_size, clock);
            timer = 0;
        }
        else
        {
            timer ++;
        }
    }

    return page_faults;
}

int main() {
    int arr[] = {1, 1, 1, 1, 1, 1, 1, 1, 3, 5, 4, 2, 3, 13, 14, 2, 2, 3, 4, 5, 6, 7, 2, 9, 10, 11, 3, 3, 3};
    int arr_size = sizeof(arr)/sizeof(arr[0]);
    int mem_size = 5;
    int clock = 5;

    int fifo_results = sim_fifo(3, arr, arr_size);
    printf("FIFO produced %d page faults\n", fifo_results);

    int second_chance_results = sim_second_chance(mem_size, arr, arr_size);
    printf("Second chance produced %d page faults\n", second_chance_results);

    int clock_results = sim_clock(mem_size, arr, arr_size);
    printf("Clock produced %d page faults\n", clock_results);

    int lru_results = sim_lru(mem_size, arr, arr_size);
    printf("LRU produced %d page faults\n", lru_results);

    int nfu_results = sim_nfu(mem_size, arr, arr_size, clock);
    printf("NFU produced %d page faults\n", nfu_results);

    int age_results = sim_aging(mem_size, arr, arr_size, clock);
    printf("AGE produced %d page faults\n", age_results);

    return 0;
}
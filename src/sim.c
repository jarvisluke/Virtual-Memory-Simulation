#include <stdio.h>
#include "data_struct.h"
#include "patterns.h"

// Simulates first in, first out algorithm
int sim_fifo(int mem_size, int pages[], int pages_size)
{
    int page_faults = 0;
    Queue* q = malloc(sizeof(Queue));
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
    Queue* q = malloc(sizeof(Queue));
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
    Queue* q = malloc(sizeof(Queue));
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
        int index = arr_contains_node(arr, mem_size, pages[i]);
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
    if (clock > 32)
    {
        printf("Clock: {%d} must be lower than 32", clock);
        return -1;
    }
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
        int index = arr_contains_node(arr, mem_size, pages[i]);
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

// Simulates optimal page replacement
int sim_optimal(int mem_size, int pages[], int pages_size)
{
    int page_faults = 0;
    int arr[mem_size];
    int arr_size = 0;
    int index;

    for (int i = 0; i < pages_size; i ++)
    {
        index = arr_contains(arr, mem_size, pages[i]);
        if (index == -1)
        {
            page_faults ++;
            if (arr_size == mem_size)
            {
                arr_replace_furthest(arr, mem_size, pages, pages_size, i);
            }
            else
            {
                arr[arr_size++] = pages[i];
            }
        } 
    }

    return page_faults;
}

int sim_random(int mem_size, int pages[], int pages_size)
{
    int page_faults = 0;
    int arr[mem_size];
    int arr_size = 0;

    int index;
    for (int i = 0; i < pages_size; i ++)
    {
        index = arr_contains(arr, mem_size, pages[i]);
        if (index == -1)
        {
            if (arr_size == mem_size)
            {       
                page_faults ++;
                arr[rand() % arr_size] = pages[i];
            }
            else
            {
                arr[arr_size++] = pages[i];
            }
        }
    }
    return page_faults;
}


void run_simulations(int mem_size, int pages_size, int page_max)
{
    int pages[5][pages_size];
    fill_looping_pattern(pages[0], pages_size, page_max);
    fill_stack_access_pattern(pages[1], pages_size, page_max);
    fill_temporal_locality_pattern(pages[2], pages_size, page_max, 72);
    fill_random_pattern(pages[3], pages_size, page_max);
    fill_front_heavy_access_pattern(pages[4], pages_size, page_max);

    int clock = 5;

    for (int i = 0; i < 5; i ++)
    {
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        //arr_print(pages[i], pages_size);

        int fifo_results = sim_fifo(mem_size, pages[i], pages_size);
        printf("FFO produced %d page faults\n", fifo_results);

        int random_results = sim_random(mem_size, pages[i], pages_size);
        printf("Random produced %d page faults\n", random_results);

        // int second_chance_results = sim_second_chance(mem_size, pages[i], pages_size);
        // printf("Second chance produced %d page faults\n", second_chance_results);

        int clock_results = sim_clock(mem_size, pages[i], pages_size);
        printf("Clock produced %d page faults\n", clock_results);

        int lru_results = sim_lru(mem_size, pages[i], pages_size);
        printf("LRU produced %d page faults\n", lru_results);

        int nfu_results = sim_nfu(mem_size, pages[i], pages_size, clock);
        printf("NFU produced %d page faults\n", nfu_results);

        int age_results = sim_aging(mem_size, pages[i], pages_size, clock);
        printf("Aging produced %d page faults\n", age_results);

        int optimal_results = sim_optimal(mem_size, pages[i], pages_size);
        printf("Optimal produced %d page faults\n", optimal_results);
    }
}

int main() {
    printf("Page frame size 8\n");
    run_simulations(8, 1000, 20);
    printf("Page frame size 10\n");
    run_simulations(10, 1000, 20);
    printf("Page frame size 12\n");
    run_simulations(12, 1000, 20);
    printf("Page frame size 15\n");
    run_simulations(15, 1000, 20);

    return 0;
}
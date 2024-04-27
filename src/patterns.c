#include <stdio.h>
#include "patterns.h"

// Fills arr with a looping pattern sequence from 0 - max
void fill_looping_pattern(int arr[], int arr_size, int max)
{
    for (int i = 0; i < arr_size; i ++)
    {
        arr[i] = i % (max + 1);
    }
}

// Fills arr with a temporal locality pattern sequence from 0 - max
void fill_temporal_locality_pattern(int arr[], int arr_size, int max, int locality)
{
    int i = 0;
    while(i < arr_size)
    {
        int current = i % (max + 1);
        int l = locality / 2;

        for (int j = 0; j < 5; j ++)
        {
            if (i < arr_size)
            {
                if (l < (rand() % locality))
                {
                    arr[i] = current;
                }
                else
                {
                    arr[i] = i % (max + 1);
                }
                i ++;
            }
            else
            {
                return;
            }
        }
    }
}

// Fills arr with a stack access pattern sequence from 0 - max
void fill_stack_access_pattern(int arr[], int arr_size, int max)
{
    int i = 0;
    while (i < arr_size) // iterate through arr
    {
        for (int j = 0; j <= max && i < arr_size; j ++) // iterate through first half of max
        {
            arr[i++] = j;
        }
        for (int j = 0; j <= max && i < arr_size; j ++) // iterate through other half of max
        {
            arr[i++] = arr[max - j];
        }
    } // using while (instead of for) so i does not iterate after iterating through max
}

// Fills arr with a random sequence from 0 - max
void fill_random_pattern(int arr[], int arr_size, int max)
{
    for (int i = 0; i < arr_size; i ++)
    {
        arr[i] = rand() % (max + 1);
    }
}

void fill_front_heavy_access_pattern(int arr[], int arr_size, int max)
{
    for (int i = 0; i < arr_size; i ++)
    {
        if (i < arr_size / 3)
        {
            arr[i] = (rand() % (3));
        }
        else
        {
            arr[i] = (rand() % max) + 3;
        }
    }
}
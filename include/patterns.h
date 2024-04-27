#ifndef PATTERNS_H
#define PATTERNS_H

#include <stdlib.h>

// void fill_sequential_access_pattern(int arr[], int arr_size, int max);
// void fill_spatial_locality_pattern(int arr[], int arr_size, int max, int locality);
void fill_temporal_locality_pattern(int arr[], int arr_size, int max, int locality);
void fill_looping_pattern(int arr[], int arr_size, int max);
void fill_random_pattern(int arr[], int arr_size, int max);
void fill_stack_access_pattern(int arr[], int arr_size, int max);
void fill_front_heavy_access_pattern(int arr[], int arr_size, int max);
// void fill_working_set(int arr_size, int max);

#endif // PATTERNS_H
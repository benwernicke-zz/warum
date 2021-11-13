#ifndef RANGE_BASED_H
#define RANGE_BASED_H
#include <stdlib.h>

static void for_each(int* arr, size_t arr_size, void (*f)(int));

#endif // RANGE_BASED_H

#ifndef RANGE_BASED_H_IMPLEMENTATION
#define RANGE_BASED_H_IMPLEMENTATION

static void for_each(int* arr, size_t arr_size, void (*f)(int))
{
    for (int i = 0; i < arr_size; i++)
        (*f)(arr[i]);
}

static void transform(int* arr, size_t arr_size, int (*f)(int))
{
    for (int i = 0; i < arr_size; i++)
        arr[i] = (*f)(arr[i]);
}

static void reverse(int* arr, size_t arr_size)
{
    int temp;
    for (int i = 0; i < arr_size / 2; i++) {
        temp = arr[i];
        arr[i] = arr[arr_size - i];
    }
}
#endif // IMPLEMENTATION

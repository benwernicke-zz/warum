#ifndef RANGE_BASED_H
#define RANGE_BASED_H
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static void for_each(int* arr, size_t arr_size, void (*f)(int));
#endif // RANGE_BASED_H

#ifndef RANGE_BASED_H_IMPLEMENTATION
#define RANGE_BASED_H_IMPLEMENTATION

// TODO: Variable number of args - for "capture"
static void for_each(int* arr, size_t arr_size, void (*f)(int))
{
    for (int i = 0; i < arr_size; i++)
        (*f)(arr[i]);
}

static void reduce(int* arr, size_t arr_size, int (*f)(int, int))
{
    for (int i = 0; i < arr_size; i++)
        arr[0] = (*f)(arr[i], arr[0]);
}

inline int add(int a, int b)
{
    return a + b;
}

static int sum(int* arr, size_t arr_size)
{
    reduce(arr, arr_size, &add);
    return arr[0];
}

inline static int mult(int a, int b)
{
    return a * b;
}

static int product(int* arr, size_t arr_size)
{
    reduce(arr, arr_size, &mult);
    return arr[0];
}

static void for_each_ptr(int* arr, size_t arr_size, void (*f)(int*))
{
    for (int i = 0; i < arr_size; i++)
        (*f)(&arr[i]);
}

static void transform(int* arr, size_t arr_size, int (*f)(int))
{
    for (int i = 0; i < arr_size; i++)
        arr[i] = (*f)(arr[i]);
}

static void transform_if(int* arr, size_t arr_size, bool (*cond)(int), int (*f)(int))
{
    for (int i = 0; i < arr_size; i++)
        if ((*cond)(arr[i]))
            arr[i] = (*f)(arr[i]);
}

static void reverse(int* arr, size_t arr_size)
{
    int temp;
    for (int i = 0; i < arr_size / 2; i++) {
        arr[i] = arr[i] + arr[arr_size - i - 1];
        arr[arr_size - i - 1] = arr[i] - arr[arr_size - i - 1];
        arr[i] = arr[i] - arr[arr_size - i - 1];
    }
}

static int* find(int* arr, size_t arr_size, int element)
{
    for (int i = 0; i < arr_size; i++) {
        if (arr[i] == element)
            return &arr[i];
    }
    return NULL;
}

static void copy(int* src, size_t src_size, int* dest)
{
    memcpy(dest, src, sizeof(int) * src_size);
}

static void fill(int* arr, size_t arr_size, int value)
{
    for (int i = 0; i < arr_size; i++) {
        arr[i] = value;
    }
}

static bool equal(int* arr1, size_t arr1_size, int* arr2)
{
    for (int i = 0; i < arr1_size; i++) {
        if (arr1[i] != arr2[i])
            return false;
    }
    return true;
}

static int* find_if(int* arr, size_t arr_size, bool (*f)(int))
{
    for (int i = 0; i < arr_size; i++) {
        if ((*f)(arr[i]))
            return &arr[i];
    }
    return NULL;
}
#endif // IMPLEMENTATION

#include <stdio.h>

#define compose(arr_name, arr_size, ...) void (*arr_name[arr_size])(void*) = { __VA_ARGS__ };

#define calc(arr_name, arr_size, var_name) \
    for (int i = 0; i < arr_size; i++)     \
        arr_name[i](var_name);

void add_one(void* a)
{
    (*(int*)a)++;
}

void time_two(void* a)
{
    (*(int*)a) *= 2;
}

void arr_time_two(void* a)
{
    for (int i = 0; i < 10; i++)
        ((int*)a)[i] *= 2;
}

void sum(void* a)
{
    int sum = 0;
    for (int i = 0; i < 10; i++)
        sum += ((int*)a)[i];
    *(int*)a = sum;
}

int main()
{
    /*int a = 34;*/
    int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    compose(fn, 2, &arr_time_two, &sum);
    calc(fn, 2, arr);
    printf("a: %d\n", *arr);
    return 0;
}

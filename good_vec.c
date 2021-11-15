#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

size_t* vec_create()
{
    size_t* vec_wrapper = (size_t*)malloc(4 * sizeof(size_t));
    vec_wrapper[0] = 0; // elements in buffer
    vec_wrapper[1] = 1; // chunks allocated
    return &vec_wrapper[2];
}

inline size_t* vec_wrapper(void* vec)
{
    return ((size_t*)vec - 2);
}

void vec_push(void*)

    int main(void)
{
    int* vec = (int*)vec_create();
    vec[0] = 69;
    vec[1] = 420;
    return 0;
}

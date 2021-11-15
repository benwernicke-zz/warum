#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#pragma pack(1)

typedef unsigned char byte;

void* vec_create()
{
    void** vec_wrapper = (void**)malloc(3 * sizeof(void*));

    vec_wrapper[0] = malloc(1 * sizeof(size_t));
    vec_wrapper[1] = malloc(1 * sizeof(size_t));
    vec_wrapper[2] = malloc(4 * sizeof(byte));

    *(size_t*)vec_wrapper[0] = 0; // size of array in elements
    *(size_t*)vec_wrapper[1] = 1; // actual allocated number of bytes
    return &vec_wrapper[2];
}

void** vec_wrapper_address(void* vec_buffer)
{
    return ((void**)vec_buffer) - 2;
}

void vec_push(void* vec, char val)
{
    void** vec_wrapper = vec_wrapper_address(vec);
    ((char*)vec)[*(size_t*)vec_wrapper[0]] = val;
    (*(size_t*)vec_wrapper[0])++;
}

int main()
{
    /*void** vec_wrapper = vec_create();*/
    char* vec = (char*)vec_create();
    /*void** vec_wrapper = vec_wrapper_address(vec);*/
    vec_push(vec, 'b');
    vec_push(vec, 'e');
    vec_push(vec, 'n');
    vec_push(vec, '\0');
    printf("%s\n", vec);
    return 0;
}

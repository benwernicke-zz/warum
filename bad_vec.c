#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma pack(1)

typedef unsigned char byte;

void* vec_create()
{
    void** vec_wrapper = (void**)malloc(3 * sizeof(void*));

    vec_wrapper[0] = malloc(1 * sizeof(size_t));
    vec_wrapper[1] = malloc(1 * sizeof(size_t));
    vec_wrapper[2] = malloc(1 * sizeof(byte));

    *(size_t*)vec_wrapper[0] = 0; // size of array in elements
    *(size_t*)vec_wrapper[1] = 1; // actual allocated number of bytes
    return &vec_wrapper[2];
}

void** vec_wrapper_address(void* vec_buffer)
{
    return ((void**)vec_buffer) - 2;
}

void* resize(void* vec, size_t n_bytes)
{
    void** vec_wrapper = vec_wrapper_address(vec);
    vec_wrapper[2] = (byte*)realloc(vec_wrapper[2], n_bytes * sizeof(byte));
    *(size_t*)vec_wrapper[1] = n_bytes;
    return &vec_wrapper[2];
}

int main()
{
    /*void** vec_wrapper = vec_create();*/
    char* vec = (char*)vec_create();
    void** vec_wrapper = vec_wrapper_address(vec);
    vec[0] = 'B';
    vec_wrapper[2] = realloc(&vec, 4);
    vec = (char*)&vec_wrapper[2];
    vec[1] = 'e';
    vec[2] = 'n';
    vec[3] = '\0';
    printf("%s\n", vec);
    return 0;
}

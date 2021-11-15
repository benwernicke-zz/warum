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

// TODO: this is shit

void vec_resize(void* vec, size_t n_bytes)
{
    void** vec_wrapper = vec_wrapper_address(vec);
    /*vec_wrapper[2] = realloc(&vec_wrapper[2], n_bytes);*/
    /**(size_t*)vec_wrapper[1] = n_bytes;*/
    void** new_vec_wrapper = (void**)malloc(3 * sizeof(void*));
    new_vec_wrapper[0] = malloc(1 * sizeof(size_t));
    new_vec_wrapper[1] = malloc(1 * sizeof(size_t));
    new_vec_wrapper[2] = malloc(1 * sizeof(byte));

    *(size_t*)new_vec_wrapper[0] = *(size_t*)vec_wrapper[0]; // size of array in elements
    *(size_t*)new_vec_wrapper[1] = n_bytes;                  // actual allocated number of bytes
    new_vec_wrapper[2] = malloc(n_bytes);
    memcpy(new_vec_wrapper[2], vec_wrapper[2], n_bytes < *(size_t*)vec_wrapper[1] ? n_bytes : *(size_t*)vec_wrapper[1]);
    vec = &new_vec_wrapper[2];
}

void vec_push(void* vec, char val)
{
    void** vec_wrapper = vec_wrapper_address(vec);
    if (*(size_t*)vec_wrapper[0] >= *(size_t*)vec_wrapper[1])
        vec_resize(vec, *(size_t*)vec_wrapper[1] * 2 + 1);
    ((char*)vec)[(*(size_t*)vec_wrapper[0])++] = val;
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

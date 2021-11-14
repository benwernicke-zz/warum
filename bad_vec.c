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
    vec_wrapper[2] = malloc(1 * sizeof(byte));

    *(size_t*)vec_wrapper[0] = 0; // size of array in elements
    *(size_t*)vec_wrapper[1] = 1; // actual allocated number of bytes
    return &vec_wrapper[3];
}

void** vec_wrapper_address(void* vec_buffer)
{
    return ((void**)vec_buffer) - 2;
}

void vec_push(void* vec, char val)
{
    void** vec_wrapper = vec_wrapper_address(vec);
    if (*(size_t*)vec_wrapper[0] >= *(size_t*)vec_wrapper[1])
        vec_wrapper[2] = (char*)realloc(vec_wrapper[2], (*(size_t*)vec_wrapper[1] *= 2) * sizeof(byte));
    /*vec_wrapper[2 + *(size_t*)vec_wrapper[0]] = val;*/
    *(char*)&vec_wrapper[2 + *(size_t*)vec_wrapper[0]] = val;
}

int main()
{
    /*void** vec_wrapper = vec_create();*/
    char* vec = (char*)vec_create();
    vec_push(vec, 'b');
    vec_push(vec, 'e');
    vec_push(vec, 'n');
    vec_push(vec, '\0');

    /*vec_buffer[0] = 'b';*/
    /*vec_buffer[1] = 'e';*/
    /*vec_buffer[2] = 'n';*/
    /*vec_buffer[3] = '\0';*/
    /*void** test = vec_wrapper_address(vec_buffer);*/
    /*printf("%ld, %ld\n", *(size_t*)test[0], *(size_t*)test[1]);*/
    printf("%s\n", vec);
    return 0;
}

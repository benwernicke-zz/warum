#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#pragma pack(1)

typedef unsigned char byte;

void* vec_create()
{
    void** vec = (void**)malloc(3 * sizeof(void*));
    *(size_t*)vec[0] = 69;  // size
    *(size_t*)vec[1] = 420; // bytes alloced
    vec[2] = NULL;
    return &vec[2];
}

int main()
{
    int* vec = (int*)vec_create();
    return 0;
}

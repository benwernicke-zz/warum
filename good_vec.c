#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char byte;

void* vec_create()
{
    byte* vec_buffed = (byte*)malloc(2 * sizeof(size_t) + 1);
    ((size_t*)vec_buffed)[0] = 0;
    ((size_t*)vec_buffed)[1] = 1;
    return &vec_buffed[2 * sizeof(size_t)];
}

byte* vec_wrapper(void* vec)
{
    return (vec - (2 * sizeof(size_t) + 1));
}

void vec_free(void* vec)
{
    free(vec_wrapper(vec));
    vec = NULL;
}

void* vec_push(void* vec, char val)
{
    byte* vec_buffed = vec_wrapper(vec);
    if (((size_t*)vec_buffed)[0] >= ((size_t*)vec_buffed)[1])
        vec_buffed = (byte*)realloc(vec_buffed, ((size_t*)vec_buffed)[1] * 2);
}

int main(void)
{
    char* vec = vec_create();
    vec_free(vec);
    return 0;
}

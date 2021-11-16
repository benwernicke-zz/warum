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

size_t vec_size(void* vec)
{
    return ((size_t*)vec_wrapper(vec))[0];
}

size_t vec_scope(void* vec)
{
    return ((size_t*)vec_wrapper(vec))[1];
}

void vec_free(void* vec)
{
    free(vec_wrapper(vec));
    vec = NULL;
}

void* vec_push(void* vec, char val)
{
    byte* vec_buffed = vec_wrapper(vec);
    /*if (vec_size(vec) >= vec_scope(vec))*/
    /*vec_buffed = (byte*)realloc(vec_buffed, vec_scope(vec) * 2);*/
    vec_buffed[2 * sizeof(size_t) + vec_size(vec)] = val;
    return &vec_buffed[2];
}

void* vec_upsize(size_t n_bytes, byte* old_vec_buffed)
{
    byte* new_vec_buffed = (byte*)malloc(2 * sizeof(size_t) + ((size_t*)old_vec_buffed)[1] * 2);
    ((size_t*)new_vec_buffed)[0] = ((size_t*)old_vec_buffed)[0];
    ((size_t*)new_vec_buffed)[1] = n_bytes;

    memcpy(new_vec_buffed, old_vec_buffed, 2 * (sizeof(size_t) + ((size_t*)old_vec_buffed)[0]));
    free(old_vec_buffed);
    old_vec_buffed = NULL;
    return &new_vec_buffed[2];
}

int main(void)
{
    char* vec = vec_create();
    byte* vec_buffed = vec_wrapper(vec);

    /*vec = vec_push(vec, 'B');*/
    vec = vec_upsize(10, vec_buffed);

    /*vec = vec_push(vec, 'e');*/
    /*vec = vec_push(vec, 'n');*/
    /*vec = vec_push(vec, '\0');*/
    printf("%s\n", vec);
    vec_free(vec);
    return 0;
}

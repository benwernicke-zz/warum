#include "range_based.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    size_t size;
    size_t scope;
    int* buffer;
} vec_t;

vec_t* vec_create(size_t scope)
{
    vec_t* v = (vec_t*)malloc(1 * sizeof(vec_t));
    v->size = 0;
    v->scope = scope + 1;
    v->buffer = (int*)malloc(v->scope * sizeof(int));
    return v;
}

void vec_free(vec_t* v)
{
    free(v->buffer);
    free(v);
    v = NULL;
}

void vec_push(vec_t* v, int val)
{
    if (v->size >= v->scope)
        v->buffer = (int*)realloc(v->buffer, (v->scope *= 2) * sizeof(int));
    v->buffer[v->size++] = val;
}

void vec_rem(vec_t* v, size_t index)
{
    free(v->buffer);
    free(v);
    v = NULL;
    v->size--;
    for (int i = index; i < v->size; i++)
        v->buffer[i] = v->buffer[i + 1];
}

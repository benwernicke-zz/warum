#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define vec_make(cname) vec_t cname = { .size = 0, .scope = 0 };

#define ASSERT(condition, ...)        \
    if (!(condition)) {               \
        fprintf(stderr, __VA_ARGS__); \
        exit(1);                      \
    }

typedef struct
{
    size_t size;
    size_t scope;
    int* body;
} vec_t;

void vec_push(vec_t* vec, int val)
{
    if (vec->size >= vec->scope)
        vec->body = (int*)realloc(vec->body, (vec->scope += 50) * sizeof(int));
    vec->body[vec->size++] = val;
}

void vec_rem(vec_t* vec, size_t index)
{
    if (index >= vec->size)
        return;
    for (int i = index + 1; i < vec->size; i++)
        vec->body[i - 1] = vec->body[i];
    vec->size--;
}

int vec_get(vec_t* vec, size_t index)
{
    ASSERT(index < vec->size, "DIGGA Vec");
    return vec->body[index];
}

void vec_destroy(vec_t* vec)
{
    free(vec->body);
    free(vec);
    vec = NULL;
}

int main()
{
    return 0;
}

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char byte;

typedef struct
{
    size_t bytes_allocated;
    size_t bytes_used;
    byte* buffer;
} vector_t;

byte* get_vec_wrapper(void* vec)
{
    return ((byte*)vec - 2 * sizeof(size_t) - 1);
}

void vec_upsize(void* vec, size_t n_bytes)
{
    byte* vec_wrapper = get_vec_wrapper(vec);
    vec_wrapper = (byte*)realloc(vec_wrapper, n_bytes);
    vec = &vec_wrapper[2 * sizeof(size_t) + 1];
}

size_t vec_allocated_bytes(void* vec)
{
    return ((size_t*)get_vec_wrapper(vec))[1];
}

size_t vec_used_bytes(void* vec)
{
    return ((size_t*)get_vec_wrapper(vec))[0];
}

// TODO: make this universal
//
/*#define vec_push(vec_name, val) _vec_push(vec_name, *(unsigned long*)&val, sizeof(typeof(*vec_name)));*/
/*void vec_push(void* vec, char val)*/
/*{*/
/*if (vec_used_bytes(vec) >= vec_allocated_bytes(vec))*/
/*vec_upsize(vec, vec_allocated_bytes(vec) * 2);*/
/*((char*)vec)[vec_used_bytes(vec)] = val;*/
/*((size_t*)get_vec_wrapper(vec))[0]++;*/
/*}*/
#define vec_push(vec_name, val)                                    \
    {                                                              \
        (vec_name);                                                \
        (val);                                                     \
        typeof(*vec_name) tmp_val = val;                           \
        byte tmp_bytes[sizeof(typeof(*vec_name))];                 \
        memcpy(tmp_bytes, &tmp_val, sizeof(typeof(*vec_name)));    \
        _vec_push(vec_name, tmp_bytes, sizeof(typeof(*vec_name))); \
    }

void _vec_push(void* vec, byte* val, size_t n_bytes)
{
    if (vec_used_bytes(vec) + n_bytes >= vec_allocated_bytes(vec))
        vec_upsize(vec, vec_allocated_bytes(vec) * 2 + n_bytes);
    memcpy(&((byte*)vec)[vec_used_bytes(vec)], val, n_bytes);
    ((size_t*)get_vec_wrapper(vec))[0] += n_bytes;
}

void* vec_create()
{
    byte* vec_wrapper = (byte*)malloc(2 * sizeof(size_t) + 2);
    ((size_t*)vec_wrapper)[0] = 0;
    ((size_t*)vec_wrapper)[1] = 2 * sizeof(size_t) + 1;
    return &vec_wrapper[2 * sizeof(size_t) + 1];
}

void vec_free(void* vec)
{
    free(get_vec_wrapper(vec));
}

int main()
{
    /*char* vec = vec_create();*/
    /*vec_push(vec, 'B');*/
    /*vec_push(vec, 'e');*/
    /*vec_push(vec, 'n');*/
    /*vec_push(vec, '\0');*/
    int* vec = vec_create();
    vec_push(vec, 69);
    vec_push(vec, 420);

    printf("%ld\n", vec_used_bytes(vec));
    printf("%ld\n", vec_allocated_bytes(vec));
    printf("%d, %d\n", vec[0], vec[1]);
    /*printf("%s\n", vec);*/

    vec_free(vec);
    return 0;
}

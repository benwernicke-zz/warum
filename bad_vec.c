
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char byte;

//----------------------------------------------------------------------------------------------------
//  Get General Vector Ino

inline byte* vec_get_wrapper(void* vec)
{
    return ((byte*)vec - 2 * sizeof(size_t) - 1);
}

inline size_t vec_allocated_bytes(void* vec)
{
    return ((size_t*)vec_get_wrapper(vec))[1];
}

inline size_t vec_used_bytes(void* vec)
{
    return ((size_t*)vec_wrapper(vec))[0];
}

//----------------------------------------------------------------------------------------------------
// Vector Size Control

void vec_double(void* vec)
{
    byte* _vec_wrapper = vec_wrapper(vec);
    _vec_wrapper = (byte*)realloc(_vec_wrapper, vec_allocated_bytes(vec) * 2);
    ((size_t*)_vec_wrapper)[1] *= 2;
    vec = &_vec_wrapper[2 * sizeof(size_t) + 1];
}

void vec_upsize(void* vec, size_t n_bytes)
{
    if (vec_used_bytes(vec) + n_bytes < vec_allocated_bytes(vec))
        return;
    vec_double(vec);
    vec_upsize(vec, n_bytes);
}
//----------------------------------------------------------------------------------------------------
// Vec Constructor Destructor

void* vec_create()
{
    byte* _vec_wrapper = (byte*)malloc(2 * sizeof(size_t) + 2);
    ((size_t*)_vec_wrapper)[0] = 2 * sizeof(size_t);
    ((size_t*)_vec_wrapper)[1] = 2 * sizeof(size_t) + 1;
    return &_vec_wrapper[2 * sizeof(size_t) + 1];
}

void vec_free(void* vec)
{
    free(vec_wrapper(vec));
}
//----------------------------------------------------------------------------------------------------
// General vec usage

void _vec_push(void* vec, byte* val, size_t n_bytes)
{
    vec_upsize(vec, n_bytes);
    memcpy(&((byte*)vec)[vec_used_bytes(vec)], val, n_bytes);
    ((size_t*)vec_wrapper(vec))[0] += n_bytes;
}

//----------------------------------------------------------------------------------------------------

int main()
{
    /*char* vec = vec_create();*/
    /*vec_push(vec, 'B');*/
    /*vec_push(vec, 'e');*/
    /*vec_push(vec, 'n');*/
    /*vec_push(vec, '\0');*/
    int* vec = vec_create();
    int a = 69;
    int b = 420;

    union {
        int a;
        byte b[sizeof(int)];
    } i2b;
    i2b.a = a;
    _vec_push(vec, i2b.b, sizeof(int));
    i2b.a = b;
    _vec_push(vec, i2b.b, sizeof(int));
    /*_vec_push(vec, i2b.b, sizeof(int));*/

    /*vec_push(vec, 69);*/
    /*vec_push(vec, 420);*/
    /*vec_push(vec, 420);*/

    printf("%ld\n", vec_used_bytes(vec));
    printf("%ld\n", vec_allocated_bytes(vec));
    printf("%d, %d\n", vec[0], vec[1]);
    /*printf("%s\n", vec);*/

    vec_free(vec);
    return 0;
}

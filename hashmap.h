
#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    const char* key;
    int val;
} hashmap_element_t;

typedef struct
{
    hashmap_element_t** elems;
    size_t size;
} hashmap_t;

size_t hashmap_hash(hashmap_t* map, const char* key)
{
    size_t hash = 1;
    while (*key != '\0')
    {
        hash *= *key++;
    }

    return hash % map->size;
}

hashmap_element_t* hashmap_create_element(const char* key, int val)
{
    hashmap_element_t* element = (hashmap_element_t*) malloc(1 * sizeof(hashmap_element_t)); 
    element->key = key;
    element->val = val;
    return element;
}

hashmap_t* hashmap_create(size_t size)
{
    hashmap_t* map = (hashmap_t*) malloc(1 * sizeof(hashmap_t));
    map->elems = (hashmap_element_t**) calloc(size, sizeof(hashmap_element_t*));
    map->size = size;
    return map;
}

void hashmap_set(hashmap_t* map, const char* key, int val)
{
    size_t index = hashmap_hash(map, key);
    for (int i = 0; i < map->size; ++i)
    {
        if (map->elems[index] == NULL)
        {
            map->elems[index] = hashmap_create_element(key, val);
            return;
        }

        else if (strcmp(map->elems[index]->key, key) == 0)
        {
            map->elems[index]->val = val;
            return;
        }

        index = index < map->size ? index + 1 : 0;
    }

    printf("Warum digga?!\n");
    exit(1);
}

int* hashmap_get(hashmap_t* map, const char* key)
{
    size_t index = hashmap_hash(map, key);

    for (int i = 0; i < map->size; ++i)
    {
        if (strcmp(map->elems[index]->key, key) == 0)
        {
            return &map->elems[index]->val;
        }

        index = index < map->size ? index + 1 : 0;
    }

    return NULL;
}

void hashmap_destroy(hashmap_t* map)
{
    for (int i = 0; i < map->size; ++i)
    {
        free(map->elems[i]);
    }

    free(map->elems);
    free(map);
    map = NULL;
}

#endif // HASHMAP_H


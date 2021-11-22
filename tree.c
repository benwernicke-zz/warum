#include "../cryless/evil_vec.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node_t node_t;

struct node_t {
    int id;
    node_t** children;
};

node_t* tree_create(int id)
{
    node_t* n = (node_t*)malloc(1 * sizeof(node_t));
    n->children = (node_t**)vec_create();
    n->id = id;
    return n;
}

void tree_add_child(node_t* root, int id)
{
    node_t* n = tree_create(id);
    vec_push(root->children, n);
}

int main(void)
{
    return 0;
}

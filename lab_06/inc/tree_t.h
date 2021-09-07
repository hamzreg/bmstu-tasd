#ifndef TREE_T
#define TREE_T

typedef struct tree_t
{
    char *word;
    int height;
    struct tree_t *left;
    struct tree_t *right;
} tree_t;

#endif
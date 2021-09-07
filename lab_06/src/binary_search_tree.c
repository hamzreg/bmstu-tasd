#include "../inc/binary_search_tree.h"

tree_t *create_node(char *word, int h)
{
    tree_t *node = malloc(sizeof(tree_t));

    if (node)
    {
        node->height = h;
        node->left = NULL;
        node->right = NULL;
        node->word = malloc(sizeof(char *) * (strlen(word) + 1));
        strcpy(node->word, word);
    }

    return node;
}


tree_t *add_node(char *word, tree_t *tree, int *h)
{
    (*h)++;

    if (tree == NULL)
    {
        return create_node(word, *h);
    }
    else if (strcmp(word, tree->word) < 0)
    {
        tree->left = add_node(word, tree->left, h);
    }
    else if (strcmp(word, tree->word) > 0)
    {
        tree->right = add_node(word, tree->right, h);
    }

    return tree;
}


void free_tree(tree_t *tree)
{
    if(tree) 
    {
        free_tree(tree->left);
        free_tree(tree->right);
        free(tree);
    }
}


int create_tree(tree_t **root, FILE *f_in, int *count)
{
    *count = 0;
    char str[MAGIC_SIZE];

    fgets(str, MAGIC_SIZE, f_in);

    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';

    int h = -1;
    *root = add_node(str, *root, &h);
    (*count)++;

    while (fgets(str, MAGIC_SIZE, f_in) != NULL)
    {
        if (str[strlen(str) - 1] == '\n')
            str[strlen(str) - 1] = '\0';
        
        h = -1;
        *root = add_node(str, *root, &h);
        (*count)++;
    }

    return OK;
}


int find(tree_t *tree, char *word, int *count_cmprs)
{
    tree_t *head = tree;

    while (head != NULL)
    {
        (*count_cmprs)++;
        if (strcmp(head->word, word) == 0)
            return OK;

        if (strcmp(head->word, word) > 0)
            head = head->left;
        else if (strcmp(head->word, word) < 0)
            head = head->right;
    }

    return NOT_FOUND;
}

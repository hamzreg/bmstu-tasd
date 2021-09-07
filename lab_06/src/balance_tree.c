#include "../inc/balance_tree.h"

unsigned char height(tree_t *root)
{
    return root ? root->height : 0;
}


int bfactor(tree_t *root)
{
    return height(root->right) - height(root->left);
}


void fixheight(tree_t *root)
{
    unsigned char hl = height(root->left);
    unsigned char hr = height(root->right);
    root->height = (hl > hr ? hl : hr) + 1;
}


tree_t *rotateright(tree_t *tree)
{
    tree_t *node = tree->left;
    tree->left = node->right;
    node->right = tree;
    fixheight(tree);
    fixheight(node);

    return node;
}


tree_t *rotateleft(tree_t *tree)
{
    tree_t *node = tree->right;
    tree->right = node->left;
    node->left = tree;
    fixheight(tree);
    fixheight(node);

    return node;
}


tree_t *balance(tree_t *tree)
{
    fixheight(tree);

    if (bfactor(tree) == 2)
    {
        if (bfactor(tree->right) < 0)
            tree->right = rotateright(tree->right);
        return rotateleft(tree);
    }

    if (bfactor(tree) == -2)
    {
        if (bfactor(tree->left) > 0)
            tree->left = rotateleft(tree->left);

        return rotateright(tree);
    }

    return tree;
}


tree_t *add_balance(char *word, tree_t *tree, int *h)
{
    (*h)++;

    if (tree == NULL)
    {
        tree = create_node(word, *h);
    }
    else if (strcmp(word, tree->word) < 0)
    {
        tree->left = add_balance(word, tree->left, h);
    }
    else if (strcmp(word, tree->word) > 0)
    {
        tree->right = add_balance(word, tree->right, h);
    }

    return balance(tree);
}


int create_balance(tree_t **root, FILE *f_in)
{
    char str[MAGIC_SIZE];

    while (fgets(str, MAGIC_SIZE, f_in) != NULL)
    {
        if (str[strlen(str) - 1] == '\n')
            str[strlen(str) - 1] = '\0';

        int h = -1;
        *root = add_balance(str, *root, &h);
    }

    return OK;
}


int balance_find(tree_t *tree, char *word, int *count_cmprs)
{
    while (tree != NULL)
    {
        (*count_cmprs)++;
        if (strcmp(tree->word, word) == 0)
            return OK;

        if (strcmp(tree->word, word) > 0)
        {
            tree = tree->left;
        }
        else if (strcmp(tree->word, word) < 0)
        {
            tree = tree->right;
        }
    }

    return NOT_FOUND;
}

tree_t *balance_find_time(tree_t *tree, char *word, int *count_cmprs, uint64_t *time)
{
    uint64_t start = get_time_ticks();

    while (tree)
    {
        (*count_cmprs)++;
        if (strcmp(tree->word, word) == 0)
            break;

        if (strcmp(tree->word, word) > 0)
            tree = tree->right;
        else if (strcmp(tree->word, word) < 0)
            tree = tree->left;
    }

    *time += get_time_ticks() - start;

    return tree;
}
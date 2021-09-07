#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strings.h"
#include "tree_t.h"
#include "constants.h"
#include "errors.h"

#define _GNU_SOURCE

int create_tree(tree_t **root, FILE *f_in, int *count);

tree_t *create_node(char *word, int h);

void free_tree(tree_t *tree);

void print_tree(tree_t *tree, int place);

void treeprint(tree_t *p);

int find(tree_t *tree, char *word, int *count_cmprs);

#endif

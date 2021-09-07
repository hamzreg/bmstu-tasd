#ifndef BALANCE_TREE_H
#define BALANCE_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "time_function.h"
#include "tree_t.h"
#include "binary_search_tree.h"
#include "constants.h"
#include "errors.h"

#define _GNU_SOURCE

int create_balance(tree_t **root, FILE *f_in);

int balance_find(tree_t *tree, char *word, int *count_cmprs);

tree_t *balance_find_time(tree_t *tree, char *word, int *count_cmprs, uint64_t *time);

#endif
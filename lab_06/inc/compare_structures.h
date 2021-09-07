#ifndef COMPARE_STRUCTURES_H
#define COMPARE_STRUCTURES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../inc/binary_search_tree.h"
#include "../inc/balance_tree.h"
#include "../inc/hash.h"
#include "../inc/time_function.h"

int compare_structures(void);

int search_file(char *to_find, FILE *f, int *cmprs);

int fbytes(FILE *f);

#endif
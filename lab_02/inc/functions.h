#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdlib.h>
#include <string.h>
#include "structers.h"
#include "constants.h"
#include "errors.h"
#include "input_output.h"
#include <time.h>

int add_subscriber(table_t *table, char *record);

int delete_subscribers(table_t *table, char *record);

void sort_table_qsort(table_t *table, int type_sort, int start, int end);

void sort_table_bubble(table_t *table, int type_sort);

void print_sorts_result(table_t *table, char *filename);

#endif
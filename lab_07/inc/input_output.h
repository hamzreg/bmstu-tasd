#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include <stdio.h>
#include "graph.h"
#include "constants.h"
#include "return_codes.h"

void print_conditions(void);

void print_input_rules(void);

int check_read(int row, int column, int value, int size);

int input_graph(graph_t *graph);

int read_graph(graph_t *graph, const char *filename);

void print_graph(int **graph, const int size);

#endif
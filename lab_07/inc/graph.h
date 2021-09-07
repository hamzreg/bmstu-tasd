#ifndef GRAPH_T
#define GRAPH_T

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "constants.h"
#include "return_codes.h"

typedef struct graph
{
    int size;
    int **matrix;
    int **path;
} graph_t;

void init_graph(graph_t *graph);

int create_graph(graph_t *graph);

void free_graph(graph_t *graph);

int Dijkstra(graph_t *graph, const int start);

int get_median(graph_t *graph, int *median_index);

#endif
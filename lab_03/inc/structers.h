#ifndef STRUCTERS_H
#define STRUCTERS_H

typedef struct
{
    int **matrix;
    int rows;
    int columns;
} matrix_t;

typedef struct
{
    int *elements;
    int *rows;
    int *columns;
    int count_non_zero;
} sparce_matrix;

#endif
#include "../inc/visualization.h"

void visualizate_graph(int **matrix, const int size, char *name, char *filename, int node)
{
    FILE *file = fopen(filename, "w");

    fprintf(file, "graph %s{\n", name);

    fprintf(file, "node [shape = circle];\n");

    if (node != INT_MAX)
        fprintf(file, "%d [color = red];\n", node);

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if ((matrix[i][j] != 0) && j > i)
            {
                fprintf(file, "%d--%d [ label = %d ];\n", i + 1, j + 1, matrix[i][j]);
            }
        }
    }

    fprintf(file, "}");

    fclose(file);
}


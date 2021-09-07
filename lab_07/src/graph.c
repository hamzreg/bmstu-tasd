#include "../inc/graph.h"

void init_graph(graph_t *graph)
{
    graph->size = 0;
    graph->matrix = NULL;
    graph->path = NULL;
}


int create_graph(graph_t *graph)
{
    graph->matrix = calloc(graph->size, sizeof(int *));

    if (!(graph->matrix))
        return ALLOCATE_ERROR;
    
    for (int i = 0; i < graph->size; i++)
    {
        (graph->matrix)[i] = calloc(graph->size, sizeof(int));

        if (!(graph->matrix)[i])
        {
            free_graph(graph);
            return ALLOCATE_ERROR;
        }
    }

    return OK;
}


void free_graph(graph_t *graph)
{
    for (int i = 0; i < graph->size; i++)
    {
        free(graph->matrix[i]);
        free(graph->path[i]);
    }
    free(graph->matrix);
    free(graph->path);
}


int get_index_min(int *distances, char *visited, const int size)
{
    int min = INT_MAX;
    int index_min;

    for (int i = 0; i < size; i++)
    {
        if (visited[i] == 0 && distances[i] <= min)
        {
            min = distances[i];
            index_min = i;
        }
    }

    return index_min;
}


int Dijkstra(graph_t *graph, const int start)
{
    char *visited = calloc(graph->size, sizeof(char));

    for (int i = 0; i < graph->size; i++)
    {
        graph->path[start][i] = INT_MAX;
    }

    graph->path[start][start] = 0;

    for (int i = 0; i < graph->size; i++)
    {
        int index_min = get_index_min(graph->path[start], visited, graph->size);
        visited[index_min] = 1;

        for (int j = 0; j < graph->size; j++)
        {
            if (!visited[j] && graph->matrix[index_min][j] && graph->path[start][index_min] != INT_MAX
                && graph->path[start][index_min] + graph->matrix[index_min][j] < graph->path[start][j])
                graph->path[start][j] = graph->path[start][index_min] + graph->matrix[index_min][j];
        }
    }

    for (int i = 0; i < graph->size; i++)
    {
        if (graph->path[start][i] == INT_MAX)
        {
            printf("\nГраф не является связным\n");
            free(visited);
            return GRAPH_ERROR;
        }
    }

    free(visited);

    return OK;
}


int get_median(graph_t *graph, int *median_index)
{
    for (int i = 0; i < graph->size; i++)
    {
        if (Dijkstra(graph, i))
            return GRAPH_ERROR;
    }

    int min_sum_path = 0, now_sum;
    *median_index = 0;

    for (int i = 0; i < graph->size; i++)
        min_sum_path += graph->path[0][i];
    
    for (int i = 0; i < graph->size; i++)
    {
        now_sum = 0;

        for (int j = 0; j < graph->size; j++)
            now_sum += graph->path[i][j];

        if (now_sum < min_sum_path)
        {
            min_sum_path = now_sum;
            *median_index = i;
        }
    }

    return OK;
}
#include <stdio.h>
#include <stdlib.h>

#include "../inc/constants.h"
#include "../inc/input_output.h"
#include "../inc/graph.h"
#include "../inc/visualization.h"


int main(int argc, char **argv)
{
    print_conditions();

    graph_t graph;
    init_graph(&graph);

    int code;

    if (argc == INPUT_STDIN)
    {
        print_input_rules();

        code = input_graph(&graph);

        if (code != OK)
            return code;
    }
    else if (argc == INPUT_FILE)
    {
        code = read_graph(&graph, argv[1]);

        if (code != OK)
            return code;
    }
    else
    {
        printf("\nНеверный вызов программы\n");
        return ERROR_ARGC;
    }

    graph.path = calloc(graph.size, sizeof(int *));

    if (!graph.path)
        return ALLOCATE_ERROR;
    
    for (int i = 0; i < graph.size; i++)
    {
        graph.path[i] = calloc(graph.size, sizeof(int));

        if (!graph.path[i])
        {
            free_graph(&graph);
            return ALLOCATE_ERROR;
        }
    }

    printf("\nМатрица смежности:\n");
    print_graph(graph.matrix, graph.size);
    visualizate_graph(graph.matrix, graph.size, "START", "start_graph.gv", INT_MAX);

    int index_city;

    if (get_median(&graph, &index_city) == GRAPH_ERROR)
        return GRAPH_ERROR;
    
    printf("\nМатрица кратчайших расстояний:\n");
    print_graph(graph.path, graph.size);
    visualizate_graph(graph.path, graph.size, "RESULT", "result_graph.gv", index_city + 1);

    printf("\nГород с минимальной суммой расстояний до других городов: %d\n\n", index_city + 1);
    system("dot -Tpng -O start_graph.gv");
    system("dot -Tpng -O result_graph.gv");

    free_graph(&graph);

    return OK;
}
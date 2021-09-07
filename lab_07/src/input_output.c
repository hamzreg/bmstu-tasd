#include "../inc/input_output.h"

void print_conditions(void)
{
    printf("%s",
           "\nПрограмма предназначена для работы с графом. Граф:\n"
           "\n - связный\n"
           "\n - взвешенный\n"
           "\n - с положительными весами ребер\n"
           "\n - неориентированный\n"
           "\nДля системы двусторонних дорог, соединяющих города, программа\n"
           "\nнаходит город с минимальной суммой расстояний до других городов\n"
           "\nпри помощи алгоритма Дейкстры.\n");
}

void print_input_rules(void)
{
    printf("%s",
           "\n\nПравила ввода графа с n вершинами координатным методом:\n"
           "\nввести число городов - вершин n - целое число, заданное\n"
           "\nпоследовательностью цифр n = 3...INT_MAX - 1\n\n"
           "\nввести дороги - ребра - в формате: row column value, где\n"
           "\n - row = 1... n - номер первой вершины ребра\n"
           "\n                   (номер строки в матрице смежности)\n"
           "\n - column = 1... n - номер второй вершины ребра\n"
           "\n                   (номер столбца в матрице смежности)\n"
           "\n - value = 1... INT_MAX - 1 - вес ребра\n"
           "\n                   (значение в матрице смежности)\n\n"
           "\nТак как дороги двусторонние, нужно вводить данные для элементов\n"
           "\nматрицы смежности, расположенных только над или только под\n"
           "\nглавной диагональю\n");
}


int check_read(int row, int column, int value, int size)
{
    if (row < 1 || row > size)
    {
        printf("\nНеверно введен номер первой вершины ребра\n");
        return INPUT_ERROR;
    }

    if (column < 1 || column > size)
    {
        printf("\nНеверно введен номер второй вершины ребра\n");
        return INPUT_ERROR;
    }

    if (value < 0)
    {
        printf("\nВес ребра графа должен быть неотрицательным\n");
        return INPUT_ERROR;
    }

    return OK;
}


int input_graph(graph_t *graph)
{
    int size;

    printf("\nВведите число городов: ");
    int code = scanf("%d", &size);

    if (!code || size < MIN_COUNT_NODES || size > INT_MAX - 1)
    {
        printf("\nНеверно введено число городов\n");
        return INPUT_ERROR;
    }

    graph->size = size;
    code = create_graph(graph);

    if (code)
    {
        printf("\nОшибка выделения памяти\n");
        return code;
    }

    int row, column, value;

    while (row != -1 && column != -1 && value != -1)
    {
        code = scanf("%d %d %d", &row, &column, &value);

        if (row != -1 && column != -1 && value != -1)
        {
            if (code != 3)
            {
                printf("\nНеверно задано ребро графа\n");
                return INPUT_ERROR;
            }

            if (check_read(row, column, value, graph->size) == OK)
            {
                graph->matrix[row - 1][column - 1] = value;
                graph->matrix[column - 1][row - 1] = value;
            }
            else
                return ERROR_READ;
        }
    }

    return OK;
}


int read_graph(graph_t *graph, const char *filename)
{
    FILE *in_file = fopen(filename, "r");

    if (!in_file)
    {
        printf("\nОшибка открытия файла\n");
        return ERROR_READ;
    }

    int code = fscanf(in_file, "%d", &graph->size);

    if (!code || graph->size < MIN_COUNT_NODES || graph->size > INT_MAX - 1)
    {
        printf("\nНеверно задано число городов\n");
        return ERROR_READ;
    }

    code = create_graph(graph);

    if (code)
    {
        printf("\nОшибка выделения памяти\n");
        return code;
    }

    for (int i = 0; i < graph->size; i++)
    {
        for (int j = 0; j < graph->size; j++)
        {
            if (fscanf(in_file, "%d", &graph->matrix[i][j]) != 1)
                return ERROR_READ;
        }
    }

    fclose(in_file);

    return OK;
}


void print_graph(int **graph, const int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            printf("%5d ", graph[i][j]);
        
        printf("\n");
    }
}

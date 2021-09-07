#include "../inc/matrix.h"
#include "sys/time.h"
#include <inttypes.h>


uint64_t time_ticks(void)
{
    uint32_t high, low;
    __asm__ __volatile__(
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}


int create_matrix(matrix_t *matrix)
{
    int row, column;
    printf("\nВведите число строк матрицы: ");
    
    if (scanf("%d", &row))
        matrix->rows = row;
    else
    {
        printf("\nЧисло строк матрицы введено неверно.\n");
        return ROWS_ERROR;
    }

    if (row < MIN_SIZE || row > MAX_SIZE)
    {
        printf("\nЧисло строк матрицы введено неверно.\n");
        return ROWS_ERROR;
    }

    printf("\nВведите число столбцов матрицы: ");

    if (scanf("%d", &column))
        matrix->columns = column;
    else
    {
        printf("\nЧисло столбцов введено неверно.\n");
        return COLUMNS_ERROR;
    }

    if (column < MIN_SIZE || column > MAX_SIZE)
    {
        printf("\nЧисло столбцов матрицы введено неверно.\n");
        return COLUMNS_ERROR;
    }

    matrix->matrix = calloc(matrix->rows, sizeof(int*));

    if (!matrix->matrix)
        return ERROR_MEMORY_ALLOC;

    for (int i = 0; i < matrix->rows; i++)
    {
        matrix->matrix[i] = malloc(matrix->columns * sizeof(int));
    
        if (!matrix->matrix[i])
        {
            free_matrix(matrix, matrix->rows);
            return ERROR_MEMORY_ALLOC;
        }
    }

    return OK;
}


void random_matrix(matrix_t *const matrix, const int size)
{
    srand(time(NULL));

    for (int i = 0; i < size; i++)
    {
        int irand = 0;
        int jrand = 0;

        while (*(*(matrix->matrix + irand) + jrand) != 0)
        {
            irand = rand() % matrix->rows;
            jrand = rand() % matrix->columns;
        }

        *(*(matrix->matrix + irand) + jrand) = rand() % 100 + 1;
    }
}


void nullify(sparce_matrix *sparce, const int col_amount)
{
    for (int i = 0; i < sparce->count_non_zero; i++)
    {
        *(sparce->rows + i) = 0;
        *(sparce->elements + i) = 0;
    }

    for (int i = 0; i < col_amount; i++)
        *(sparce->columns + i) = -1;
}


int parse_matrix(matrix_t matrix, sparce_matrix *sparce)
{
    sparce->elements = malloc(sparce->count_non_zero * sizeof(int *));

    if (!sparce->elements)
        return ERROR_MEMORY_ALLOC;

    int k = 0;

    sparce->rows = malloc(sparce->count_non_zero * sizeof(int *));

    if (!sparce->rows)
        return ERROR_MEMORY_ALLOC;

    sparce->columns = malloc(matrix.columns * sizeof(int *));

    if (!sparce->columns)
        return ERROR_MEMORY_ALLOC;

    nullify(sparce, matrix.columns);

    for (int j = 0; j < matrix.columns; ++j)
    {
        for (int i = 0; i < matrix.rows; ++i)
        {
            if (*(*(matrix.matrix + i) + j) != 0)
            {
                *(sparce->elements + k) = *(*(matrix.matrix + i) + j);
                *(sparce->rows + k) = i;
                k++;
            }
        }
    }

    k = -1;

    for (int j = 0; j < matrix.columns; ++j)
    {
        for (int i = 0; i < matrix.rows; ++i)
        {
            if (*(*(matrix.matrix + i) + j) != 0)
            {
                k++;

                if (*(sparce->columns + j) == -1)
                    *(sparce->columns + j) = k;
            }
        }
    }

    for (int i = 0; i < matrix.columns; i++)
    {
        if (*(sparce->columns + i) == -1)
        {
            for (int j = i; j < matrix.columns; j++)
            {
                if (*(sparce->columns + j) != -1)
                {
                    *(sparce->columns + i) = *(sparce->columns + j);
                    break;
                }

                *(sparce->columns + j) = sparce->count_non_zero;
            }
        }
    }

    int now_count = 0;

    for (int j = 0; j < matrix.columns; j++)
    {
        int column = 0;

        for (int i = 0; i < matrix.rows; i++)
        {
            if (*(*(matrix.matrix + i) + j) != 0)
            {
                now_count++;
                column++;
            }
        }

        *(sparce->columns + j) = now_count - column;
    }

    return OK;
}


void free_matrix(matrix_t *matrix, int n)
{
    for (int i = 0; i < n; i++)
        free(matrix->matrix[i]);
    
    free(matrix->matrix);
}


void free_sparse(sparce_matrix *matrix)
{
    free(matrix->elements);
    free(matrix->columns);
    free(matrix->rows);
}


int classic_add(matrix_t matrix_A, matrix_t matrix_B, matrix_t *result, uint64_t *time)
{
    if (!matrix_A.matrix)
    {
        {
            printf("\nМатрица A не создана.\n");
            return ERROR_MEMORY_ALLOC;
        }
    }

    if (!matrix_B.matrix)
    {
        {
            printf("\nМатрица B не создана.\n");
            return ERROR_MEMORY_ALLOC;
        }
    }

    result->rows = matrix_A.rows;
    result->columns = matrix_A.columns;

    result->matrix = malloc(result->rows * sizeof(int*));

    if (!result->matrix)
        return ERROR_MEMORY_ALLOC;

    for (int i = 0; i < result->rows; i++)
    {
        result->matrix[i] = malloc(result->columns * sizeof(int));
    
        if (!result->matrix[i])
        {
            free_matrix(result, result->rows);
            return ERROR_MEMORY_ALLOC;
        }
    }

    uint64_t start = time_ticks();

    for (int i = 0; i < matrix_A.rows; i++)
        for (int j = 0; j < matrix_A.columns; j++)
            *(*(result->matrix + i) + j) = *(*(matrix_A.matrix + i) + j) + *(*(matrix_B.matrix + i) + j);

    uint64_t end = time_ticks();
    *time = end - start;

    return OK;
}


int count_result_non_zero(sparce_matrix sparse_a, sparce_matrix sparse_b, const int column, int *const result_count)
{
    for (int j = 0; j < column; ++j)
    {
        int *a_arr, *b_arr;
        int a_ind = 0, b_ind = 0;
        int cur_a, cur_b;

        if (j + 1 != column)
        {
            cur_a = *(sparse_a.columns + j + 1);
            cur_b = *(sparse_b.columns + j + 1);
        }
        else
        {
            cur_a = sparse_a.count_non_zero;
            cur_b = sparse_b.count_non_zero;
        }

        int a_column = cur_a - *(sparse_a.columns + j);
        int b_column = cur_b - *(sparse_b.columns + j);
        a_arr = (int *)calloc(a_column, sizeof(int));
        b_arr = (int *)calloc(b_column, sizeof(int));

        for (int a_col = *(sparse_a.columns + j); a_col < cur_a; ++a_col)
        {
            if (a_arr)
                *(a_arr + a_ind) = *(sparse_a.rows + a_col);
            a_ind++;
        }

        for (int b_col = *(sparse_b.columns + j); b_col < cur_b; ++b_col)
        {
            if (b_arr)
                *(b_arr + b_ind) = *(sparse_b.rows + b_col);
            b_ind++;
        }

        int matches = 0;

        for (int i = 0; i < a_column; ++i)
            for (int j = i; j < b_column; ++j)
                if (*(a_arr + i) == *(b_arr + j))
                    matches++;

        *result_count += a_column + b_column - matches;

        free(a_arr);
        free(b_arr);
    }

    return OK;
}


int arrays_min(int *a_arr, const int a_len, int *b_arr, const int b_len)
{
    if (a_len == 0 && b_len != 0)
        return B_LESS;

    if (b_len == 0 && a_len != 0)
        return A_LESS;

    int a_min = *a_arr, b_min = *b_arr;
    int a_pos = 0, b_pos = 0;

    for (int a = 0; a < a_len; ++a)
    {
        if (*(a_arr + a) < a_min)
        {
            a_min = *(a_arr + a);
            a_pos = a;
        }
    }

    for (int b = 0; b < b_len; ++b)
    {
        if (*(b_arr + b) < b_min)
        {
            b_min = *(b_arr + b);
            b_pos = b;
        }
    }

    if (a_min < b_min)
    {
        *(a_arr + a_pos) = 1000;

        return A_LESS;
    }

    if (b_min < a_min)
    {
        *(b_arr + b_pos) = 1000;

        return B_LESS;
    }

    if (a_min == b_min && a_min == 1000 && b_min == 1000)
    {
        return UB;
    }

    *(a_arr + a_pos) = 1000;
    *(b_arr + b_pos) = 1000;

    return EQUAL;
}


void fill_columns(matrix_t matrix, sparce_matrix *sparce)
{
    int now_count = 0;

    for (int j = 0; j < matrix.columns; ++j)
    {
        int column = 0;

        for (int i = 0; i < matrix.rows; ++i)
        {
            if (*(*(matrix.matrix + i) + j) != 0)
            {
                now_count++;
                column++;
            }
        }

        *(sparce->columns + j) = now_count - column;
    }
}


int sparse_sum(sparce_matrix sparse_a, sparce_matrix sparse_b, sparce_matrix *result, const int column, const int row, uint64_t *time)
{
    if (!sparse_a.elements || !sparse_b.elements)
    {
        printf("\nМатрицы не созданы.\n");
        return ERROR_MEMORY_ALLOC;
    }
    int cur_el = 0;
    int a_glob = 0;
    int b_glob = 0;

    for (int j = 0; j < column; j++)
    {
        int *a_arr, *b_arr;
        int a_ind = 0, b_ind = 0;
        int cur_a, cur_b;

        if (j + 1 != column)
        {
            cur_a = *(sparse_a.columns + j + 1);
            cur_b = *(sparse_b.columns + j + 1);
        }
        else
        {
            cur_a = sparse_a.count_non_zero;
            cur_b = sparse_b.count_non_zero;
        }

        int a_column = cur_a - *(sparse_a.columns + j);
        int b_column = cur_b - *(sparse_b.columns + j);
        a_arr = calloc(a_column, sizeof(int));
        b_arr = calloc(b_column, sizeof(int));

        for (int a_col = *(sparse_a.columns + j); a_col < cur_a; ++a_col)
        {
            if (a_arr)
                *(a_arr + a_ind) = *(sparse_a.rows + a_col);
            a_ind++;
        }

        for (int b_col = *(sparse_b.columns + j); b_col < cur_b; ++b_col)
        {
            if (b_arr)
                *(b_arr + b_ind) = *(sparse_b.rows + b_col);
            b_ind++;
        }

        int matches = 0;

        for (int i = 0; i < a_column; ++i)
            for (int j = i; j < b_column; ++j)
                if (*(a_arr + i) == *(b_arr + j))
                    matches++;

        int range = a_column + b_column - matches;

        uint64_t start = time_ticks();

        for (int i = 0; i < range; ++i)
        {
            start = time_ticks();
            int where = arrays_min(a_arr, a_column, b_arr, b_column);

            if (where == A_LESS)
            {
                *(result->elements + cur_el) = *(sparse_a.elements + a_glob);
                *(result->rows + cur_el) = *(sparse_a.rows + a_glob);
                cur_el++;
                a_glob++;
            }

            if (where == B_LESS)
            {
                *(result->elements + cur_el) = *(sparse_b.elements + b_glob);
                *(result->rows + cur_el) = *(sparse_b.rows + b_glob);
                cur_el++;
                b_glob++;
            }

            if (where == EQUAL)
            {
                *(result->elements + cur_el) = *(sparse_a.elements + a_glob) + *(sparse_b.elements + b_glob);
                *(result->rows + cur_el) = *(sparse_a.rows + a_glob);
                cur_el++;
                a_glob++;
                b_glob++;
            }
        }

        uint64_t end = time_ticks();
        *time += end - start;
        free(a_arr);
        free(b_arr);
    }

    return OK;
}
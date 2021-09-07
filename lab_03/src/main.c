#include <stdio.h>

#include "../inc/structers.h"
#include "../inc/input_output.h"
#include "../inc/matrix.h"
#include "../inc/constants.h"
#include "../inc/errors.h"

int main(void)
{
    matrix_t matrix_A, matrix_B, result;
    sparce_matrix sparce_A, sparce_B, sresult;
    int result_count;

    int command, process = START;

    print_conditions();
    print_menu();

    while (process)
    {
        if (input_command(&command) != OK)
        {
            printf("\nКоманда введена неверно\n");
            print_menu();
        }
        else if (command == INPUT_A)
        {
            if (create_matrix(&matrix_A) == OK)
            {
                if (input_matrix(&matrix_A, &sparce_A) == OK)
                {
                    printf("\nМатрица A создана.\n");

                    parse_matrix(matrix_A, &sparce_A);
                }
                else
                    free_matrix(&matrix_A, matrix_A.rows);
            }

            print_menu();
        }
        else if (command == INPUT_B)
        {
            if (create_matrix(&matrix_B) == OK)
            {
                if (matrix_B.rows != matrix_A.rows || matrix_B.columns != matrix_A.columns)
                    printf("\nРазмерность матрицы B должна соответствовать размерности матрицы A.\n");
                else
                {
                    if (input_matrix(&matrix_B, &sparce_B) == OK)
                    {
                        printf("\nМатрица B создана.\n");

                        parse_matrix(matrix_B, &sparce_B);
                    }
                    else
                        free_matrix(&matrix_B, matrix_B.rows);
                }
            }

            print_menu();
        }
        else if (command == AUTO_A)
        {
            if (create_matrix(&matrix_A) == OK)
            {
                int count;

                printf("\nВведите число ненулевых элементов матрицы: ");
    
                if (scanf("%d", &count))
                    sparce_A.count_non_zero = count;
                else
                {
                    printf("\nЧисло ненулевых элементов введено неверно.\n");
                    return ERROR_NON_ZERO;
                }

                random_matrix(&matrix_A, count);
                printf("\nМатрица A заполнена.\n");
                parse_matrix(matrix_A, &sparce_A);
            }

            print_menu();
        }
        else if (command == AUTO_B)
        {
            if (create_matrix(&matrix_B) == OK)
            {
                int count;

                printf("\nВведите число ненулевых элементов матрицы: ");
    
                if (scanf("%d", &count))
                    sparce_B.count_non_zero = count;
                else
                {
                    printf("\nЧисло ненулевых элементов введено неверно.\n");
                    return ERROR_NON_ZERO;
                }

                if (matrix_B.rows != matrix_A.rows || matrix_B.columns != matrix_A.columns)
                    printf("\nРазмерность матрицы B должна соответствовать размерности матрицы A.\n");
                    
                random_matrix(&matrix_B, count);
                printf("\nМатрица B заполнена.\n");
                parse_matrix(matrix_B, &sparce_B);
            }

            print_menu();
        }
        else if (command == CLASSIC_ADD)
        {
            uint64_t time;

            if (classic_add(matrix_A, matrix_B, &result, &time) == OK)
            {
                printf("\nСложение выполнено.\n");
                printf("\nВремя классического сложения: %ju\n", time);
            }
            
            print_menu();
        }
        else if (command == SPARSE_ADD)
        {
            count_result_non_zero(sparce_A, sparce_B, matrix_A.columns, &result_count);

            sresult.elements = (int *)malloc(result_count * sizeof(int));
            sresult.rows = (int *)malloc(result_count * sizeof(int));
            sresult.columns = (int *)malloc(matrix_A.columns * sizeof(int));
            sresult.count_non_zero = result_count;
            if (!sresult.elements || !sresult.rows || !sresult.columns)
                printf("\nОшибка выделения памяти.\n");
            else
            {
                uint64_t time;

                classic_add(matrix_A, matrix_B, &result, &time);
                nullify(&sresult, matrix_A.columns);
                fill_columns(matrix_A, &sparce_A);
                fill_columns(matrix_B, &sparce_B);

                time = 0;

                if (sparse_sum(sparce_A, sparce_B, &sresult, matrix_A.columns, matrix_A.rows, &time) == OK)
                {

                    //fill_columns(result, &sresult);

                    printf("\nСложение выполнено.\n");
                    printf("\nВремя столбцого сложения: %ju\n", time);
                }
            }

            print_menu();
        }
        else if (command == PRINT_CLASSIC)
        {
            printf("\nМатрица A:\n");
            print_matrix(matrix_A);

            printf("\nМатрица B:\n");
            print_matrix(matrix_B);

            print_menu();
        }
        else if (command == PRINT_SPARCE)
        {
            printf("\nМатрица A:\n");
            print_sparce(sparce_A, matrix_A.columns);

            printf("\nМатрица B:\n");
            print_sparce(sparce_B, matrix_B.columns);

            print_menu();
        }
        else if (command == RESULT_CLASSIC)
        {
            printf("\nРезультирующая матрица:\n");

            print_matrix(result);

            int matrix_size = sizeof(int **) + 
                              sizeof(int *) * result.rows + 
                              sizeof(int) * result.rows * result.columns + 
                              2 * sizeof(int);

            printf("\nОбъем занимаемой памяти классической матрицы (байты) - %d\n", matrix_size);

            print_menu();
        }
        else if (command == RESULT_SPARE)
        {
            printf("\nРезультирующая матрица:\n");
            print_sparce(sresult, result.columns);

            int sparse_size = sizeof(int *) * 3 +
                              sizeof(int) * sresult.count_non_zero * 2 + 
                              sizeof(int) * result_count +
                              sizeof(int);

           printf("\nОбъем занимаемой памяти разреженной матрицы (байты) - %d\n", sparse_size);
           
           print_menu();        
        }
        else
        {
            free_matrix(&matrix_A, matrix_A.rows);
            free_matrix(&matrix_B, matrix_B.rows);
            free_matrix(&result, result.rows);

            free_sparse(&sparce_A);
            free_sparse(&sparce_B);

            process = END;
        }
    }

    return OK;
}
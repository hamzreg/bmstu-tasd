#include "../inc/input_output.h"

void print_conditions(void)
{
    printf("%s",
           "\nПрограмма складывает матрицу A и матрицу B.\n"
           "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
           "Порядок ввода команды:\n\n"
           "Введите номер команды из меню k - целое число,\n"
           "представленное последовательностью цифр, идущих подряд\n\n"
           "Вид ввода:\n\n"
           "k\n"
           "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
           "Порядок ввода матрицы N на M элементов вручную:\n\n"
           "1. Введите число строк в матрице N ([1, 1000]) - целое число,\n"
           "   представленное последовательностью цифр, идущих подряд\n"
           "2. Введите число столбцов в матрице M ([1, 1000])- целое число,\n"
           "   представленное последовательностью цифр, идущих подряд\n"
           "3. Введите число ненулевых элементов матрицы ([1; 1000]) - целое число,\n"
           "   представленное последовательностью цифр, идущих подряд\n"
           "4. Введите элементы матрицы:\n"
           "    1) Введите номер строки([1;+∞)), в которой находится элемент n -\n"
           "    целое число, представленное последовательностью цифр,\n"
           "    идущих подряд\n"
           "    2) Введите пробел\n"
           "    3) Введите номер столбца([1;+∞)), в которой находится элемент m -\n"
           "    целое число, представленное последовательностью цифр,\n"
           "    идущих подряд\n"
           "    4) Введите пробел\n"
           "    5) Введите элемент a - целое число, представленое\n"
           "    последовательностью цифр, идущих подряд\n\n"
           "Вид ввода:\n\n"    
           "n m a\n"
           "Размерность матриц должна совпадать.\n");
}

void print_menu(void)
{
    printf("%s",
           "\nВыберите номер пункта меню:\n"
           "1) Ввести матрицу A вручную\n"
           "2) Ввести матрицу B вручную\n"
           "3) Автоматически заполнить матрицу A\n"
           "4) Автоматически заполнить матрицу B\n"
           "5) Сложить матрицы, используя классический способ хранения\n"
           "6) Сложить матрицы, используя разреженный столбцовый способ хранения\n"
           "7) Вывести исходные матрицы в классическом виде\n"
           "8) Вывести исходные матрицы в разреженном столбцовом виде\n"
           "9) Вывести результирующую матрицу в классическом виде\n"
           "10) Вывести результирующую матрицу в разреженном столбцовом виде\n"
           "0) Выход\n\n"
           "Введите команду: ");
}

void clean_input_stream()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

int input_command(int *command)
{
    int rc = scanf("%d", command);

    if (!rc)
    {
        clean_input_stream();
        return COMMAND_ERROR;
    }
    if (END > *command || *command > RESULT_SPARE)
    {
        clean_input_stream();
        return COMMAND_ERROR;
    }

    return OK;
}



int input_matrix(matrix_t *matrix, sparce_matrix *sparce)
{
    if (!matrix->matrix)
         return ERROR_MEMORY_ALLOC;
    
    int count, row, column, element;

    printf("\nВведите число ненулевых элементов матрицы: ");
    
    if (scanf("%d", &count))
        sparce->count_non_zero = count;
    else
    {
        printf("\nЧисло ненулевых элементов введено неверно.\n");
        return ERROR_NON_ZERO;
    }
    
    printf("\nВведите элементы матрицы:\n");
    for (int i = 0; i < count; i++)
    {
        if (scanf("%d %d %d", &row, &column, &element))
        {
            *(*(matrix->matrix + (row - 1)) + (column - 1)) = element;
        }
        else
        {
            printf("\nЭлемент введен неправильно.\n");
            return ERROR_INPUT;
        }
    }

    return OK;
}


int print_matrix(matrix_t matrix)
{
    if (!matrix.matrix)
    {
        printf("\nМатрица не создана.\n");
        return ERROR_MEMORY_ALLOC;
    }

    for (int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.columns; j++)
            printf("%3d ", *(*(matrix.matrix + i) + j));
        printf("\n");
    }

    return OK;
}


int print_sparce(sparce_matrix matrix, const int count)
{
    if (!matrix.columns || !matrix.elements || !matrix.rows)
    {
        printf("\nМатрица не создана.\n");        
        return ERROR_MEMORY_ALLOC;
    }

    printf("\nМассив с ненулевыми элементами\n");
    for (int i = 0; i < matrix.count_non_zero; i++)
        printf("%5d ", *(matrix.elements + i));
    
    printf("\n");

    printf("\nМассив с номерами строк для элементов первого массива\n");
    for (int i = 0; i < matrix.count_non_zero; i++)
        printf("%5d ", *(matrix.rows + i) + 1);

    printf("\n");

    printf("\nМассив с номерами элементов первого вектора, с которых начинается столбец\n");
    for (int i = 0; i < count; i++)
        printf("%5d ", *(matrix.columns + i) + 1);

    printf("\n");

    return OK;
}
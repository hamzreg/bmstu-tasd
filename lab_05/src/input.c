#include <stdio.h>

#include "../inc/constants.h"
#include "../inc/errors.h"

void print_conditions(void)
{
    printf("%s",
           "\nПрограмма предназначена для работы с очередью, реализованной при помощи массива или списка.\n"
           "\n\n"
           "\nПравила ввода команды : вводить комбинацию цифр без пробелов, соответствующую номеру пункта меню.\n"
           "\nМаксимальный размер очереди - 1001 * sizeof(char).\n");
}


void print_menu(void)
{
    printf("%s",
           "\nВыберите номер пункта меню для работы с очередью, реализованной при помощи МАССИВА:\n"
           "1) Добавить элемент в очередь\n"
           "2) Удалить элемент из очереди\n"
           "3) Вывести очередь\n"
           "4) Смоделировать процесс обработки первых 1000 заявок\n");
    printf("%s",
           "\nВыберите номер пункта меню для работы с очередью, реализованной при помощи СПИСКА:\n"
           "5) Добавить элемент в очередь\n"
           "6) Удалить элемент из очереди\n"
           "7) Вывести очередь\n"
           "8) Смоделировать процесс обработки первых 1000 заявок\n"
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
    if (scanf("%d", command) != 1)
    {
        clean_input_stream();
        return INPUT_ERROR;
    }

    if (*command < END || *command > SIMULATE_LIST_QUEUE)
    {
        clean_input_stream();
        return INPUT_ERROR;
    }

    return OK;
}

int input_element(int *element)
{
    if (scanf("%d", element) != 1)
    {
        clean_input_stream();
        return INPUT_ERROR;
    }

    return OK;
}
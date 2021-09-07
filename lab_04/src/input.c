#include <stdio.h>

#include "../inc/input.h"
#include "../inc/constants.h"
#include "../inc/errors.h"

void print_conditions(void)
{
    printf("%s",
           "\nПрограмма предназначена для работы со стеком, реализованным при помощи массива или списка.\n"
           "\nПрограмма при помощи стека определяет, является ли строка палиндромом.\n"
           "\nПравила ввода строки : вводить символы без пробелов и завершить ввод симовлом '.'\n"
           "\nМаксимальный размер стека - 100 * sizeof(char).\n");
}


void print_menu(void)
{
    printf("%s",
           "\nВыберите номер пункта меню для работы со стеком, реализованным при помощи МАССИВА:\n"
           "1) Ввести стек\n"
           "2) Добавить элемент в стек\n"
           "3) Удалить элемент из стека\n"
           "4) Определить, является ли строка палиндромом\n"
           "5) Вывести стек\n");
    printf("%s",
           "\nВыберите номер пункта меню для работы со стеком, реализованным при помощи СПИСКА:\n"
           "6) Ввести стек\n"
           "7) Добавить элемент в стек\n"
           "8) Удалить элемент из стека\n"
           "9) Определить, является ли строка палиндромом\n"
           "10) Вывести стек\n"
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
    if (END > *command || *command > PRINT_LIST_STACK)
    {
        clean_input_stream();
        return COMMAND_ERROR;
    }

    return OK;
}


int input_symbol(char *symbol)
{
    int rc = scanf("%c", symbol);

    if (!rc)
    {
        clean_input_stream();
        return INPUT_ERROR;
    }

    return OK;
}
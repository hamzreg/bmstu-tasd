#include <stdio.h>
#include <stdlib.h>

#include "../inc/stack_list.h"
#include "../inc/free_address.h"

stack_list_t* symbol_create(const char symbol)
{
    stack_list_t *node = malloc(sizeof(stack_list_t));

    if (node)
    {
        node->count = 0;
        node->symbol = symbol;
        node->next = NULL;
    }

    return node;
}

void symbol_free(stack_list_t *node)
{
    free(node);
}


int push_list(stack_list_t **head, const char symbol)
{
    if ((*head)->count == MAX_CAPACITY)
        return STACK_OVERFLOW;

    stack_list_t *node = symbol_create(symbol);

    if (node)
    {
        node->count = (*head)->count + 1;
        node->next = *head;
        *head = node;
    }

    return OK;
}


int input_list_stack(stack_list_t **head)
{
    char symbol;
    // uint64_t time;

    printf("\nВведите последовательность символов, оканчивающихся точкой: ");

    while ((symbol = getchar()) != '.')
    {
        // uint64_t start = get_time_ticks();

        if (!(*head))
            *head = symbol_create(symbol);
        else
            if (push_list(head, symbol) != OK)
                return STACK_OVERFLOW;
            
        // uint64_t end = get_time_ticks();

        // time += end - start;
    }

    // printf("\nВремя добавления %d элементов (тики) - %ju\n", (*head)->count, time);

    if ((*head)->count == 0)
        return EMPTY_STACK;

    return OK;
}


char pop_list(stack_list_t **head, size_t *adress)
{
    stack_list_t *add_node = *head;
    *head = (*head)->next;
    *adress = (size_t)add_node;
    char element = add_node->symbol;

    return element;
}


int print_list_stack(stack_list_t **head, free_address_t array)
{
    if (!(*head))
        return EMPTY_STACK;

    stack_list_t *add_head = *head;
    int size = (*head)->count;
    size_t address;

    printf("\nТекущее состояние стека, реализованного при помощи списка:\n");
    while (size)
    {
        printf("\nЭлемент : %c  Адрес: %zx\n", pop_list(&add_head, &address), address);
        size--;
    }

    printf("\nМассив освободившихся областей:\n");

    output_array(array);

    return OK;
}


int stack_list_is_palindrome(stack_list_t **head, uint64_t *time)
{
    stack_list_t *add_head;
    char symbol;
    int size = (*head)->count;
    size_t adress;

    uint64_t start = get_time_ticks();
    for (int i = 0; i < size / 2; i++)
    {
        symbol = pop_list(head, &adress);
        push_list(&add_head, symbol);
    }

    for (int i = 0; i < size % 2; i++)
        pop_list(head, &adress);

    for (int i = 0; i < (*head)->count; i++)
    {
        if (pop_list(head, &adress) != pop_list(&add_head, &adress))
        {
            uint64_t end = get_time_ticks();
            *time = end -start;
            return NO_PALINDROME;
        }
    }
    
    uint64_t end = get_time_ticks();
    *time = end - start;

    return PALINDROME;
}


free_address_t *create_array(void)
{
    free_address_t *array = malloc(sizeof(free_address_t));

    if (!array)
        return NULL;

    array->count= 0;
    array->array = malloc(MAX_CAPACITY * sizeof(size_t));

    return array;
}


void output_array(const free_address_t array)
{
    if (array.count == 0)
        printf("\nМассив освободившихся областей пуст\n");
    else
        for (int i = 0; i < array.count; i++)
            printf("\n%zx\n", array.array[i]);
}


int free_array(free_address_t *array)
{
    if (array)
    {
        if (array->array)
        {
            free(array->array);
            free(array);

            return OK;
        }

        free(array);

        return OK;
    }

    return MEMORY_ERROR;
}
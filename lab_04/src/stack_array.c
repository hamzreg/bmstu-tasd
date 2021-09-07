#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/stack_array.h"
#include "../inc/errors.h"
#include "../inc/constants.h"

int push_array(stack_array_t *stack, const char symbol)
{
    if (stack->count == MAX_CAPACITY + 1)
        return STACK_OVERFLOW;

    stack->array[stack->count++] = symbol;

    return OK;
}


int input_array_stack(stack_array_t *stack)
{
    char symbol;
    stack->count = 0;
    // uint64_t time = 0;

    printf("\nВведите последовательность символов, оканчивающихся точкой: ");

    while ((symbol = getchar()) != '.')
    {
        // uint64_t start = get_time_ticks();

        if (push_array(stack, symbol) != OK)
            return STACK_OVERFLOW;

        // uint64_t  end = get_time_ticks();

        // time += end - start;
    }

    // printf("\nВремя добавления %d элементов (тики) - %ju\n", stack->count - 1, time);

    if (stack->count == 0)
        return EMPTY_STACK;

    return OK;
}


char pop_array(stack_array_t *stack)
{
    stack->count--;

    return stack->array[stack->count];
}


int print_array_stack(stack_array_t *stack)
{
    if (stack->count == 0)
        return EMPTY_STACK;

    stack_array_t add_stack;
    add_stack.count = stack->count;
    strcpy(add_stack.array, stack->array);

    printf("\nТекущее состояние стека, реализованного при помощи массива:\n");
    int size = stack->count;

    while (size)
    {
        printf("\n%c\n", pop_array(&add_stack));
        size--;
    }


    return OK;
}


int stack_array_is_palindrome(stack_array_t *stack, uint64_t *time)
{
    stack_array_t add_stack;
    add_stack.count = 0;
    char symbol;
    int size = stack->count - 1;

    uint64_t start = get_time_ticks();
    for (int i = 0; i < size / 2; i++)
    {
        symbol = pop_array(stack);
        push_array(&add_stack, symbol);
    }

    for (int i = 0; i < size % 2; i++)
        pop_array(stack);
    
    for (int i = 0; i < stack->count; i++)
    {
        if (pop_array(stack) != pop_array(&add_stack))
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
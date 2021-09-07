#ifndef STACK_ARRAY_H
#define STACK_ARRAY_H

#include <inttypes.h>
#include "time_functions.h"
#include "constants.h"

typedef struct
{
    int count;
    char array[MAX_CAPACITY];
} stack_array_t;

int push_array(stack_array_t *stack, const char symbol);

int input_array_stack(stack_array_t *stack);

char pop_array(stack_array_t *stack);

int print_array_stack(stack_array_t *stack);

int stack_array_is_palindrome(stack_array_t *stack, uint64_t *time);

#endif
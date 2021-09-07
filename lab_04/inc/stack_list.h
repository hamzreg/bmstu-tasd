#ifndef STACK_LIST_H
#define STACK_LIST_H

#include <inttypes.h>
#include "time_functions.h"
#include "free_address.h"
#include "constants.h"
#include "errors.h"


typedef struct stack_list
{
    int count;
    char symbol;
    struct stack_list *next;
} stack_list_t;

stack_list_t* symbol_create(const char symbol);

void symbol_free(stack_list_t *node);

int push_list(stack_list_t **head, const char symbol);

int input_list_stack(stack_list_t **head);

char pop_list(stack_list_t **head, size_t *address);

int print_list_stack(stack_list_t **head, free_address_t array);

int stack_list_is_palindrome(stack_list_t **head, uint64_t *time);

free_address_t *create_array(void);

void output_array(const free_address_t array);

int free_array(free_address_t *array);

#endif
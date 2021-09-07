#include <stdio.h>

#include <string.h>
#include <stdlib.h>
#include "../inc/constants.h"
#include "../inc/errors.h"
#include "../inc/stack_array.h"
#include "../inc/input.h"
#include "../inc/time_functions.h"
#include "../inc/stack_list.h"
#include "../inc/free_address.h"

int main(void)
{
    int process = START;
    int command;
    stack_array_t stack_array;
    stack_array.count = 0;
    stack_list_t *head = NULL;
    free_address_t *array = NULL;

    print_conditions();
    print_menu();

    while (process)
    {
        if (input_command(&command) != OK)
        {
            printf("\nКоманда введена неверно\n");
            print_menu();
        }
        else if (command == INPUT_ARRAY_STACK)
        {
            if (stack_array.count)
                printf("\nСтек уже создан\n");
            else if (input_array_stack(&stack_array) == OK)
                printf("\nСтек создан\n");
            else
                printf("\nСтек переполнен\n");

            print_menu();
        }
        else if (command == ADD_ARRAY_STACK)
        {
            printf("\nВведите символ: ");
            clean_input_stream();
            char symbol;
            input_symbol(&symbol);

            // uint64_t start = get_time_ticks();

            if (push_array(&stack_array, symbol) == OK)
            {
                // uint64_t end = get_time_ticks();
                printf("\nЭлемент добавлен\n");
                
                // uint64_t time = end - start;
                // printf("\nВремя добавления элемента (тики) - %ju\n", time);
            }
            else
                printf("\nСтек переполнен\n");

            clean_input_stream();
            print_menu();
        }
        else if (command == DELETE_ARRAY_STACK)
        {
            if (stack_array.count == 0)
                printf("\nСтек пуст\n");
            else
            {
                // uint64_t start = get_time_ticks();

                pop_array(&stack_array);

                // uint64_t end = get_time_ticks();
                
                printf("\nЭлемент удален\n");

                // uint64_t time = end - start;
                // printf("\nВремя удаления элемента (тики) - %ju\n", time);
            }

            clean_input_stream();
            print_menu();
        }
        else if (command == PALINDROME_ARRAY_STACK)
        {
            if (stack_array.count == 0)
                printf("\nСтек пуст\n");
            else
            {
                uint64_t time;
                stack_array_t add_stack_array;
                add_stack_array.count = stack_array.count;
                strcpy(add_stack_array.array, stack_array.array);

                if (stack_array_is_palindrome(&add_stack_array, &time))
                    printf("\nСтрока - палиндром\n");
                else
                    printf("\nСтрока не палиндром\n");

                printf("\nВремя проверки строки на палиндром при реализации стека с помощью массива (тики): %ju\n", time);
                size_t size = sizeof(int) + sizeof(char) * MAX_CAPACITY;
                printf("\nОбъем занимаемой памяти (байты): %lu\n", size);
            }

            clean_input_stream();
            print_menu();
        }
        else if (command == PRINT_ARRAY_STACK)
        {
            if (stack_array.count == 0)
                printf("\nСтек пуст\n");
            else
                print_array_stack(&stack_array);

            clean_input_stream();
            print_menu();
        }
        else if (command == INPUT_LIST_STACK)
        {
            if (head)
                printf("\nСтек уже создан\n");
            else if (input_list_stack(&head) == OK)
            {
                array = create_array();
                printf("\nСтек создан\n");
            }
            else
                printf("\nСтек переполнен\n");

            clean_input_stream();
            print_menu();
        }
        else if (command == ADD_LIST_STACK)
        {
            printf("\nВведите символ: ");
            clean_input_stream();
            char symbol;
            input_symbol(&symbol);

            // uint64_t start = get_time_ticks();
            if (push_list(&head, symbol) == OK)
            {
                // uint64_t end = get_time_ticks();

                printf("\nЭлемент добавлен\n");

                // uint64_t time = end - start;
                // printf("\nВремя добавления элемента (тики) - %ju\n", time);
            }
            else
                printf("\nСтек переполнен\n");

            clean_input_stream();
            print_menu();
        }
        else if (command == DELETE_LIST_STACK)
        {
            if (!head)
                printf("\nСтек пуст\n");
            else
            {
                size_t adress;
                // uint64_t start = get_time_ticks();

                pop_list(&head, &adress);

                // uint64_t end = get_time_ticks();

                array->array[array->count++] = adress;
                
                printf("\nЭлемент удален\n");
                
                // uint64_t time = end - start;
                // printf("\nВремя удаления элемента (тики) - %ju\n", time);
            }

            clean_input_stream();
            print_menu();
        }
        else if (command == PRINT_LIST_STACK)
        {
            if (!head)
                printf("\nСтек пуст\n");
            else
                print_list_stack(&head, *array);

            clean_input_stream();
            print_menu();
        }
        else if (command == PALINDROME_LIST_STACK)
        {
            if (!head)
                printf("\nСтек пуст\n");
            else
            {            
                uint64_t time;
                stack_list_t *add_stack_list = head;
                add_stack_list->count = head->count;

                if (stack_list_is_palindrome(&add_stack_list, &time))
                    printf("\nСтрока - палиндром\n");
                else
                    printf("\nСтрока не палиндром\n");

                printf("\nВремя проверки строки на палиндром при реализации стека с помощью массива (тики): %ju\n", time);
                size_t size = sizeof(stack_list_t) * head->count;
                printf("\nОбъем занимаемой памяти (байты): %lu\n", size);
            }

            clean_input_stream();
            print_menu();
        }
        else if (command == END)
        {
            free(head);
            free_array(array);
            process = END;
        }
    }

    return OK;
}
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "../inc/array_queue_t.h"
#include "../inc/array_queue.h"
#include "../inc/list_queue_t.h"
#include "../inc/list_queue.h"
#include "../inc/input.h"
#include "../inc/errors.h"
#include "../inc/constants.h"


int main(void)
{
    array_queue_t array_queue = {.head = -1,
                                 .tail = -1, 
                                 .size = 0};

    list_queue_t list_queue;
    list_queue.head = malloc(sizeof(list_queue));
    list_queue.tail = malloc(sizeof(list_queue));
    list_queue.head->next = list_queue.tail;
    list_queue.head->data = 0;
    list_queue.tail->next = NULL;
    list_queue.tail->data = 0;
    list_queue.size = 0;

    int *free_elements = calloc(MAX_CAPACITY, sizeof(int));
    int count_free_elements = 0;

    int element;
    int command;

    print_conditions();
    print_menu();
    int process = START;

    while (process)
    {
        int code = input_command(&command);

        if (code)
        {
            printf("\nКоманда введена неверно\n");
            print_menu();
        }
        else if (command == PUSH_ARRAY_QUEUE)
        {
            printf("\nВведите элемент - целое число, представленное комбинацией цифр без пробелов: \n");
            code = input_element(&element);

            if (code)
                printf("\nЭлемент введен неверно\n");
            else if (array_push_queue(&array_queue, element) != OK)
                printf("\nОчередь переполнена\n");

            printf("\nЭлемент добавлен\n");

            print_menu();
        }
        else if (command == POP_ARRAY_QUEUE)
        {
            if (array_queue.size == 0)
                printf("\nОчередь пуста\n");
            else
            {
                element = array_pop_queue(&array_queue);

                printf("\nУдаленный элемент: %d\n", element);
            }

            print_menu();
        }
        else if (command == PRINT_ARRAY_QUEUE)
        {
            if (array_queue.size == 0)
                printf("\nОчередь пуста\n");
            else
                print_array_queue(array_queue);

            print_menu();
        }
        else if (command == SIMULATE_ARRAY_QUEUE)
        {
            simulate_array_queue();

            print_menu();
        }
        else if (command == PUSH_LIST_QUEUE)
        {
            printf("\nВведите элемент - целое число, представленное комбинацией цифр без пробелов: \n");
            code = input_element(&element);

            if (code)
                printf("\nЭлемент введен неверно\n");
            else if (list_push_queue(&list_queue, element) == OK)
            {
                int count = count_free_elements;
                for (int i = 0; i < count; i++)
                {
                    if ((void*)free_elements[i] == (void*)list_queue.head)
                        count_free_elements--;
                }
            }
            else
                printf("\nОчередь переполнена\n");
            
            printf("\nЭлемент добавлен\n");

            print_menu();
        }
        else if (command == POP_LIST_QUEUE)
        {
            if (list_queue.size == 0)
                printf("\nОчередь пуста\n");
            else
            {
                free_elements[count_free_elements++] = (void *)list_queue.head->next;

                element = list_pop_queue(&list_queue);

                printf("\nУдаленный элемент: %d\n", element);
            }

            print_menu();
        }
        else if (command == PRINT_LIST_QUEUE)
        {
            if (list_queue.size == 0)
                printf("\nОчередь пуста\n");
            else
            {
                print_list_queue(list_queue);

                print_list_adress(list_queue);

                print_free_address(free_elements, count_free_elements);
            }

            print_menu();
        }
        else if (command == SIMULATE_LIST_QUEUE)
        {
            simulate_list_queue();

            print_menu();
        }
        else if (command == END)
        {
            free_list_queue(&list_queue);
            process = END;
        }
    }
}
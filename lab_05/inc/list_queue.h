#ifndef LIST_QUEUE_H
#define LIST_QUEUE_H

#include "list_queue_t.h"

list_queue * node_create(const int element);

int list_push_queue(list_queue_t *queue, int element);

int list_pop_queue(list_queue_t *queue);

void free_list_queue(list_queue_t *queue);

void print_list_queue(list_queue_t queue);

void print_list_adress(list_queue_t queue);

void print_free_address(int *free_elements, int count);

void simulate_list_queue(void);
// void copy_queue(list_queue_t *add_queue, list_queue_t queue);

#endif
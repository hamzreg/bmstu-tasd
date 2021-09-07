#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H

#include "array_queue_t.h"

int array_push_queue(array_queue_t *queue, int element);

int array_pop_queue(array_queue_t *queue);

void print_array_queue(array_queue_t queue);

//void copy_queue(array_queue_t *add_queue, array_queue_t queue);

void simulate_array_queue(void);

#endif
#ifndef ARRAY_QUEUE_T_H
#define ARRAY_QUEUE_T_H

#include <stdio.h>
#include "constants.h"


typedef struct
{
    int queue[MAX_CAPACITY];
    int head;
    int tail;
    int size;
} array_queue_t;


#endif
#ifndef LIST_QUEUE_T
#define LIST_QUEUE_T

typedef struct list_queue
{
    int data;
    struct list_queue *next;
} list_queue;

typedef struct list_queue_t
{
    int size;
    list_queue *head;
    list_queue *tail;
} list_queue_t;

#endif
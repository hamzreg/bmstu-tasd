#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include <math.h>

#include "../inc/list_queue_t.h"
#include "../inc/list_queue.h"
#include "../inc/constants.h"
#include "../inc/errors.h"
#include "../inc/time_function.h"

#define TIME (float)rand()/RAND_MAX
#define PROBABILITY (float)rand()/RAND_MAX
#define ELEMENT 5
#define EPS 1e-5

list_queue * node_create(const int element)
{
    list_queue *node = malloc(sizeof(list_queue));

    if (node)
    {
        node->data = element;
        node->next = NULL;
    }

    return node;
}

int list_push_queue(list_queue_t *queue, int element)
{
    if (queue->size == MAX_CAPACITY)
        return OVERFLOW_ERROR;

    uint64_t start = get_time_ticks();
    list_queue *node = queue->tail;
    node->data = element;

    queue->tail = node_create(0);

    node->next = queue->tail;

    queue->size++;

    uint64_t end = get_time_ticks();
    printf("\nВремя добавления: %ju\n", end - start);

    return OK;
}


int list_pop_queue(list_queue_t *queue)
{
    if (queue->size == 0)
        return 1;

    uint64_t start = get_time_ticks();
    list_queue *element = queue->head->next;
    int data = element->data;

    queue->head->next = element->next;

    queue->size--;
    uint64_t end = get_time_ticks();
    printf("\nВремя удаления: %ju\n", end - start);
    return data;
}


void free_list_queue(list_queue_t *queue)
{
    while (queue->size > 0)
        list_pop_queue(queue);

    free(queue->head);
    queue->head = NULL;

    free(queue->tail);
    queue->tail = NULL;
}


void print_list_queue(list_queue_t queue)
{
    printf("\nОчередь в виде списка:\n");

    for (list_queue *i = queue.head->next; i != queue.tail; i = i->next)
        printf("Элемент: %d\n", i->data);
}


void print_list_adress(list_queue_t queue)
{
    printf("\nАдреса элементов очереди в виде списка: \n");

    for (list_queue *i = queue.head->next; i != queue.tail; i = i->next )
        printf("Адрес: %p\n", &i->data);
}


void print_free_address(int *free_elements, int count)
{
    if (count == 0)
        return;

    printf("\nАдреса свободных областей: \n");
    for (int i = 0; i < count; i++)
        printf("Адрес: %p\n", &free_elements[i]);
}


void simulate_list_queue(void)
{
    list_queue_t queue;
    queue.head = malloc(sizeof(list_queue));
    queue.tail = malloc(sizeof(list_queue));
    queue.head->next = queue.tail;
    queue.head->data = 0;
    queue.tail->next = NULL;
    queue.tail->data = 0;
    queue.size = 0;

    float input_t1 = 0.0;
    float input_t2 = 6.0;
    float input_time = (input_t2 - input_t1) * (float)(TIME) + input_t1;

    float process_t1 = 0.0;
    float process_t2 = 1.0;
    float process_time = (process_t2 - process_t1) * (float)(TIME) + process_t1;

    double downtime = 0;
    double model_time = 0;

    int count_input = 0;
    int count_return  = 0;
    int count_out = 0;
    int count_out_forever = 0;

    int count_add = 0;
    int fl = 0;
    int len = 0;

    while (count_out_forever < MAX_CAPACITY - 1)
    {
        if ((count_out_forever) % 100 == 0 && count_out_forever != 0 && fl == 0)
        {
            printf("Текущая длина очереди: %d\n", queue.size);
            printf("Средняя длина очереди: %f\n\n", (float)len / count_add);
            fl = 1;
        }

        if (process_time - input_time > 0)
        {
            process_time -= input_time;
            list_push_queue(&queue, 5);

            count_input++;

            model_time+= input_time;

            get_now_time(&input_time, input_t1, input_t2);
        }
        else if (queue.size != 0)
        {
            input_time-= process_time;
            list_pop_queue(&queue);

            count_out++;

            if (PROBABILITY < 0.8 + EPS)
            {
                list_push_queue(&queue, 5);

                count_input++;
                count_return++;
            }
            else
            {
                count_out_forever++;
                fl = 0;

            }
            model_time+= process_time;
            get_now_time(&process_time, process_t1, process_t2);
        }
        else
        {
            input_time -= process_time;
            downtime += process_time;
            get_now_time(&process_time, process_t1, process_t2);

        }
        len += queue.size;
        count_add++;

    }
    model_time+=downtime;

    printf("Ожидаемое время моделирования: 3000 е.в.\n");
    printf("Общее время моделирования: %f е.в.\n\n", model_time);

    printf("Количество вошедших заявок: %d, из них повторно возвращенные заявки: %d\n", count_input, count_return);
    printf("Количество вышедших заявок: %d, из них не вернувшихся обратно: %d\n\n", count_out, count_out_forever);

    printf("Ожидаемое время простоя: 500 е.в\n");
    printf("Время простоя аппарата: %f е.в.\n\n", downtime);

    printf("Время среднего пребывания заявки в очереди: %f е.в.\n", model_time/count_out * (float)len / count_add);

    printf("Количество cрабатываний ОА: %d\n\n", count_out);

    printf("Проверка работы:\n");
    printf("Погрешность по вошедшим заявкам: %f%%\n", 100*fabs(((count_input-count_return - model_time/3)/(model_time/3))));
    printf("Погрешность по вышедшим заявкам: %f%%\n\n", 100*fabs((model_time - 3000)/3000));
}

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include <math.h>

#include "../inc/array_queue_t.h"
#include "../inc/array_queue.h"
#include "../inc/constants.h"
#include "../inc/errors.h"
#include "../inc/time_function.h"

#define TIME (float)rand() / RAND_MAX
#define PROBABILITY (float)rand() / RAND_MAX
#define ELEMENT 5
#define EPS 1e-5

int array_push_queue(array_queue_t *queue, int element)
{
    if ((queue->head == queue->tail + 1) || (queue->head == 0 && queue->tail == MAX_CAPACITY - 1))
        return OVERFLOW_ERROR;

    uint64_t start = get_time_ticks();
    if (queue->head == -1)
        queue->head = 0;

    queue->tail = (queue->tail + 1) % MAX_CAPACITY;
    queue->queue[queue->tail] = element;
    queue->size++;
    uint64_t end = get_time_ticks();
    printf("\nВремя добавления: %ju\n", end - start);

    return OK;
}


int array_pop_queue(array_queue_t *queue)
{
    if (queue->head == -1)
        return 0;

    if (queue->head == queue->tail)
    {
        queue->head = -1;
        queue->tail = -1;
        return 0;
    }
    uint64_t start = get_time_ticks();

    int element = queue->queue[queue->head];
    queue->head = (queue->head + 1) % MAX_CAPACITY;
    queue->size--;
    uint64_t end = get_time_ticks();
    printf("\nВремя удаления: %ju\n", end - start);
    return element;
}


void copy_queue(array_queue_t *add_queue, array_queue_t queue)
{
    add_queue->head = queue.head;
    add_queue->tail = queue.tail;
    add_queue->size = queue.size;

    for (int i = add_queue->head; i < add_queue->tail + 1; i++)
        add_queue->queue[i] = queue.queue[i];
}


void print_array_queue(array_queue_t queue)
{
    printf("\nОчередь в виде массива:\n");

    int i;
    for(i = queue.head; i < queue.tail; i++)
        printf("Элемент: %d\n",queue.queue[i]);
    printf("Элемент: %d\n",queue.queue[i]);
}


void simulate_array_queue(void)
{
    array_queue_t queue = {.head = -1,
                           .tail = -1, 
                           .size = 0};

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

    int fl = 0;
    int len = 0;
    int count_add = 0;

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
            array_push_queue(&queue, ELEMENT);

            count_input++;

            model_time+= input_time;
            get_now_time(&input_time, input_t1, input_t2);
        }
        else if (queue.head != -1)
        {
            input_time-= process_time;
            array_pop_queue(&queue);

            count_out++;

            if (PROBABILITY < 0.8 + EPS)
            {
                array_push_queue(&queue, ELEMENT);

                count_input++;
                count_return++;
            }
            else
            {
                count_out_forever++;
                fl = 0;
            }
            model_time += process_time;
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

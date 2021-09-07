#include "../inc/functions.h"

int add_subscriber(table_t *table, char *record)
{
    if (add_record(table, record, table->table_size) != OK)
        return ERROR_ADD;

    table->table_size++;

    return OK;
}

int delete_subscribers(table_t *table, char *record)
{
    int count_deleted = 0;

    for (int i = 0; i < table->table_size; i++)
    {
        if (strcmp(table->human[i].number, record) == 0)
        {
            for (int j = i; j < table->table_size - 1; j++)
            {
                table->human[j] = table->human[j + 1];
                table->key[j] = table->key[j + 1];
            }

            i--;
            table->table_size--;
            count_deleted++;
        }
    }

    if (!count_deleted)
    {
        printf("\nАбоненты с данным номером не найдены.\n");
        return ERROR_DELETE;
    }

    return OK;
}

void sort_table_qsort(table_t *table, int type_sort, int start, int end)
{
    if (type_sort == NOT_KEY)
    {
        int i, j, average;
        subscriber first_record, last_record, average_record;

        if (start < end)
        {
            average = (start + end) / 2;
            i = start;
            j = end;

            while (i < j)
            {
                first_record = table->human[i];
                last_record = table->human[j];
                average_record = table->human[average];

                while ((strcmp(first_record.number, average_record.number) <= 0) && i < end)
                {
                    i++;
                    first_record = table->human[i];
                }

                while (strcmp(last_record.number, average_record.number) > 0)
                {
                    j--;
                    last_record = table->human[j];
                }

                if (i < j)
                {
                    table->human[i] = last_record;
                    table->human[j] = first_record;
                }
            }

            table->human[average] = last_record;
            table->human[j] = average_record;

            sort_table_qsort(table, 1, start, i - 1);
            sort_table_qsort(table, 1, j + 1, end);
        }
    }

    if (type_sort == KEY)
    {
        int i, j, average;
        keys first_record, last_record, average_record;

        if (start < end)
        {
            average = (start + end) / 2;
            i = start;
            j = end;

            while (i < j)
            {
                first_record = table->key[i];
                last_record = table->key[j];
                average_record = table->key[average];

                while ((strcmp(first_record.number, average_record.number) <=0) && i < end)
                {
                    i++;
                    first_record = table->key[i];
                }

                while (strcmp(last_record.number, average_record.number) > 0)
                {
                    j--;
                    last_record = table->key[j];
                }

                if (i < j)
                {
                    table->key[i] = last_record;
                    table->key[j] = first_record;
                }
            }

            table->key[average] = last_record;
            table->key[j] = average_record;

            sort_table_qsort(table, 1, start, i - 1);
            sort_table_qsort(table, 1, j + 1, end);
        }
    }
}

void sort_table_bubble(table_t *table, int type_sort)
{
    if (type_sort == NOT_KEY)
    {
        for (int i = 0; i < table->table_size; i++)
        {
            for (int j = 0; j < table->table_size - 1; j++)
            {
                if (strcmp(table->human[j].number,table->human[j + 1].number) > 0)
                {
                    subscriber tmp = table->human[j];
                    table->human[j] = table->human[j + 1];
                    table->human[j + 1] = tmp;
                }
            }
        }
    }

    if (type_sort == KEY)
    {
        for (int i = 0; i < table->table_size; i++)
        {
            for (int j = 0; j < table->table_size - 1; j++)
            {
                if (strcmp(table->key[j].number,table->key[j + 1].number) > 0)
                {
                    keys tmp = table->key[j];
                    table->key[j] = table->key[j + 1];
                    table->key[j + 1] = tmp;
                }
            }
        }
    }
}

void copy_table(table_t *table, table_t *now_table)
{
    now_table->table_size = table->table_size;

    for (int i = 0; i < table->table_size; i++)
    {
        strcpy(now_table->human[i].surname, table->human[i].surname);
        strcpy(now_table->human[i].name, table->human[i].name);
        strcpy(now_table->human[i].number, table->human[i].number);
        strcpy(now_table->human[i].address, table->human[i].address);
        now_table->human[i].status_type = table->human[i].status_type;
        now_table->key[i].index = table->key[i].index;
        strcpy(now_table->key[i].number, table->key[i].number);

        if (table->human[i].status_type == personal)
        {
            now_table->human[i].human_status.personal_status.day = table->human[i].human_status.personal_status.day;
            strcpy(now_table->human[i].human_status.personal_status.month, table->human[i].human_status.personal_status.month);
            now_table->human[i].human_status.personal_status.year = table->human[i].human_status.personal_status.year;
        }
        if (table->human[i].status_type == service)
        {
            strcpy(now_table->human[i].human_status.service_status.position, table->human[i].human_status.service_status.position);
            strcpy(now_table->human[i].human_status.service_status.organization, table->human[i].human_status.service_status.organization);
        }
    }
}

void print_sorts_result(table_t *table, char *filename)
{
    printf("\nЧисло записей в файле - %d\n", table->table_size);

    clock_t start, stop;
    table_t now_table;

    copy_table(table, &now_table);
    float time = 0;

    for (int i = 0; i < 1000; i++)
    {
        copy_table(&now_table, table);
        start = clock();
        sort_table_bubble(table, NOT_KEY);
        stop = clock();
        time += (float)(stop - start) / CLOCKS_PER_SEC;
    }

    printf("\nВремя сортировки таблицы пузырьком (c): %f.\n", time);
    time = 0;
    for (int i = 0; i < 1000; i++)
    {
        copy_table(&now_table, table);
        start = clock();
        sort_table_bubble(table, KEY);
        stop = clock();
        time += (float)(stop - start) / CLOCKS_PER_SEC;
    }

    printf("\nВремя сортировки таблицы ключей пузырьком (c): %f.\n", time);
    time = 0;
    for (int i = 0; i < 1000; i++)
    {
        copy_table(&now_table, table);
        start = clock();
        sort_table_qsort(table, NOT_KEY, 0, table->table_size - 1);
        stop = clock();
        time += (float)(stop - start) / CLOCKS_PER_SEC;
    }

    printf("\nВремя сортировки таблицы быстрой сортировкой (c): %f.\n",  time);

    time = 0;
    for (int i = 0; i < 1000; i++)
    {
        copy_table(&now_table, table);
        start = clock();
        sort_table_qsort(table, KEY, 0, table->table_size - 1);
        stop = clock();
        time += (float)(stop - start) / CLOCKS_PER_SEC;
    }

    printf("\nВремя сортировки таблицы ключей быстрой сортировкой (c): %f.\n",  time);

    printf("\nРазмер массива ключей (Б): %zu\n", sizeof(keys) * table->table_size);
    printf("\nРазмер таблицы (Б): %zu\n", (sizeof(keys) + sizeof(subscriber)) * table->table_size );
}

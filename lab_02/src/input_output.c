#include "../inc/input_output.h"

void print_start(void)
{
    printf("Данная программа вводит, выводит и обрабатывает таблицу записей-абонентов при помощи меню.\n");
}
void print_condition(void)
{
    printf("%s",
    "\nВыберите один из следующих пунктов - введите номер пункта меню - целое число от 0 до 12 включительно.\n"
    "1 - Ввести абонентов в таблицу из файлa (до 1000 записей включительно).\n"
    "2 - Добавить абонента в конец таблицы (до 1000 записей включительно).\n"
    "3 - Удалить абонентов из таблицы по номеру телефона.\n"
    "4 - Вывести список друзей, которых необходимо поздравить с днем рождения в ближайшую неделю.\n"
    "5 - Отсортировать исходную таблицу по номеру телефона сортировкой пузырьком.\n"
    "6 - Отсортировать исходную таблицу по номеру телефона быстрой сортировкой.\n"
    "7 - Отсортировать таблицу ключей сортировкой пузырьком.\n"
    "8 - Отсортировать таблицу ключей быстрой сортировкой.\n"
    "9 - Вывести  исходную таблицу.\n"
    "10 - Вывести исходную таблицу, используя таблицу ключей.\n"
    "11 - Вывести таблицу ключей.\n"
    "12 - Вывести сравнение сортировок.\n"
    "0 - Выход из программы.\n\n"
    "Выбор: ");
}

void clean_input_stream()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

int input_command(int *command)
{
    int rc = scanf("%d", command);

    if (!rc)
    {
        clean_input_stream();
        return COMMAND_ERROR;
    }
    if (END > *command || *command > PRINT_SORTS_RESULT)
    {
        clean_input_stream();
        return COMMAND_ERROR;
    }

    return OK;
}

int input_str(char *str)
{
    scanf("%s", str);
    clean_input_stream();
    return OK;
}

int add_record(table_t *table, char *record, int i)
{
    if (i > COUNT_SUBSCRIBER - 1)
    {
        printf("Число записей в файле больше допустимого.\n");
        return ERROR_RECORD;
    }

    char *part = strtok(record, ";\n");

    if (part == NULL)
    {
        printf("Данные записаны неверно.\n");
        return ERROR_RECORD;
    }

    if (strlen(part) > MAX_LEN_SURNAME)
    {
        printf("Длина фамилии должна быть меньше 11 символов.\n");
        return ERROR_RECORD;
    }
    //printf("%s\n", part);
    strcpy(table->human[i].surname, part);
    
    part = strtok(NULL, ";\n");

    if (part == NULL)
    {
        printf("Данные записаны неверно.\n");
        return ERROR_RECORD;
    }

    if (strlen(part) > MAX_LEN_NAME)
    {
        printf("Длина имени должна быть меньше 11 символов.\n");
        return ERROR_RECORD;
    }
    //printf("%s\n", part);
    strcpy(table->human[i].name, part);

    part = strtok(NULL, ";\n");

    if (part == NULL)
    {
        printf("Данные записаны неверно.\n");
        return ERROR_RECORD;
    }

    if (strlen(part) > MAX_COUNT_DIGITS)
    {
        printf("Длина номера должна быть меньше 8 символов.\n");
        return ERROR_RECORD;
    }

    for (int i = 0; i < strlen(part); i++)
    {
        if (part[i] < '0' || part[i] > '9')
        {
            printf("Номер абонента должен состоять только из цифр.\n");
            return ERROR_RECORD;
        }
    }
    //printf("%s\n", part);
    strcpy(table->human[i].number, part);
    strcpy(table->key[i].number, part);

    part = strtok(NULL, ";\n");

    if (part == NULL)
    {
        printf("Данные записаны неверно.\n");
        return ERROR_RECORD;
    }

    if (strlen(part) > MAX_LEN_ADDRESS)
    {
        printf("Длина адреса должна быть меньше 21 символа.\n");
        return ERROR_RECORD;
    }
    //printf("%s\n", part);
    strcpy(table->human[i].address, part);

    part = strtok(NULL, ";\n");

    if (part == NULL)
    {
        printf("Данные записаны неверно.\n");
        return ERROR_RECORD;
    }

    if (atoi(part) != 0 && atoi(part) != 1)
    {
        //printf("%s\n", part);
        printf("Должен быть указан тип статуса - 0 или 1.\n");
        return ERROR_RECORD;
    }

    table->human[i].status_type = atoi(part);

    if (atoi(part) == personal)
    {
        part = strtok(NULL, ";\n");

        if (part == NULL)
        {
            printf("Данные записаны неверно.\n");
            return ERROR_RECORD;
        }

        for (int i = 0; i < strlen(part); i++)
        {
            if (part[i] < '0' || part[i] > '9')
            {
                printf("День рождения должен быть числом от 0 до 31 включительно.\n");
                return ERROR_RECORD;
            }
        }

        if (atoi(part) <= 0 || atoi(part) > 31)
        {
            printf("День рождения должен быть числом от 0 до 31 включительно.\n");
            return ERROR_RECORD;
        }
        //printf("%s\n", part);
        table->human[i].human_status.personal_status.day = atoi(part);

        part = strtok(NULL, ";\n");

        if (part == NULL)
        {
            printf("Данные записаны неверно.\n");
            return ERROR_RECORD;
        }

        if (strlen(part) > MAX_LEN_MONTH)
        {
            printf("Длина месяца должна быть меньше 10 символов.\n");
            return ERROR_RECORD;
        }
        //printf("%s\n", part);
        strcpy(table->human[i].human_status.personal_status.month, part);

        part = strtok(NULL, ";\n");

        if (part == NULL)
        {
            printf("Данные записаны неверно.\n");
            return ERROR_RECORD;
        }

        for (int i = 0; i < strlen(part); i++)
        {
            if (part[i] < '0' || part[i] > '9')
            {
                printf("Год должен быть целым числом, большим 0.\n");
                return ERROR_RECORD;
            }
        }

        if (atoi(part) <= 0)
        {
            printf("Год должен быть целым числом, большим 0.\n");
            return ERROR_RECORD;            
        }
        //printf("%s\n", part);
        table->human[i].human_status.personal_status.year = atoi(part);
    }

    if (atoi(part) == service)
    {
        part = strtok(NULL, ";\n");

        if (part == NULL)
        {
            printf("Данные записаны неверно.\n");
            return ERROR_RECORD;
        }

        if (strlen(part) > MAX_LEN_POSITION)
        {
            printf("Длина должности должна быть меньше 21 символа.\n");
            return ERROR_RECORD;
        }

        //printf("%s\n", part);
        strcpy(table->human[i].human_status.service_status.position, part);

        part = strtok(NULL, ";\n");

        if (part == NULL)
        {
            printf("Данные записаны неверно.\n");
            return ERROR_RECORD;
        }

        if (strlen(part) > MAX_LEN_POSITION)
        {
            printf("Длина организации должна быть меньше 21 символа.\n");
            return ERROR_RECORD;
        }

        //printf("%s\n", part);
        strcpy(table->human[i].human_status.service_status.organization, part); 
    }

    part = strtok(NULL, ";\n");

    if (part != NULL)
    {
        printf("Число полей в записе больше допустимого.\n");
        return ERROR_RECORD;
    }
    table->key[i].index = i;

    return OK;
}

int check_file_size(FILE *f)
{
    long size;

    if (fseek(f, 0L, SEEK_END))
        return FILE_ERROR;

    size = ftell(f);

    if (size <= 0)
        return FILE_ERROR;

    return fseek(f, 0L, SEEK_SET);
}

int read_data(table_t *table, char *filename)
{
    FILE *file = fopen(filename, "r");

    if (!file)
    {
        printf("Такого файла не существует.\n");
        return FILE_ERROR;
    }

    if (check_file_size(file) != OK)
    {
        printf("Файл пустой.\n");
        return FILE_ERROR;
    }

    fseek(file, SEEK_SET, 0);
    char record[MAX_LEN_RECORD];
    int count_record = 0;

    while (fgets(record, MAX_LEN_RECORD, file))
    {
        if (add_record(table, record, count_record) != OK)
            return ERROR_RECORD;

        count_record++;
    }

    table->table_size = count_record;

    fclose(file);

    return OK;
}

void print_table(table_t table)
{
    char str_surname[] = "Фамилия";
    char str_name[] = "Имя";
    char str_number[] = "Номер абонента";
    char str_address[] = "Адрес";
    char str_type[] = "Тип статуса";
    char str_day[] = "День/Должность";
    char str_month[] = "Месяц/Организация";
    char str_year[] = "Год/-";

    printf("\nТаблица абонентов:\n");
    printf("\n┏━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━┳"
           "━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━┳━━━━━┓\n");
    printf("┃   %s┃       %s┃%s┃               %s┃%11s┃%14s┃%17s┃%5s┃\n", str_surname, str_name, str_number, str_address, str_type, str_day, str_month, str_year);
    printf("┃----------┃----------┃--------------┃--------------------┃-----------┃--------------┃-----------------┃-----┃\n");
    for (int i = 0; i < table.table_size; i++)
    {
        printf("┃%10s┃%10s┃%14s┃%20s┃%11d┃",
               table.human[i].surname,
               table.human[i].name,
               table.human[i].number,
               table.human[i].address,
               table.human[i].status_type);

        if (table.human[i].status_type == personal)
            printf("%14d┃%17s┃%5d┃\n",
                   table.human[i].human_status.personal_status.day,
                   table.human[i].human_status.personal_status.month,
                   table.human[i].human_status.personal_status.year);
        
        if (table.human[i].status_type == service)
            printf("%14s┃%17s┃     ┃\n", 
                   table.human[i].human_status.service_status.position,
                   table.human[i].human_status.service_status.organization);
    }

    printf("┗━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━┻"
           "━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━┻━━━━━┛\n");
}

void print_table_by_key(table_t table)
{
    char str_surname[] = "Фамилия";
    char str_name[] = "Имя";
    char str_number[] = "Номер абонента";
    char str_address[] = "Адрес";
    char str_type[] = "Тип статуса";
    char str_day[] = "День/Должность";
    char str_month[] = "Месяц/Организация";
    char str_year[] = "Год/-";

    printf("\nТаблица абонентов:\n");
    printf("\n┏━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━┳"
           "━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━┳━━━━━┓\n");
    printf("┃   %s┃       %s┃%s┃               %s┃%11s┃%14s┃%17s┃%5s┃\n", str_surname, str_name, str_number, str_address, str_type, str_day, str_month, str_year);
    printf("┃----------┃----------┃--------------┃--------------------┃-----------┃--------------┃-----------------┃-----┃\n");
    for (int i = 0; i < table.table_size; i++)
    {
        printf("┃%10s┃%10s┃%14s┃%20s┃%11d┃",
               table.human[table.key[i].index].surname,
               table.human[table.key[i].index].name,
               table.human[table.key[i].index].number,
               table.human[table.key[i].index].address,
               table.human[table.key[i].index].status_type);

        if (table.human[table.key[i].index].status_type == personal)
            printf("%14d┃%17s┃%5d┃\n",
                   table.human[table.key[i].index].human_status.personal_status.day,
                   table.human[table.key[i].index].human_status.personal_status.month,
                   table.human[table.key[i].index].human_status.personal_status.year);

        if (table.human[table.key[i].index].status_type == service)
            printf("%14s┃%17s┃     ┃\n",
                   table.human[table.key[i].index].human_status.service_status.position,
                   table.human[table.key[i].index].human_status.service_status.organization);

    }
    printf("┗━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━┻"
           "━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━┻━━━━━┛\n");;
}
void print_key_table(table_t table)
{
    char str_index[] = "Индекс";
    char str_number[] = "Номер абонента";

    printf("\nТаблица ключей:\n");
    printf("\n┏━━━━━━┳━━━━━━━━━━━━━━┓\n");
    printf("┃%6s┃%14s┃\n", str_index, str_number);
    printf("┃------┃--------------┃\n");
    for (int i = 0; i < table.table_size; i++)
        printf("┃%6d┃%14s┃\n", table.key[i].index, table.key[i].number);
    
     printf("┗━━━━━━┻━━━━━━━━━━━━━━┛\n");
}

int print_bithday_friends(table_t *table)
{
    int now_day;
    char now_month[MAX_LEN_MONTH + 10];

    int rc = fscanf(stdin, "%d %s", &now_day, now_month);

    if (rc != 2)
    {
        printf("\nДанные введены неверно.\n");
        return ERROR_RECORD;
    }

    if (now_day <= 0 || now_day > 31)
    {
        printf("Число месяца может быть в диапозоне от 1 до 31 включительно.\n");
        return ERROR_RECORD;
    }

    if (strlen(now_month) > MAX_LEN_MONTH)
    {
        printf("Длина месяца должна быть меньше 10 символов.\n");
        return ERROR_RECORD;   
    }

    int count = 0;

    printf("\nВ ближайшую неделю необходимо поздравить с днем рождения:\n");

    printf("\n┏━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━┳━━━━━━━━━━━━━━┳━┳"
           "━━━━━━━━━━━━┳━━━━━━━━━━━━┳━━━━┓\n");
    for (int i = 0; i < table->table_size; i++)
    {
        if (table->human[i].status_type == personal &&
            strcmp(table->human[i].human_status.personal_status.month, now_month) == 0 &&
            abs(table->human[i].human_status.personal_status.day - now_day) < 7)
        {
            count++;
            printf("┃%10s┃%10s┃%7s┃%14s┃%3d┃",
                   table->human[i].surname,
                   table->human[i].name,
                   table->human[i].number,
                   table->human[i].address,
                   table->human[i].status_type);
            printf("%12d┃%12s┃%4d┃\n",
                   table->human[i].human_status.personal_status.day,
                   table->human[i].human_status.personal_status.month,
                   table->human[i].human_status.personal_status.year);
        }
    }

    printf("┗━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━┻━━━━━━━━━━━━━━┻━┻"
           "━━━━━━━━━━━━┻━━━━━━━━━━━━┻━━━━┛\n");
    
    if (!count)
        printf("Таких друзей нет.\n");

    return OK;   
}
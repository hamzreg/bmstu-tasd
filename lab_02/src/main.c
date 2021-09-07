#include <stdio.h>

#include "../inc/structers.h"
#include "../inc/errors.h"
#include "../inc/constants.h"
#include "../inc/input_output.h"
#include "../inc/functions.h"

int main(void)
{
    table_t table;
    table.table_size = 0;

    char filename[MAX_LEN_FILENAME + 1];
    char record[MAX_LEN_RECORD + 1];
    char add_record[MAX_LEN_RECORD + 1];
    char record_number[MAX_LEN_RECORD + 1];

    int command = START;
    print_start();
    print_condition();

    while (command != END)
    {
        if (input_command(&command) != OK)
        {
            printf("\nНеобходимо вводить только числа, равные пунктам меню, от 0 до 12.\n");
            print_condition();
        }
        else
        {
            if (command == FILE_INPUT)
            {
                printf("\nВы можете загрузить данные из файлов test_30.txt, test_150.txt, test_300.txt или ввести имя своего файла.\n");
                printf("\nВведите имя файла с данными для записи (например, test_150.txt): ");
                input_str(filename);

                if (read_data(&table, filename) == OK)
                    printf("\nДанные записаны в таблицу.\n");

                print_condition();
            }

            if (command == ADD_SUBSCRIBER)
            {
                if (table.table_size == COUNT_SUBSCRIBER)
                    printf("\nТаблица заполнена полностью.\n");
                else
                {
                    printf("Ввод должен осуществляться на английском.\n");
                    printf("При добавлении абонента необходимо ввести все данные о нем через ; в следующем порядке:\n");
                    printf("фамилия - от 1 до 10 символов, имя - от 1 до 10 символов, номер телефона - от 1 до 7 цифр,\n");
                    printf("адрес - от 1 до 20 символов, тип статуса - 0 - личный, 1 - служебный.\n");
                    printf("Для личного статуса ввести день рождения - целое число от 1 до 31, месяц рождения - от 1 до 9 символов\n");
                    printf("и год  - целое положительное число\n");
                    printf("Для служебного статуса ввести должность - от 1 до 20 символов и организацию - от 1 до 20 символов.\n");                
                    printf("\nВведите данные абонента: ");
                    input_str(record);
                    strcpy(add_record, record);

                    if (add_subscriber(&table, record) == OK)
                    {
                        printf("\nАбонент добавлен.\n");

                        FILE *file = fopen(filename, "r+");

                        if (file)
                        {
                            fprintf(file, "%s\n", add_record);
                            fclose(file);
                        }
                    }
                }
                
                print_condition();
            }

            if (command == DELETE_SUBSCRIBER)
            {
                if (table.table_size == 0)
                    printf("\nНеобходимо ввести данные из файла в таблицу или добавить абонента в таблицу.\n");
                else
                {
                    printf("\nВведите номер абонентов для удаления - от 1 до 7 цифр: ");
                    input_str(record_number);

                    if (delete_subscribers(&table, record_number) == OK)
                    {
                        printf("\nАбоненты удалены.\n");
                        FILE *file = fopen(filename, "w");
                        if (file)
                        {
                            for (int i = 0; i < table.table_size; i++)
                            {
                                fprintf(file, "%s;%s;%s;%s;%d;", table.human[i].surname, table.human[i].name, table.human[i].number, table.human[i].address, table.human[i].status_type);

                                if (table.human[i].status_type == personal)
                                    fprintf(file, "%d;%s;%d\n", table.human[i].human_status.personal_status.day, table.human[i].human_status.personal_status.month, table.human[i].human_status.personal_status.year);
                                if (table.human[i].status_type == service)
                                    fprintf(file, "%s;%s\n", table.human[i].human_status.service_status.position, table.human[i].human_status.service_status.organization);                      
                            }

                            fclose(file);
                        }
                    }
                }

                print_condition();
                
            }

            if (command == HAPPY_BITHDAY)
            {
                if (table.table_size == 0)
                    printf("\nНеобходимо ввести данные из файла в таблицу или добавить абонента в таблицу.\n");
                else
                {
                    printf("Ввод должен осуществляться на английском.\n");
                    printf("Для поиска друзей необходимо ввести через пробел день рождения - целое число от 1 до 31 и\n");
                    printf(" месяц рождения - от 1 до 9 символов\n");
                    printf("\nВведите сегодняшнюю дату: ");

                    print_bithday_friends(&table);
                }
                
                print_condition();
            }

            if (command == SORT_TABLE_BUBBLE)
            {
                if (table.table_size == 0)
                    printf("\nНеобходимо ввести данные из файла в таблицу или добавить абонента в таблицу.\n");
                else
                {
                    sort_table_bubble(&table, NOT_KEY);
                    printf("\nТаблица отсортирована.\n");   
                }
                
                print_condition();
            }
 
             if (command == SORT_TABLE_QSORT)
            {
                if (table.table_size == 0)
                    printf("\nНеобходимо ввести данные из файла в таблицу или добавить абонента в таблицу.\n");
                else
                {
                    sort_table_qsort(&table, NOT_KEY, 0, table.table_size - 1);
                    printf("\nТаблица отсортирована.\n");  
                }
                
                print_condition();
            }

            if (command == SORT_KEY_BUBBLE)
            {
                if (table.table_size == 0)
                    printf("\nНеобходимо ввести данные из файла в таблицу или добавить абонента в таблицу.\n");
                else
                {
                    sort_table_bubble(&table, KEY);
                    printf("\nТаблица ключей отсортирована.\n");   
                }
                
                print_condition();
            }

            if (command == SORT_KEY_QSORT)
            {
                if (table.table_size == 0)
                    printf("\nНеобходимо ввести данные из файла в таблицу или добавить абонента в таблицу.\n");
                else
                {
                    sort_table_qsort(&table, KEY, 0, table.table_size - 1);
                    printf("\nТаблица ключей отсортирована.\n");   
                }
                
                print_condition();
            }

            if (command == PRINT_TABLE)
            {
                if (table.table_size != 0)
                    print_table(table);
                else
                    printf("\nНеобходимо ввести данные из файла в таблицу или добавить абонента в таблицу.\n");
                
                print_condition();
            }

            if (command == PRINT_TABLE_BY_KEY)
            {
                if (table.table_size != 0)
                    print_table_by_key(table);
                else
                    printf("\nНеобходимо ввести данные из файла в таблицу или добавить абонента в таблицу.\n");
                
                print_condition();
            }

            if (command == PRINT_KEY)
            {
                if (table.table_size != 0)
                    print_key_table(table);
                else
                    printf("\nНеобходимо ввести данные из файла в таблицу или добавить абонента в таблицу.\n");
                
                print_condition();
            }

            if (command == PRINT_SORTS_RESULT)
            {
                if (table.table_size != 0)
                    print_sorts_result(&table, filename);
                else
                    printf("\nНеобходимо ввести данные из файла в таблицу или добавить абонента в таблицу.\n");
                
                print_condition();
            }
        }
    }

    return OK;
}
#include "../inc/compare_structures.h"

int file_len(FILE *f)
{
    rewind(f);

    int lines = 0;
    char buffer[MAGIC_SIZE];

    while (fgets(buffer, MAGIC_SIZE, f) != NULL)
        lines++;

    rewind(f);

    return lines;
}

int fbytes(FILE *f)
{
    rewind(f);
    fseek(f, 0, SEEK_END);
    unsigned size = ftell(f);
    rewind(f);

    return size;
}

char **fill_words(FILE *f, int n)
{
    rewind(f);
    unsigned long flen = file_len(f);

    int ind = 0;
    char buffer[MAGIC_SIZE];
    char **words = (char **)malloc(sizeof(char *) * n);
    for (int i = 0; i < flen; ++i)
    {
        words[i] = (char *)malloc(sizeof(char) * MAGIC_SIZE);
    }

    while (fgets(buffer, MAGIC_SIZE, f) != NULL && ind < n)
    {
        if (buffer[strlen(buffer) - 1] == '\n')
        {
            buffer[strlen(buffer) - 1] = '\0';
        }

        strcpy(words[ind], buffer);
        ind++;
    }

    rewind(f);

    return words;
}

double tree_count(tree_t *tree, char **words, int n, int *cmprs)
{
    uint64_t start, stop, time = 0;

    *cmprs = 0;

    start =  get_time_ticks();

    for (int i = 0; i < n; i++)
        find(tree, words[i], cmprs);

    stop = get_time_ticks();
    time = stop - start;

    return (double)(time / n);
}


double balance_count(tree_t *tree, char **words, int n, int *cmprs)
{
    uint64_t time = 0;

    *cmprs = 0;

    for (int i = 0; i < n; i++)
        balance_find_time(tree, words[i], cmprs, &time);

    return (double)(time / n);
}


double hash_count_time(hash_table_t *hash_table,  char **words, int n, int *cmprs)
{
    uint64_t time = 0;
    int code;
    *cmprs = 0;
    int collisions = 4;


    for (int i = 0; i < n; i++)
        hash_find_time(hash_table, words[i], cmprs, &time, &code, collisions);
    
    return (double)(time / n);
}


int search_file(char *to_find, FILE *f, int *cmprs)
{
    rewind(f);

    int i = 0;
    char buffer[MAGIC_SIZE];

    while (fgets(buffer, MAGIC_SIZE, f) != NULL)
    {
        i++;
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        
        (*cmprs)++;
        if (strcmp(to_find, buffer) == 0)
        {
            return OK;
        }
    }

    rewind(f);
    return NOT_FOUND;
}


double file_count(FILE *f, char **words, int n, int *cmprs)
{
    uint64_t start, stop, time = 0;

    *cmprs = 0;

    start = get_time_ticks();

    for (int i = 0; i < n; i++)
    {
        search_file(words[i], f, cmprs);
    }

    stop = get_time_ticks();
    time = stop - start;

    return (double)(time / n);
}


void count_for_file(FILE *f, tree_t *tree, tree_t *balance, hash_table_t *table, int n)
{
    char **words = fill_words(f, n);
    double time = 0;
    if (n == 1000)
        time = 100;
    int cmprs;
    unsigned long flen = file_len(f);

    time = tree_count(tree, words, flen, &cmprs);
    printf("%20f  |", time);

    time = 0;
    if (n == 1000)
        time = 100;
    time = balance_count(balance, words, flen, &cmprs);
    printf("%20f  |", time);

    time = 0;
    if (n == 1000)
        time = 100;
    time = hash_count_time(table, words, flen, &cmprs);
    printf("%20f  |", time);
    rewind(f);

    time = 0;
    time = file_count(f, words, n, &cmprs);
    printf("%20f  |\n", time);

    for (int i = 0; i < n; i++)
        free(words[i]);
    free(words);

    fclose(f);
}


int compare_structures(void)
{
    printf("\n\nСрeднее время поиска слова:\n\n");

    tree_t *tree = NULL;
    tree_t *balance = NULL;
    hash_table_t table;
    int count = 0;
    FILE *file;

    printf("Количество элементов   |        ДДП           |   Сбалансированное   |      Хеш-таблица     |        Файл          |\n");

    int n = 10;
    file = fopen("test_10.txt", "r");
    create_tree(&tree, file, &count);
    rewind(file);
    create_balance(&balance, file);
    rewind(file);
    hash_table_init(&table, count);
    create_hash_table(file, &table);
    printf("         %d            |", n);
    count_for_file(file, tree, balance, &table, n);
    free_tree(tree);
    free_tree(balance);
    free_table(&table);

    n = 100;
    file = fopen("test_100.txt", "r");
    tree = NULL;
    balance = NULL;
    create_tree(&tree, file, &count);
    rewind(file);
    create_balance(&balance, file);
    rewind(file);
    hash_table_init(&table, count);
    create_hash_table(file, &table);
    printf("         %d           |", n);
    count_for_file(file, tree, balance, &table, n);
    free_tree(tree);
    free_tree(balance);
    free_table(&table);


    n = 500;
    file = fopen("test_500.txt", "r");
    tree = NULL;
    balance = NULL;
    create_tree(&tree, file, &count);
    rewind(file);
    create_balance(&balance, file);
    rewind(file);
    hash_table_init(&table, count);
    create_hash_table(file, &table);
    printf("         %d           |", n);
    count_for_file(file, tree, balance, &table, n);
    free_tree(tree);
    free_tree(balance);
    free_table(&table); 


    n = 1000;
    file = fopen("test_1000_2.txt", "r");
    tree = NULL;
    balance = NULL;
    create_tree(&tree, file, &count);
    rewind(file);
    create_balance(&balance, file);
    rewind(file);
    hash_table_init(&table, count);
    create_hash_table(file, &table);
    printf("         %d          |", n);
    count_for_file(file, tree, balance, &table, n);
    free_tree(tree);
    free_tree(balance);
    free_table(&table);

    return OK;
}
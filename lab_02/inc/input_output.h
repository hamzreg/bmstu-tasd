#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "constants.h"
#include "errors.h"
#include "structers.h"

void print_start(void);

void print_condition(void);

int input_command(int *command);

int input_str(char *str);

int add_record(table_t *table, char *record, int i);

int check_file_size(FILE *f);

int read_data(table_t *table, char *filename);

void print_table(table_t table);

void print_table_by_key(table_t table);

void print_key_table(table_t table);

int print_bithday_friends(table_t *table);

#endif
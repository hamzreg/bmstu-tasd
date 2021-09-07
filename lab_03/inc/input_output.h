#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include <stdio.h>
#include "structers.h"
#include "errors.h"
#include "constants.h"

void print_conditions(void);

void print_menu(void);

void clean_input_stream();

int input_command(int *command);

int input_matrix(matrix_t *matrix, sparce_matrix *sparce);

int print_matrix(matrix_t matrix);

int print_sparce(sparce_matrix matrix, const int count);

#endif
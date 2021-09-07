#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <inttypes.h>

#include "structers.h"
#include "errors.h"
#include "constants.h"


uint64_t time_ticks(void);

int create_matrix(matrix_t *matrix);

void free_matrix(matrix_t *matrix, int n);

void free_sparse(sparce_matrix *matrix);

int parse_matrix(matrix_t matrix, sparce_matrix *sparce);

int classic_add(matrix_t matrix_A, matrix_t matrix_B, matrix_t *result, uint64_t *time);

int count_result_non_zero(sparce_matrix sparse_a, sparce_matrix sparse_b, const int column, int *const result_count);

int sparse_sum(sparce_matrix sparse_a, sparce_matrix sparse_b, sparce_matrix *result, const int column, const int row, uint64_t *time);

void nullify(sparce_matrix *sparce, const int col_amount);

void fill_columns(matrix_t matrix, sparce_matrix *sparce);

void random_matrix(matrix_t *const matrix, const int size);

#endif
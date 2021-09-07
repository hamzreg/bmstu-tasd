#ifndef DIVISION_NUMEBRS_H
#define DIVISION_NUMBERS_H

void delete_zeros(number *result_number);

int compare_sings(char int_single, char real_single);

void normalization(number *one_number);

void add_zeros(number *one_number);

int compare_numbers(number *int_number, number *real_number);

int compare_zero(number *one_number);

void change_zero(number *one_number);

int subtraction(number *int_number, number *real_number);

int divide_numbers(number *int_number, number *real_number, number *result_number);

#endif
#include <stdio.h>
#include <stdlib.h>

#include "../inc/number.h"
#include "../inc/input_output.h"
#include "../inc/division_numbers.h"
#include "../inc/constants.h"

int main(void)
{
    print_conditions();

    number int_number, real_number, result_number;
    int return_code;

    return_code = input_int_number(&int_number);

    if (return_code != OK)
        return return_code;

    return_code = input_real_number(&real_number);

    if (return_code != OK)
        return return_code;

    if (abs(int_number.order - real_number.order) >= 99999)
    {
        printf("Переполнение порядка.\n");
        return OVERFLOW;
    }

    normalization(&int_number);
    normalization(&real_number);

    add_zeros(&int_number);
    add_zeros(&real_number);

    return_code = divide_numbers(&int_number, &real_number, &result_number);

    if (return_code == ZERO)
    {
        printf("Результат деления: +0.0E+0\n");
        return OK;
    }
    else if (return_code != OK)
        return return_code;   

    delete_zeros(&result_number);

    output_number(result_number);

    return OK;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/constants.h"
#include "../inc/number.h"
#include "../inc/division_numbers.h"


void delete_zeros(number *result_number)
{
    int i = strlen(result_number->mantissa) - 1;

    while (result_number->mantissa[i] == '0' && i > 1)
        i--;

    result_number->mantissa[i + 1] = '\0';
}

int compare_sings(char int_single, char real_single)
{
    if (int_single == real_single)
        return EQUAL;
    
    return VARIOUS;
}

void normalization(number *one_number)
{
    int len = strlen(one_number->mantissa), i;

    if (one_number->point_index != NO_POINT)
    {
        for (i = one_number->point_index; i < len; i++)
            one_number->mantissa[i] = one_number->mantissa[i + 1];

        one_number->mantissa[len] = '\0';
        one_number->order += -1 * (len - 1 - one_number->point_index);
    }

    if (one_number->point_index != NO_POINT)
        i = len - 1;
    else
        i = len;

    for (; i < MAX_LEN_MANTISSA + 2; i++)
    {
        one_number->mantissa[i] = '0';
        one_number->order--;
    }

    one_number->mantissa[MAX_LEN_MANTISSA + 1] = '\0';
}

void add_zeros(number *one_number)
{
    int len = strlen(one_number->mantissa);
    int count = 0, i;
    char symbol;

    while (one_number->mantissa[0] == '0' && count != len - 1)
    {
        for (i = 0; i < len - 1; i++)
        {
            symbol = one_number->mantissa[i];
            one_number->mantissa[i] = one_number->mantissa[i + 1];
            one_number->mantissa[i + 1] = symbol;
        }

        count++;
    }

    one_number->mantissa[len - count] = '\0';

    len = strlen(one_number->mantissa);

    for (i = len; i > 0; i--)
        one_number->mantissa[i] = one_number->mantissa[i - 1];

    one_number->mantissa[0] = '0';
    one_number->mantissa[len] = '\0';
}

int compare_numbers(number *int_number, number *real_number)
{
    int len = strlen(int_number->mantissa);

    for (int i = 0; i < len; i++)
    {
        if ((int)(int_number->mantissa[i] - real_number->mantissa[i] > 0))
            return MORE;
        else if ((int)(int_number->mantissa[i] - real_number->mantissa[i] < 0))
            return LESS;
    }

    return MORE;
}

int compare_zero(number *one_number)
{
    int len = strlen(one_number->mantissa);

    for (int i = 0; i < len; i++)
        if (one_number->mantissa[i] != '0')
            return VARIOUS;

    return EQUAL;
}

void change_zero(number *one_number)
{
    for (int i = 0; i < MAX_LEN_MANTISSA; i++)
        one_number->mantissa[i] = one_number->mantissa[i + 1];

    one_number->mantissa[30] = '0';
}

int subtraction(number *int_number, number *real_number)
{
    if (compare_numbers(int_number, real_number))
    {
        int i = strlen(real_number->mantissa) - 1;

        for (; i >= 0; i--)
        {
            if (int_number->mantissa[i] - real_number->mantissa[i] >= 0)
                int_number->mantissa[i] -= real_number->mantissa[i] - '0';
            else
            {
                int j = i - 1;

                while (int_number->mantissa[j] - '0' == 0)
                    j--;

                int_number->mantissa[j++]--;

                for (; j < i; j++)
                    int_number->mantissa[j] += 9;

                int_number->mantissa[i] += 10 - (real_number->mantissa[i] - '0');
            }
        }

        return GO;
    }

    return END;
}

int divide_numbers(number *int_number, number *real_number, number *result_number)
{
    if (compare_zero(real_number))
    {
        printf("Нельзя делить на 0.\n");
        return DIVISION_BY_ZERO;
    }

    if (compare_zero(int_number))
        return ZERO;

    if (abs(int_number->order - real_number->order) >= 99999)
    {
        printf("Переполнение порядка.\n");
        return OVERFLOW;
    }

    if (compare_numbers(int_number, real_number) == LESS)
    {
        change_zero(int_number);
        int_number->order--;
    }

    result_number->mantissa[0] = '0';
    int count_digits = 0;

    while (subtraction(int_number, real_number))
        count_digits++;

    change_zero(int_number);

    result_number->mantissa[1] = '0' + count_digits;

    int i;

    for (i= 2; i < MAX_LEN_MANTISSA + 1; i++)
    {
        if (compare_zero(int_number))
        {
            result_number->mantissa[i] = '\0';
            count_digits = 0;
            break;
        }

        if (compare_numbers(int_number, real_number) == LESS)
        {
            change_zero(int_number);
            result_number->mantissa[i] = '0';
        }
        else
        {
            count_digits = 0;

            while (subtraction(int_number, real_number))
                count_digits++;

            change_zero(int_number);
            result_number->mantissa[i] = '0' + count_digits;
        }
    }

    result_number->mantissa[MAX_LEN_MANTISSA + 1] = '\0';

    count_digits = 0;

    while (subtraction(int_number, real_number))
        count_digits++;

    change_zero(int_number);

    if (i == MAX_LEN_MANTISSA + 1 && count_digits >= 5)
        result_number->mantissa[MAX_LEN_MANTISSA] += 1;

    for (; i < MAX_LEN_MANTISSA + 1; i++)
        result_number->mantissa[i] = '0';

    result_number->mantissa[MAX_LEN_MANTISSA + 1] = '\0';

    int remainder = 0;

    for (i = MAX_LEN_MANTISSA; i >= 0; i--)
    {
        result_number->mantissa[i] += remainder;

        if (result_number->mantissa[i] == ':')
        {
            result_number->mantissa[i] = '0';
            remainder = 1;
        }
        else
            break;
    }

    if (result_number->mantissa[0] == '1')
    {
        for (i = MAX_LEN_MANTISSA; i > 0; i--)
            result_number->mantissa[i] = result_number->mantissa[i - 1];

        result_number->mantissa[0] = '0';
    }
    else
        remainder = 0;

    result_number->mantissa[MAX_LEN_MANTISSA + 1] = '\0';

    result_number->order = int_number->order - real_number->order + remainder + 1;

    if (compare_sings(int_number->number_sign, real_number->number_sign))
        result_number->number_sign = '+';
    else
        result_number->number_sign = '-';
    
    return OK;
}

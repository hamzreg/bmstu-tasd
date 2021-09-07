#ifndef NUMBER_H
#define NUMBER_H

typedef struct
{
    char number_sign; 
    char mantissa[32];
    int point_index;
    char order_sign;
    int order;
} number;

#endif
#ifndef STRUCTERS_H
#define STRUCTERS_H

#include "constants.h"
#define MAX_LEN_SURNAME 10
#define MAX_LEN_NAME 10
#define MAX_COUNT_DIGITS 7
#define MAX_LEN_ADDRESS 20
#define MAX_LEN_MONTH 9
#define MAX_LEN_POSITION 20
#define MAX_LEN_ORGANIZATION 20

typedef enum status
{
    personal,
    service
} status_t;

typedef struct
{
    int day;
    char month[MAX_LEN_MONTH + 1];
    int year; 
} personal_t;

typedef struct
{
    char position[MAX_LEN_POSITION + 1];
    char organization[MAX_LEN_ORGANIZATION + 1];    
} service_t;


typedef union
{
    personal_t personal_status;
    service_t service_status;
} variable;


typedef struct
{
    char surname[MAX_LEN_SURNAME + 1];
    char name[MAX_LEN_NAME + 1];
    char number[MAX_COUNT_DIGITS + 1];
    char address[MAX_LEN_ADDRESS + 1];
    status_t status_type;    
    variable human_status;
} subscriber;


typedef struct
{
    int index;
    char number[MAX_COUNT_DIGITS + 1];
} keys;

typedef struct
{
    subscriber human[COUNT_SUBSCRIBER];
    keys key[COUNT_SUBSCRIBER];
    int table_size;
} table_t;

#endif
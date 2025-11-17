#ifndef INCLUDE_H
#define INCLUDE_H

#include <stdarg.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


typedef enum {
    OK = 0,
    BAD_INPUT = 1,
    OVERFLOW_ERROR = 2,
    MALLOC_ERROR = 3,
    POINTER_ERROR = 4,
    WRONG_ARGUMENTS = 5,
    BAD_BASE = 6
} errorCodes;


errorCodes convertToBase(int decimal, char* result, int r);
int add(int a, int b);
int strSize(const char *str);
errorCodes reverse(char* array);
errorCodes rightShift(char* array);

#endif
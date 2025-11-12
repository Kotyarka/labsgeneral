#ifndef INCLUDE_H
#define INCLUDE_H

#include <stdarg.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define EPSILON 1e-12
#define MAX_ACCURACY 1000

typedef enum {
    OK = 0,
    BAD_INPUT = 1,
    OVERFLOW_ERROR = 2,
    MALLOC_ERROR = 3,
    POINTER_ERROR = 4,
    WRONG_ARGUMENTS = 5,
    BAD_BASE = 6
} errorCodes;

errorCodes isFinitePresent(int base, int* results, int count, ...);
#endif
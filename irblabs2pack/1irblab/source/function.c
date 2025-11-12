
#include "../include/include.h"

errorCodes isFinitePresent(int base, int* results, int count, ...) {
    if (base < 2) {
        return BAD_BASE;
    }
    if (results == NULL) {
        return POINTER_ERROR;
    }
    if (count <= 0) {
        return WRONG_ARGUMENTS;
    }

    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        double number = va_arg(args, double);
        
        if (number <= 0.0 || number >= 1.0) {
            va_end(args);
            return BAD_INPUT;
        }

        int cycleCount = 0;
        int remaindersSize = 1;
        double *remainders = malloc(remaindersSize * sizeof(double));
        if (remainders == NULL) {
            va_end(args);
            return MALLOC_ERROR;
        }

        double currentNumber = number;
        int finite = 0;

        while (currentNumber > EPSILON && cycleCount < MAX_ACCURACY) {
            currentNumber *= base;
            int intNumber = (int)currentNumber;
            currentNumber -= intNumber;
            
            if (currentNumber < EPSILON || (1.00 - currentNumber) < EPSILON) {
                finite = 1;
                break;
            }

            int foundCycle = 0;
            for (int j = 0; j < cycleCount; j++) {
                if (fabs(currentNumber - remainders[j]) < EPSILON) {
                    foundCycle = 1;
                    break;
                }
            }
            
            if (foundCycle) {
                finite = 0;
                break;
            }

            if (cycleCount == remaindersSize) {
                remaindersSize *= 2;
                double *newRemainders = realloc(remainders, remaindersSize * sizeof(double));
                if (newRemainders == NULL) {
                    free(remainders);
                    va_end(args);
                    return MALLOC_ERROR;
                }
                remainders = newRemainders;
            }

            remainders[cycleCount] = currentNumber;
            cycleCount++;
        }

        if (cycleCount >= MAX_ACCURACY) {
            finite = (currentNumber < EPSILON);
        }

        results[i] = finite;
        free(remainders);
    }

    va_end(args);
    return OK;
}

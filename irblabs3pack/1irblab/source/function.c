#include "../include/include.h"

errorCodes decimalToOther(int number, int power, int* result, int* resultSize) {
    int countOfConquctions = 0;
    int mask = (1 << power) - 1;
    while (number > 0) {
        result[countOfConquctions] = number & mask;
        number = number >> power;
        countOfConquctions++;
    }

    resultSize* = countOfConquctions;
    return OK;

}

errorCodes printNumber(int number, int power)
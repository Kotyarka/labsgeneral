#include "../include/functions.h"

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include <stdlib.h>
#include <ctype.h>

int isValidSymbolInBase(char c, int base) {
    if (c == '+' || c == '-') {
        return 1;
    }
    if (base >= 2 && base <= 9) {
        return (c >= '0' && c < ('0' + base));
    }
    return isdigit(c) || (c >= 'A' && c < ('A' + base - 10));
}

void printUniversal(void* stream, TypeOfPrint type, const char* format, ...) {
    va_list args;
    va_start(args, format);

    if (type == PRINT_TO_FILE_STREAM) {
        vfprintf((FILE*)stream, format, args);
    } else if (type == PRINT_TO_STRING) {
        vsprintf((char*)stream + strlen(stream), format, args);
    }

    va_end(args);
}

errorCodes printToStreamReversed(void* stream, TypeOfPrint type, const char* reversedStr, int indOfEnd) {
    if (!reversedStr) {
        return BAD_POINTER_ERROR;
    }
    if (indOfEnd < 0) {
        return BAD_INPUT_ERROR;
    }
    for (int i = indOfEnd; i >= 0; --i) {
        printUniversal(stream, type, "%c", reversedStr[i]);
    }
    return OK;
}

errorCodes convertToDecimal(const char* numReprInBase, int endOfNumRepr, FormatForChar formatChar, int base, int* decimalResult) {
    *decimalResult = 0;
    int value;
    int sign = 1;

    if (endOfNumRepr == 0) {
        return OK;
    }

    for (int i = 0; i < endOfNumRepr; i++) {
        char c = (numReprInBase[i]);
        if (c != formatChar(numReprInBase[i])) {
            return BAD_INPUT_ERROR;
        }

        if (!isValidSymbolInBase(toupper(c), base)) {
            return BAD_INPUT_ERROR;
        }

        if (i == 0 && c == '+') {
            continue;
        }
        if (i == 0 && c == '-') {
            sign = -1;
            continue;
        }

        if (isdigit(c)) {
            value = c - '0';
        } else if (isalpha(c)) {
            value = c - formatChar('A') + 10;
        } else {
            return BAD_INPUT_ERROR;
        }

        if (*decimalResult > INT_MAX / base) {
            return OVERFLOW_ERROR;
        }
        *decimalResult *= base;
        if (value > 0 && (*decimalResult > INT_MAX - value)) {
            return OVERFLOW_ERROR;
        }
        *decimalResult += value;
    }
    *decimalResult *= sign;
    return OK;
}

errorCodes convertDecimalToBase(int x, int base, FormatForChar formatChar, char* representation, int* ind) {
    if (representation == NULL || ind == NULL) {
        return BAD_POINTER_ERROR;
    }
    if (!(base >= 2 && base <= 36)) {
        return BAD_INPUT_ERROR;
    }

    *ind = 0;
    if (x == 0) {
        representation[0] = '0';
        ++(*ind);
        return OK;
    }

    int isNegative = (x < 0) ? 1 : 0;
    x = abs(x);

    while (x > 0) {
        int digit = x % base;
        if (digit < 10) {
            representation[*ind] = '0' + digit;
        } else {
            representation[*ind] = formatChar('A' + (digit - 10));
        }
        ++(*ind);
        x /= base;
    }
    if (isNegative) {
        representation[*ind] = '-';
        ++(*ind);
    }
    return OK;
}

errorCodes generateFibonacci(unsigned int n, unsigned int* size, unsigned int** fibResult) {
    if (!size || ! fibResult) {
        return BAD_POINTER_ERROR;
    }
    if (n < 1) {
        return BAD_INPUT_ERROR; 
    }
    unsigned int fibCap = 10; 
    unsigned int* fib = malloc(fibCap * sizeof(unsigned int));
    if (!fib) {
        return MEMORY_ALLOC_ERROR;
    }
    fib[0] = 1;
    fib[1] = 2;
    *size = 2;
    unsigned int nextFib;
    do {
        if (UINT_MAX - fib[*size - 1] < fib[*size - 2]) {
            free(fib);
            return OVERFLOW_ERROR;
        }
        nextFib = fib[*size - 1] + fib[*size - 2];
        
        fib[(*size)++] = nextFib;
        
        if (*size >= fibCap) {
            fibCap *= 2;
            unsigned int* newFib = realloc(fib ,fibCap * sizeof(unsigned int));
            if (!newFib) {
                free(fib);
                return MEMORY_ALLOC_ERROR;
            }
            fib = newFib;
        }
    } while (nextFib < n);
    *fibResult = fib;
    return OK;
}

errorCodes printMemoryDump(void* stream, TypeOfPrint typeOfPrint, void *ptr, long unsigned int sizeOfDataUnderPointer) {
    if (!stream || !ptr) {
        return BAD_POINTER_ERROR;
    }
    unsigned char *bytePtr = (unsigned char *)ptr;
    for (long unsigned int i = 0; i < sizeOfDataUnderPointer; ++i) {
        unsigned char byteValue = *(bytePtr + i);
        
        for (int j = 7; j >= 0; --j) {
            printUniversal(stream, typeOfPrint, "%d", (byteValue >> j) & 1);
        }
        
        printUniversal(stream, typeOfPrint, " ");
    }
    return OK;
}

errorCodes printNumberInBaseToDecimal(void* stream, TypeOfPrint typeOfPrint, FormatForChar formatChar, char const* numRepr, int base) {
    int decimalValue = 0;
    int res = convertToDecimal(numRepr, strlen(numRepr), formatChar, base, &decimalValue);
    if (res != OK) {
        return res;
    }
    printUniversal(stream, typeOfPrint, "%d", decimalValue);
    return OK;
}

errorCodes printNumberInBase(void* stream, TypeOfPrint typeOfPrint, FormatForChar formatChar, int number, int base) {
    if (!(base >= 2 && base <= 36)) {
        base = 10;
    }
    char baseRepr[100];
    int indOfRepr = 0;
    convertDecimalToBase(number, base, formatChar, baseRepr, &indOfRepr);
    printToStreamReversed(stream, typeOfPrint, baseRepr, indOfRepr - 1);
    return OK;
}

errorCodes printZeckendorf(void* stream, TypeOfPrint typeOfPrint, unsigned int num) {
    unsigned int* fib;
    unsigned int size = 0;
    int resultOfFibGeneration = generateFibonacci(num, &size, &fib);
    if (resultOfFibGeneration != OK) {
        return resultOfFibGeneration;
    }

    char* result = (char*)malloc(size + 1);
    if (!result) {
        free(fib);
        return MEMORY_ALLOC_ERROR;
    }

    int amountOfNumbers = 0;
    
    for (int i = size - 1; i >= 0; --i) {
        if (fib[i] <= num) {
            result[amountOfNumbers++] = '1';
            num -= fib[i];
        } else if (amountOfNumbers > 0) {
            result[amountOfNumbers++] = '0';
        }
    }

    printToStreamReversed(stream, typeOfPrint, result, amountOfNumbers - 1);
    printUniversal(stream, typeOfPrint, "%c", '1');

    free(fib);
    free(result);
    return OK;
}

errorCodes printIntToRoman(void* stream, TypeOfPrint typeOfPrint, int num) {
    if (!stream) {
        return BAD_STREAM_ERROR;
    }
    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    char* symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

    if (num < 0) {
        printUniversal(stream, typeOfPrint, "%c", '-');
        num *= -1;
    }

    if (num > 4000) {
        for (int i = 0; i < num / 1000; ++i) {
            printUniversal(stream, typeOfPrint, "%c", 'M');
        }
        num = num % 1000;
    }

    for (int i = 0; i < 13; i++) {
        while (num >= values[i]) {
            printUniversal(stream, typeOfPrint, "%s", symbols[i]);
            num -= values[i];           
        }
    }
    return OK;
}

errorCodes ownFlagsSupport(void* stream, TypeOfPrint typeOfPrint, const char* pos, va_list* args, int* toMove) {
    if (!stream || !pos || !args || !toMove) {
        return BAD_POINTER_ERROR;
    }
    int result = 0;
    *toMove = 0;
    switch (*pos) {
        case 'R':
            if (*(pos + 1) == 'o') {
                int num = va_arg(*args, int);
                result = printIntToRoman(stream, typeOfPrint, num);
                if (result == OK) {
                    *toMove = 2;
                }
                return result;
            }
            break;

        case 'Z':
            if (*(pos + 1) == 'r') {
                unsigned int num = va_arg(*args, unsigned int);
                result = printZeckendorf(stream, typeOfPrint, num);
                if (result == OK) {
                    *toMove = 2;
                }
                return result;  
            }
            break;

        case 'C':
            if (*(pos + 1) == 'v') {
                int number = va_arg(*args, int);
                int base = va_arg(*args, int);
                result = printNumberInBase(stream, typeOfPrint, tolower, number, base);
                if (result == OK) {
                    *toMove = 2;
                }
                return result;
            } else if (*(pos + 1) == 'V') {
                int number = va_arg(*args, int);
                int base = va_arg(*args, int);
                result = printNumberInBase(stream, typeOfPrint, toupper, number, base);
                if (result == OK) {
                    *toMove = 2;
                }
                return result;
            }
            break;

        case 't':
            if (*(pos + 1) == 'o') {
                char* numRepr = va_arg(*args, char*);
                int base = va_arg(*args, int);
                
                result = printNumberInBaseToDecimal(stream, typeOfPrint, tolower, numRepr, base);
                if (result == OK) {
                    *toMove = 2;
                }
                return result;

            } 
            break;

        case 'T':
            if (*(pos + 1) == 'O') {
                char* numRepr = va_arg(*args, char*);
                int base = va_arg(*args, int);
                
                result = printNumberInBaseToDecimal(stream, typeOfPrint, toupper, numRepr, base);
                if (result == OK) {
                    *toMove = 2;
                }
                
                return result;

            }
            break;
        
        case 'm':
            if (*(pos + 1) == 'i') {
                int num = va_arg(*args, int);
                result = printMemoryDump(stream, typeOfPrint, (void*)&num, sizeof(num));
                if (result == OK) {
                    *toMove = 2;
                }
                return result;
            } else if (*(pos + 1) == 'u') {
                unsigned int num = va_arg(*args, unsigned int);
                result = printMemoryDump(stream, typeOfPrint, (void*)&num, sizeof(num));
                if (result == OK) {
                    *toMove = 2;
                }
                return result;
            } else if (*(pos + 1) == 'd') {
                double num = va_arg(*args, double);
                result = printMemoryDump(stream, typeOfPrint, (void*)&num, sizeof(num));
                if (result == OK) {
                    *toMove = 2;
                }
                return result;
            } else if (*(pos + 1) == 'f') {
                float num = va_arg(*args, double);
                result = printMemoryDump(stream, typeOfPrint, (void*)&num, sizeof(num));
                if (result == OK) {
                    *toMove = 2;
                }
                return result;
            }
            break;
        default:
            return OK;
    }
    return OK;
}

errorCodes generalPrintf(void* stream, TypeOfPrint typeOfPrint, const char* format, va_list* args) {
    if (!stream || !format || !args) {
        return BAD_POINTER_ERROR;
    }
    if (typeOfPrint == PRINT_TO_STRING) {
        ((char*)stream)[0] = '\0';
    }
    const char* pos = format;
    char buffer[BUFFER_SIZE];
    int bufferPos = 0;

    while (*pos) {
        if (*pos == '%') {
            pos++;

            int toMove = 0;
            int resultOfFlag = ownFlagsSupport(stream, typeOfPrint, pos, args, &toMove);
            if (resultOfFlag != OK) {
                 return resultOfFlag;
            }
            if (toMove > 0) {
                pos += toMove;
                continue;
            }

            buffer[bufferPos++] = '%';
            while (*pos && !strchr("diufFeEgGxXoscpaA", *pos)) {
                buffer[bufferPos++] = *pos++;
                if (bufferPos >= BUFFER_SIZE - 1) {
                    break;
                }
            }
            if (bufferPos < BUFFER_SIZE - 1) {
                buffer[bufferPos++] = *pos;
            }

            buffer[bufferPos] = '\0';
            if (typeOfPrint == PRINT_TO_FILE_STREAM) {
                vfprintf((FILE*)stream, buffer, *args);
            }
            else {
                vsprintf((char*)stream + strlen(stream), buffer, *args);
            }

            bufferPos = 0;
        } else {
            printUniversal(stream, typeOfPrint, "%c", *pos);
        }
        pos++;
    }
    return OK;
}

errorCodes overfprintf(FILE* stream, char const* format, ...) {
    va_list args;
    va_start(args, format);
    int res = generalPrintf((void*)stream, PRINT_TO_FILE_STREAM, format, &args);
    va_end(args);
    return res;
}

errorCodes oversprintf(char* stream, char const* format, ...) {
    va_list args;
    va_start(args, format);
    int res = generalPrintf((void*)stream, PRINT_TO_STRING, format, &args);
    va_end(args);
    return res;
}
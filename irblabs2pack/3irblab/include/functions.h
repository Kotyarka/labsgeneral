#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdarg.h>

#define INITIAL_SIZE_OF_FIB 10
#define BUFFER_SIZE 1024

typedef enum {
    OK = 0,
    BAD_INPUT_ERROR = 1,
    OVERFLOW_ERROR = 2,
    BAD_POINTER_ERROR = 3,
    MEMORY_ALLOC_ERROR = 4,
    WRONG_ARGUMENTS_ERROR = 5,
    NOT_A_DOUBLE_ERROR = 6,
    NOT_AN_INTEGER_ERROR = 7,
    BAD_STREAM_ERROR = 8,
    FILE_ERROR = 9,
} errorCodes;

typedef enum TypeOfPrint {
    PRINT_TO_FILE_STREAM = 1,
    PRINT_TO_STRING = 2,
} TypeOfPrint;


typedef void (*Printer)(void* stream, TypeOfPrint type, const char* format, ...);
typedef int (*FormatForChar)(int);

int isValidSymbolInBase(char c, int base);
errorCodes convertToDecimal(const char* numReprInBase, int endOfNumRepr, FormatForChar formatChar, int base, int* decimalResult);
void printUniversal(void* stream, TypeOfPrint type, const char* format, ...);
errorCodes convertDecimalToBase(int x, int base, FormatForChar formatChar, char* representation, int* ind);
errorCodes generateFibonacci(unsigned int n, unsigned int* size, unsigned int** fibResult);
errorCodes printToStreamReversed(void* stream, TypeOfPrint type, const char* reversedStr, int indOfEnd);

errorCodes printIntToRoman(void* stream, TypeOfPrint typeOfPrint, int num);
errorCodes printZeckendorf(void* stream, TypeOfPrint typeOfPrint, unsigned int num);
errorCodes printNumberInBase(void* stream, TypeOfPrint typeOfPrint, FormatForChar formatChar, int number, int base);
errorCodes printMemoryDump(void* stream, TypeOfPrint typeOfPrint, void *ptr, long unsigned int sizeOfDataUnderPointer);

errorCodes handleCustomFlags(void* stream, TypeOfPrint typeOfPrint, const char* pos, va_list* args, int* toMove);

errorCodes overfprintf(FILE* stream, const char* format, ...);
errorCodes oversprintf(char* stream, char const* format, ...);

#endif
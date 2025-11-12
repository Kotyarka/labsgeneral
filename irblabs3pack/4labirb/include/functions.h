#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdarg.h>

typedef enum {
    OK,
    BAD_POINTER_ERROR,
    BAD_INPUT_ERROR,
    OVERFLOW_ERROR,
    MEMORY_ALLOC_ERROR,
    BAD_STREAM_ERROR
} errorCodes;

typedef enum {
    SCAN_FROM_FILE_STREAM,
    SCAN_FROM_STRING
} TypeOfScan;

typedef int (*FormatForChar)(int);

#define BUFFER_SIZE 256

int isValidSymbolInBase(char c, int base);
errorCodes zeckendorfToInt(const char* zeckendorfRepr, unsigned int* result);
errorCodes isValidRoman(const char *number, int* isValid);
errorCodes romanToInt(const char *roman, int *result);
errorCodes convertToDecimal(const char* numReprInBase, int endOfNumRepr, FormatForChar formatChar, int base, int* decimalResult);
errorCodes handleCustomScanFlags(void* stream, TypeOfScan typeOfScan, const char* pos, va_list* args, int* toMove);
errorCodes generalScanf(void* stream, TypeOfScan typeOfScan, const char* format, va_list* args);
errorCodes overfscanf(FILE* stream, char const* format, ...);
errorCodes oversscanf(const char* stream, char const* format, ...);

#endif
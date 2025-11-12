#ifndef INCLUDE_H
#define INCLUDE_H

#include <stdarg.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    OK = 0,
    BAD_INPUT = 1,
    BAD_FILENAME = 2,
    OPEN_FILE_ERROR = 3,
    MEMORY_ALLOCATION_ERROR = 4,
    INVALID_PARAMETER = 5,
    FORMATTING_ERROR = 6,
    READ_ERROR = 7,
    WRITE_ERROR = 8
} errorCodes;

errorCodes formattingProcess(FILE* inputFile, FILE* outputFile);
errorCodes formatLine(char* line, FILE* outputFile);
int wordCounter(char *line, char** words);
int is_readable(char c);

#endif
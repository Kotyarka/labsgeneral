#include "../include/functions.h"

#include <regex.h>
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int isValidSymbolInBase(char c, int base) {
    if (c == '+' || c == '-') {
        return 1;
    }
    if (base >= 2 && base <= 9) {
        return (c >= '0' && c < ('0' + base));
    }
    return isdigit(c) || (c >= 'A' && c < ('A' + base - 10));
}

errorCodes zeckendorfToInt(const char* zeckendorfRepr, unsigned int* result) {
    if (!zeckendorfRepr || !result) {
        return BAD_POINTER_ERROR;
    }
    *result = 0;
    unsigned int fibPrev = 1;
    unsigned int fibCurr = 2;

    int len = strlen(zeckendorfRepr);
    for (int i = 0; i < len - 1; i++) {
        if (zeckendorfRepr[i] == '1') {
            *result += fibPrev;
        }
        unsigned int fibNext = fibPrev + fibCurr;
        fibPrev = fibCurr;
        fibCurr = fibNext;
    }
    return OK;
}

errorCodes isValidRoman(const char *number, int* isValid) {
    if (!number || !isValid) {
        return BAD_POINTER_ERROR;
    }
    regex_t regex;
    int ret;
    
    const char *pattern = "^M{0,3}(CM|CD|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})$";
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        *isValid = 0;
        return BAD_INPUT_ERROR;
    }    
    ret = regexec(&regex, number, 0, NULL, 0);
    regfree(&regex);

    *isValid = (ret == 0);
    return OK;
}

errorCodes romanToInt(const char *roman, int *result) {
    if (!roman || !result) {
        return BAD_POINTER_ERROR;
    }
    int total = 0;
    int prev = 0;
    int isValid = 0;
    int resOfValidation = isValidRoman(roman, &isValid);
    if (!isValid || resOfValidation != OK) {
        return BAD_INPUT_ERROR;
    }

    while (*roman) {
        int current = 0;
        switch (*roman) {
            case 'I': current = 1; break;
            case 'V': current = 5; break;
            case 'X': current = 10; break;
            case 'L': current = 50; break;
            case 'C': current = 100; break;
            case 'D': current = 500; break;
            case 'M': current = 1000; break;
            default: return BAD_INPUT_ERROR;
        }

        if (current > prev) {
            total += current - 2 * prev;
        } else {
            total += current;
        }

        prev = current;
        roman++;
    }

    *result = total;
    return OK;
}

errorCodes convertToDecimal(const char* numReprInBase, int endOfNumRepr, FormatForChar formatChar, int base, int* decimalResult) {
    if (!numReprInBase || !decimalResult || !formatChar) {
        return BAD_POINTER_ERROR;
    }
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

errorCodes handleCustomScanFlags(void* stream, TypeOfScan typeOfScan, const char* pos, va_list* args, int* toMove) {
    int res = 0;
    *toMove = 0;
    switch (*pos) {
        case 'R':
            if (*(pos + 1) == 'o') {
                char buffer[100];
                int* result = va_arg(*args, int*);
                if (typeOfScan == SCAN_FROM_FILE_STREAM) {
                    fscanf((FILE*)stream, "%s", buffer);
                } else {
                    sscanf((const char*)stream, "%s", buffer);
                }
                
                res = romanToInt(buffer, result);
                if (res != OK) {
                    return res;
                }
                *toMove = 2;
                return OK;
            }
            break;

        case 'Z':
            if (*(pos + 1) == 'r') {
                char buffer[100];
                unsigned int* result = va_arg(*args, unsigned int*);
                if (typeOfScan == SCAN_FROM_FILE_STREAM) {
                    fscanf((FILE*)stream, "%s", buffer);
                } else {
                    sscanf((const char*)stream, "%s", buffer);
                }
                res = zeckendorfToInt(buffer, result);
                if (res != OK) {
                    return res;
                }
                *toMove = 2;
                return OK;
            }
            break;

        case 'C':
            if (*(pos + 1) == 'v') {
                char buffer[100];
                int* result = va_arg(*args, int*);
                int base = va_arg(*args, int);
                if (base < 2 || base > 36) {
                    base = 10;
                }

                if (typeOfScan == SCAN_FROM_FILE_STREAM) {
                    fscanf((FILE*)stream, "%s", buffer);
                } else {
                    sscanf((const char*)stream, "%s", buffer);
                }

                res = convertToDecimal(buffer, strlen(buffer), tolower, base, result);
                if (res != OK) {
                    return res;
                }
                *toMove = 2;
                return OK;
            }
            else if(*(pos + 1) == 'V') {
                char buffer[100];
                int* result = va_arg(*args, int*);
                int base = va_arg(*args, int);
                if (base < 2 || base > 36) {
                    base = 10;
                }

                if (typeOfScan == SCAN_FROM_FILE_STREAM) {
                    fscanf((FILE*)stream, "%s", buffer);
                } else {
                    sscanf((const char*)stream, "%s", buffer);
                }

                res = convertToDecimal(buffer, strlen(buffer), toupper, base, result);
                if (res != OK) {
                    return res;
                }
                *toMove = 2;
                return OK;
            }
            break;
    }
    return OK;
}

errorCodes generalScanf(void* stream, TypeOfScan typeOfScan, const char* format, va_list* args) {
    if (!stream || !format || !args) {
        return BAD_POINTER_ERROR;
    }
    const char* pos = format;
    char buffer[BUFFER_SIZE];

    while (*pos) {
        if (*pos == '%') {
            pos++;

            int toMove = 0;
            int resultOfFlag = handleCustomScanFlags(stream, typeOfScan, pos, args, &toMove);
            if (resultOfFlag != OK) {
                return resultOfFlag;
            }
            if (toMove > 0) {
                pos += toMove;
                continue;
            }

            buffer[0] = '%'; 
            int bufferPos = 1;

            while (*pos && !strchr("diufFeEgGxXoscpaA", *pos)) {
                buffer[bufferPos++] = *pos++;
                if (bufferPos >= BUFFER_SIZE - 1) {
                    break; 
                }
            }
            char formatToMove = *pos;
            buffer[bufferPos] = *pos;
            buffer[bufferPos + 1] = '\0';
        
            if (typeOfScan == SCAN_FROM_FILE_STREAM) {
                if (vfscanf((FILE*)stream, buffer, *args) <= 0) {
                    return BAD_INPUT_ERROR;
                }
            } else {
                if (vsscanf((const char*)stream, buffer, *args) <= 0) {
                    return BAD_INPUT_ERROR;
                }
            }

            switch (formatToMove) {
                case 'd': case 'i': case 'u': case 'x': case 'X': case 'o':
                    va_arg(*args, int*);
                    break;
                case 'f': case 'F': case 'e': case 'E': case 'g': case 'G': case 'a': case 'A':
                    va_arg(*args, double*);
                    break;
                case 'c':
                    va_arg(*args, int*); 
                    break;
                case 's':
                    va_arg(*args, char*); 
                    break;
                case 'p':
                    va_arg(*args, void**);
                    break;
                case 'n':
                    va_arg(*args, int*);
                    break;
                default:
                    break;
            }

        } else {
            char c;
            if (typeOfScan == SCAN_FROM_FILE_STREAM) {
                if (fscanf((FILE*)stream, "%c", &c) < 0) {
                    return BAD_INPUT_ERROR;
                }
            } else {
                if (sscanf((const char*)stream, "%c", &c) < 0) {
                    return BAD_INPUT_ERROR;
                }
            }
            if (c != *pos) {
                return BAD_INPUT_ERROR;
            }
        }
        pos++;
    }
    return OK;
}

errorCodes overfscanf(FILE* stream, char const* format, ...) {
    va_list args;
    va_start(args, format);
    int res = generalScanf((void*)stream, SCAN_FROM_FILE_STREAM, format, &args);
    va_end(args);
    return res;
}

errorCodes oversscanf(const char* stream, char const* format, ...) {
    va_list args;
    va_start(args, format);
    int res = generalScanf((void*)stream, SCAN_FROM_STRING, format, &args);
    va_end(args);
    return res;
}
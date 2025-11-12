#include "../include/functions.h"
#include "../include/errors_macro.h"
#include <stddef.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>

int overfprintf( FILE * stream, const char * format, ... ) {
    va_list(args);
    va_start(args, format);
    
    int writtenChars = 0;
    const char *p = format;

    while (*p != '\0') {
        if (*p != '%') {
            fputc(*p, stream);
            writtenChars++;
            p++;
            continue;
        }
        p++;

        switch (*p) {
            case 'd':
            case 'i': {
                int value = va_arg(args, int);
                writtenChars += fprintfInt(stream, value);
                break;
            }
            case 's': {
                char *str = va_arg(args, char*);
                writtenChars += fputs(str, stream);
                break;
            }
            case 'c': {
                char ch = (char)va_arg(args, int);
                fputc(ch, stream);
                writtenChars++;
                break;
            }
            case 'f': {
                double value = va_arg(args, double);
                writtenChars += fprintfDouble(stream, value);
                break;
            }
            case '%': {
                fputc('%', stream);
                writtenChars++;
                break;
            }
            case 'R': {
                p++;
                if (*p == 'o') {
                    int value = va_arg(args, int);
                    writtenChars += fprintfRo(stream, value);
                    break;
                } else {
                    fputc('%', stream);
                    fputc('R', stream);
                    writtenChars += 2;
                    continue;
                }
            }
            default: {

                fputc('%', stream);
                fputc(*p, stream);
                writtenChars += 2;
                break;
            }
        }
        p++;
    }
    
    return writtenChars;
}

int fprintfInt(FILE *stream, int value) {
    char buffer[32];
    int i = 0;
    int writtenChars = 0;
    
    if (value < 0) {
        fputc('-', stream);
        writtenChars++;
        value = -value;
    }

    do {
        buffer[i++] = '0' + (value % 10);
        value /= 10;
    } while (value > 0);
    
    while (i > 0) {
        fputc(buffer[--i], stream);
        writtenChars++;
    }
    
    return writtenChars;
}

int fprintfDouble(FILE *stream, double value) {
    int writtenChars = 0;
    
    int int_part = (int)value;
    writtenChars += fprintfInt(stream, int_part);
    
    fputc('.', stream);
    writtenChars++;
    
    double fractional = value - int_part;
    if (fractional < 0) fractional = -fractional;
    
    for (int i = 0; i < 6; i++) {
        fractional *= 10;
        int digit = (int)fractional;
        fputc('0' + digit, stream);
        writtenChars++;
        fractional -= digit;
    }
    
    return writtenChars;
}

int fprintfRo(FILE *stream, int value) {
    int writtenChars = 0;

    int arabic[13] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    char* roman[13] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < value / arabic[i]; j++) {
            fputs(roman[i], stream);
            writtenChars += strlen(roman[i]);
            value %= arabic[i];
        }
    }
    return writtenChars;
}

int fprintfZk(FILE *stream, int value) {
    int writtenChars = 0;


}
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdbool.h>

#define VARIABLES_COUNT 26

typedef struct {
    int variables[VARIABLES_COUNT];
    bool initialized[VARIABLES_COUNT];
} Interpreter;

void init_interpreter(Interpreter* interpreter);
bool execute_line(Interpreter* interpreter, const char* line, int line_num, FILE* log_file);
void log_state(Interpreter* interpreter, const char* command, const char* operation, int line_num, FILE* log_file);
int fast_power(int base, int exponent);
#endif
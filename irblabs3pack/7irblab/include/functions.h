#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct {
    char name;
    int value;
    int initialized;
} Variable;

typedef struct {
    Variable variables[27];
    FILE *log_file;
} InterpreterContext;

InterpreterContext* interpreter_init();
void interpreter_cleanup(InterpreterContext* context);
int process_line(InterpreterContext* context, char* line, int line_num);

int evaluate_expression(char* expr);
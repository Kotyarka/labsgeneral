#include "../include/functions.h"

void remove_spaces(char* str) {
    char* i = str;
    char* j = str;
    while (*j != '\0') {
        *i = *j++;
        if (*i != ' ') {
            i++;
        }
    }
    *i = '\0';
}

InterpreterContext* interpreter_init() {
    InterpreterContext* context = (InterpreterContext*)malloc(sizeof(InterpreterContext));
    if (!context) {
        return NULL;
    }
    
    // Инициализация переменных
    for (int i = 0; i < MAX_VARIABLES; i++) {
        context->variables[i].name = 'A' + i;
        context->variables[i].value = 0;
        context->variables[i].initialized = 0;
    }
    
    // Открываем файл трассировки
    context->log_file = fopen(LOG_FILENAME, "w");
    if (!context->log_file) {
        free(context);
        return NULL;
    }
    
    return context;
}

void interpreter_cleanup(InterpreterContext* context) {
    if (context) {
        if (context->log_file) {
            fclose(context->log_file);
        }
        free(context);
    }
}
int get_variable_index(char name) {
    if (name >= 'A' && name <= 'Z') {
        return name - 'A';
    }
    return -1;
}

int evaluate_expression(char* expr) {
    char* current = expr;
    int result = parse_term(&current);
    
    while (*current == '+' || *current == '-') {
        char op = *current;
        current++;
        int right = parse_term(&current);
        
        if (op == '+') {
            result = result + right;
        } else {
            result = result - right;
        }
    }
    
    return result;
}


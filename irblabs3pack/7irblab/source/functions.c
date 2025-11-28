#include "../include/functions.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void init_interpreter(Interpreter* interpreter) {
    for (int i = 0; i < VARIABLES_COUNT; i++) {
        interpreter->variables[i] = 0;
        interpreter->initialized[i] = false;
    }
}

int fast_power(int base, int exponent) {
    if (exponent < 0) return 0;
    if (exponent == 0) return 1;
    
    int result = 1;
    while (exponent > 0) {
        if (exponent & 1) {
            result *= base;
        }
        base *= base;
        exponent >>= 1;
    }
    return result;
}

static int get_variable_index(char name) {
    if (name >= 'A' && name <= 'Z') {
        return name - 'A';
    }
    return -1;
}

static int parse_expression(Interpreter* interpreter, const char** expr);

static int parse_primary(Interpreter* interpreter, const char** expr) {
    while (isspace(**expr)) (*expr)++;
    
    if (**expr == '(') {
        (*expr)++;
        int result = parse_expression(interpreter, expr);
        while (isspace(**expr)) (*expr)++;
        if (**expr != ')') {
            return 0;
        }
        (*expr)++;
        return result;
    }
    
    if (isdigit(**expr)) {
        int num = 0;
        while (isdigit(**expr)) {
            num = num * 10 + (**expr - '0');
            (*expr)++;
        }
        return num;
    }
    
    if (**expr >= 'A' && **expr <= 'Z') {
        char var_name = **expr;
        (*expr)++;
        int var_index = get_variable_index(var_name);
        if (interpreter->initialized[var_index]) {
            return interpreter->variables[var_index];
        }
        return 0;
    }
    
    return 0;
}

static int parse_power(Interpreter* interpreter, const char** expr) {
    int left = parse_primary(interpreter, expr);
    
    while (true) {
        while (isspace(**expr)) (*expr)++;
        if (**expr != '^') break;
        
        (*expr)++;
        int right = parse_primary(interpreter, expr);
        left = fast_power(left, right);
    }
    
    return left;
}

static int parse_term(Interpreter* interpreter, const char** expr) {
    int left = parse_power(interpreter, expr);
    
    while (true) {
        while (isspace(**expr)) (*expr)++;
        char op = **expr;
        if (op != '*' && op != '/') break;
        
        (*expr)++;
        int right = parse_power(interpreter, expr);
        
        if (op == '*') {
            left *= right;
        } else {
            if (right != 0) {
                left /= right;
            }
        }
    }
    
    return left;
}

static int parse_expression(Interpreter* interpreter, const char** expr) {
    int left = parse_term(interpreter, expr);
    
    while (true) {
        while (isspace(**expr)) (*expr)++;
        char op = **expr;
        if (op != '+' && op != '-') break;
        
        (*expr)++;
        int right = parse_term(interpreter, expr);
        
        if (op == '+') {
            left += right;
        } else {
            left -= right;
        }
    }
    
    return left;
}

static bool parse_assignment(Interpreter* interpreter, const char* line) {
    const char* ptr = line;
    
    while (isspace(*ptr)) ptr++;
    
    if (*ptr < 'A' || *ptr > 'Z') return false;
    char var_name = *ptr;
    ptr++;
    
    while (isspace(*ptr)) ptr++;
    if (*ptr != '=') return false;
    ptr++;
    
    int value = parse_expression(interpreter, &ptr);
    
    int var_index = get_variable_index(var_name);
    interpreter->variables[var_index] = value;
    interpreter->initialized[var_index] = true;
    
    return true;
}

static bool parse_print(Interpreter* interpreter, const char* line) {
    const char* ptr = line;
    
    while (isspace(*ptr)) ptr++;
    
    if (strncmp(ptr, "print", 5) != 0) return false;
    ptr += 5;
    
    while (isspace(*ptr)) ptr++;
    if (*ptr != '(') return false;
    ptr++;
    
    while (isspace(*ptr)) ptr++;
    
    if (*ptr < 'A' || *ptr > 'Z') return false;
    char var_name = *ptr;
    ptr++;
    
    while (isspace(*ptr)) ptr++;
    if (*ptr != ')') return false;
    
    int var_index = get_variable_index(var_name);
    if (interpreter->initialized[var_index]) {
        printf("%d\n", interpreter->variables[var_index]);
    } else {
        printf("0\n");
    }
    
    return true;
}

void log_state(Interpreter* interpreter, const char* command, const char* operation, int line_num, FILE* log_file) {
    fprintf(log_file, "[%d] %s\n| ", line_num, command);
    
    bool first = true;
    for (int i = 0; i < VARIABLES_COUNT; i++) {
        if (interpreter->initialized[i]) {
            if (!first) {
                fprintf(log_file, ", ");
            }
            fprintf(log_file, "%c=%d", 'A' + i, interpreter->variables[i]);
            first = false;
        }
    }
    
    fprintf(log_file, " | %s\n", operation);
}

bool execute_line(Interpreter* interpreter, const char* line, int line_num, FILE* log_file) {
    char cleaned_line[256];
    int j = 0;
    
    for (int i = 0; line[i] != '\0' && line[i] != '\n'; i++) {
        if (!isspace(line[i]) || (j > 0 && !isspace(cleaned_line[j-1]))) {
            cleaned_line[j++] = line[i];
        }
    }
    cleaned_line[j] = '\0';
    
    if (strlen(cleaned_line) == 0) {
        return true;
    }
    
    const char* operation = "Unknown operation";
    
    if (strchr(cleaned_line, '=') != NULL) {
        if (parse_assignment(interpreter, cleaned_line)) {
            operation = "Assignment";
        } else {
            return false;
        }
    } else if (strncmp(cleaned_line, "print", 5) == 0) {
        if (parse_print(interpreter, cleaned_line)) {
            operation = "Print";
        } else {
            return false;
        }
    } else {
        return false;
    }
    
    log_state(interpreter, cleaned_line, operation, line_num, log_file);
    return true;
}
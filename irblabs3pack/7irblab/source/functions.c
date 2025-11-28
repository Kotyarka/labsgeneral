#include "../include/functions.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int vars[26] = {0};
int initialized[26] = {0};

// Функция для проверки корректности выражения (объявляем в начале)
int is_valid_expression(const char *line) {
    if (line == NULL || *line == '\0') {
        return 0;
    }
    
    int paren_count = 0;
    int expect_operand = 1; // 1 - ожидаем операнд, 0 - ожидаем оператор
    int has_digit_or_var = 0;
    
    for (const char *p = line; *p; p++) {
        if (*p == ' ' || *p == '\t') {
            continue;
        }
        
        if (expect_operand) {
            // Ожидаем операнд: число, переменная, унарный минус или открывающая скобка
            if (*p == '-' && (p == line || *(p-1) == '(')) {
                // Унарный минус - продолжаем ожидать операнд
                continue;
            } else if (isdigit(*p)) {
                // Число
                while (isdigit(*p)) p++;
                p--;
                expect_operand = 0;
                has_digit_or_var = 1;
            } else if (isalpha(*p) && isupper(*p)) {
                // Переменная (только заглавные буквы)
                expect_operand = 0;
                has_digit_or_var = 1;
            } else if (*p == '(') {
                paren_count++;
            } else {
                return 0; // Некорректный символ
            }
        } else {
            // Ожидаем оператор или закрывающую скобку
            if (*p == '+' || *p == '-' || *p == '*' || *p == '/' || *p == '^') {
                expect_operand = 1;
            } else if (*p == ')') {
                if (paren_count <= 0) return 0; // Лишняя закрывающая скобка
                paren_count--;
            } else {
                return 0; // Некорректный символ
            }
        }
    }
    
    return (paren_count == 0) && has_digit_or_var && !expect_operand;
}

void skip_spaces(char **s) {
    while (**s == ' ' || **s == '\t')
        (*s)++;
}

int get_var_value(char name) {
    int id = name - 'A';
    if (!initialized[id]) {
        printf("Error: variable %c is not initialized\n", name);
        return 0;
    }
    return vars[id];
}

int parse_expression(char **s) {
    int value = parse_term(s);
    
    skip_spaces(s);
    while (**s == '+' || **s == '-') {
        char op = **s;
        (*s)++;
        int right = parse_term(s);
        
        if (op == '+') value += right;
        else value -= right;
        
        skip_spaces(s);
    }
    return value;
}

int parse_term(char **s) {
    int value = parse_factor(s);
    
    skip_spaces(s);
    while (**s == '*' || **s == '/') {
        char op = **s;
        (*s)++;
        int right = parse_factor(s);
        
        if (op == '*') value *= right;
        else {
            if (right == 0) {
                printf("Error: division by zero\n");
                return value;
            }
            value /= right;
        }
        skip_spaces(s);
    }
    return value;
}

int parse_factor(char **s) {
    return parse_power(s);
}

int parse_power(char **s) {
    skip_spaces(s);
    int value;

    if (isalpha(**s)) {
        if (!isupper(**s)) {
            printf("Error: variable name must be uppercase letter\n");
            return 0;
        }
        value = get_var_value(**s);
        (*s)++;
    } else if (isdigit(**s) || (**s == '-' && isdigit((*s)[1]))) {
        value = strtol(*s, s, 10);
    } else if (**s == '(') {
        (*s)++;
        value = parse_expression(s);
        if (**s != ')') {
            printf("Error: missing closing parenthesis\n");
            return value;
        }
        (*s)++;
    } else {
        printf("Syntax error: unexpected character '%c'\n", **s);
        return 0;
    }

    skip_spaces(s);
    if (**s == '^') {
        (*s)++;
        int right = parse_power(s);
        
        if (value == 0 && right < 0) {
            printf("Error: zero cannot be raised to a negative power\n");
            return 0;
        }
        value = (int) pow(value, right);
    }
    return value;
}

void log_state(FILE *trace, const char *line, const char *opDescription, int *operation_counter) {
    fprintf(trace, "[%d] %s\n", *operation_counter, line);

    // Вывод всех инициализированных переменных
    int first = 1;
    for (int i = 0; i < 26; i++) {
        if (initialized[i]) {
            if (!first) fprintf(trace, ", ");
            fprintf(trace, "%c=%d", 'A' + i, vars[i]);
            first = 0;
        }
    }

    fprintf(trace, " | %s\n", opDescription);
    (*operation_counter)++;
}

void process_line(FILE *trace, char *line, int *operation_counter) {
    char original[MAX_LINE];
    strcpy(original, line);

    char *s = line;
    skip_spaces(&s);

    if (strlen(s) == 0) {
        return; // Пустая строка
    }

    // Проверка на команду print
    if (strncmp(s, "print", 5) == 0) {
        s += 5;
        skip_spaces(&s);

        if (*s != '(') {
            printf("Error: missing opening parenthesis after 'print'\n");
            return;
        }
        s++;
        skip_spaces(&s);

        if (!isalpha(*s) || !isupper(*s)) {
            printf("Error: print expects a single uppercase variable name\n");
            return;
        }
        
        char var = *s;
        s++;
        skip_spaces(&s);

        if (*s != ')') {
            printf("Error: missing closing parenthesis after variable\n");
            return;
        }
        s++;
        skip_spaces(&s);

        if (*s != '\0') {
            printf("Error: extra characters after print statement\n");
            return;
        }

        int val = get_var_value(var);
        printf("%d\n", val);
        
        // Специальный формат для print
        fprintf(trace, "[%d] %s\n", *operation_counter, original);
        
        int first = 1;
        for (int i = 0; i < 26; i++) {
            if (initialized[i]) {
                if (!first) fprintf(trace, ", ");
                fprintf(trace, "%c=%d", 'A' + i, vars[i]);
                first = 0;
            }
        }
        
        fprintf(trace, " | Print %c\n", var);
        (*operation_counter)++;
        return;
    }

    // Проверка на присваивание
    if (isalpha(*s) && isupper(*s)) {
        char var = *s;
        s++;
        skip_spaces(&s);

        if (*s == '=') {
            s++;
            skip_spaces(&s);
            
            // Проверяем корректность выражения перед вычислением
            if (!is_valid_expression(s)) {
                printf("Error: invalid expression\n");
                return;
            }
            
            int val = parse_expression(&s);
            skip_spaces(&s);
            
            if (*s != '\0') {
                printf("Error: extra characters after expression\n");
                return;
            }

            vars[var - 'A'] = val;
            initialized[var - 'A'] = 1;

            log_state(trace, original, "Assignment", operation_counter);
            return;
        }
    }

    // Проверка на арифметическую операцию
    if (is_valid_expression(s)) {
        int val = parse_expression(&s);
        skip_spaces(&s);
        if (*s != '\0') {
            printf("Error: extra characters after expression\n");
            return;
        }
        
        // Для арифметических операций показываем результат вычисления
        fprintf(trace, "[%d] %s\n", *operation_counter, original);
        
        int first = 1;
        for (int i = 0; i < 26; i++) {
            if (initialized[i]) {
                if (!first) fprintf(trace, ", ");
                fprintf(trace, "%c=%d", 'A' + i, vars[i]);
                first = 0;
            }
        }
        
        fprintf(trace, " | Arithmetic operation = %d\n", val);
        (*operation_counter)++;
    } else {
        printf("Error: invalid expression syntax\n");
    }
}
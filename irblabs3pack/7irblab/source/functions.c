#include "../include/functions.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int vars[26] = {0};
int initialized[26] = {0};
FILE *trace;

void skip_spaces(char **s) {
    while (**s == ' ' || **s == '\t')
        (*s)++;
}

int get_var_value(char name) {
    int id = name - 'A';
    if (!initialized[id]) {
        printf("Error: variable %c didnt initialise\n", name);
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
        else value /= right;
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
        value = get_var_value(**s);
        (*s)++;
    } else if (isdigit(**s) || (**s == '-' && isdigit((*s)[1]))) {
        value = strtol(*s, s, 10);
    } else if (**s == '(') {
        (*s)++;
        value = parse_expression(s);
        if (**s == ')') (*s)++;
    } else {
        printf("syntax error\n");
        return 0;
    }

    skip_spaces(s);
    if (**s == '^') {
        (*s)++;
        int right = parse_power(s);
        value = (int) pow(value, right);
    }
    return value;
}

void log_state(const char *line, const char *opDescription) {
    static int counter = 1;

    fprintf(trace, "[%d] %s | ", counter, line);

    int first = 1;
    for (int i = 0; i < 26; i++) {
        if (initialized[i]) {
            if (!first) fprintf(trace, ", ");
            fprintf(trace, "%c=%d", 'A' + i, vars[i]);
            first = 0;
        }
    }

    fprintf(trace, " | %s\n", opDescription);
    counter++;
}

void process_line(char *line) {
    char original[MAX_LINE];
    strcpy(original, line);

    char *s = line;
    skip_spaces(&s);

    if (strncmp(s, "print", 5) == 0) {
        s += 5;
        skip_spaces(&s);

        if (*s == '(') s++;
        skip_spaces(&s);

        char var = *s;
        int val = get_var_value(var);

        printf("%d\n", val);

        log_state(original, "Print");
        return;
    }

    if (isalpha(*s)) {
        char var = *s;
        s++;
        skip_spaces(&s);

        if (*s == '=') {
            s++;
            int val = parse_expression(&s);

            vars[var - 'A'] = val;
            initialized[var - 'A'] = 1;

            log_state(original, "Assignment");
            return;
        }
    }

    parse_expression(&s);
    log_state(original, "Arithmetic operation");
}

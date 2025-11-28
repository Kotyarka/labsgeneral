#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define MAX_LINE 256

#include <stdio.h>

void skip_spaces(char **s);
int get_var_value(char name);
int parse_expression(char **s);
int parse_term(char **s);
int parse_factor(char **s);
int parse_power(char **s);
int is_valid_expression(const char *line);
void log_state(FILE *trace, const char *line, const char *opDescription, int *operation_counter);
void process_line(FILE *trace, char *line, int *operation_counter);


#endif
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>

#define MAX_LINE 256

extern int vars[26];
extern int initialized[26];
extern FILE *trace;

void skip_spaces(char **s);
int get_var_value(char name);

int parse_expression(char **s);
int parse_term(char **s);
int parse_factor(char **s);
int parse_power(char **s);

void log_state(const char *line, const char *opDescription);
void process_line(char *line);

#endif

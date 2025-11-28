#include "./include/functions.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }
    
    FILE* input_file = fopen(argv[1], "r");
    if (!input_file) {
        fprintf(stderr, "Error: Cannot open input file %s\n", argv[1]);
        return 1;
    }
    
    FILE* log_file = fopen("trace.log", "w");
    if (!log_file) {
        fprintf(stderr, "Error: Cannot create log file\n");
        fclose(input_file);
        return 1;
    }
    
    Interpreter interpreter;
    init_interpreter(&interpreter);
    
    char line[256];
    int line_num = 1;
    
    while (fgets(line, sizeof(line), input_file)) {
        if (!execute_line(&interpreter, line, line_num, log_file)) {
            fprintf(stderr, "Error: Invalid syntax at line %d\n", line_num);
        }
        line_num++;
    }
    
    fclose(input_file);
    fclose(log_file);
    
    return 0;
}
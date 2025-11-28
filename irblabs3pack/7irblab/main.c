#include "./include/functions.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Error, usage: %s <input_file>\n", argv[0]);
        return 1;
    }
    
    log_file = fopen(LOG_FILENAME, "w");
    if (!log_file) {
        fprintf(stderr, "Error: Cannot open log file %s\n", LOG_FILENAME);
        return 1;
    }
    
    FILE* input_file = fopen(argv[1], "r");
    if (!input_file) {
        fprintf(stderr, "Error: Cannot open input file %s\n", argv[1]);
        fclose(log_file);
        return 1;
    }

    Variable variables[27];
    initialize_variables(variables);
    
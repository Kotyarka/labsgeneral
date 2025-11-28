#include <stdio.h>
#include <string.h>
#include "./include/functions.h"

// Объявляем глобальные переменные из functions.c
extern int vars[26];
extern int initialized[26];

int main() {
    FILE *trace = fopen("trace.log", "w");
    if (!trace) {
        printf("Error: cant open trace.log\n");
        return 1;
    }

    char line[MAX_LINE];
    int operation_counter = 1; // Локальный счётчик операций

    while (fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\n")] = 0;
        if (strlen(line) == 0) continue;

        process_line(trace, line, &operation_counter);
    }

    fclose(trace);
    return 0;
}
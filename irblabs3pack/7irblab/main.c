#include <stdio.h>
#include <string.h>
#include "./include/functions.h"

int main() {
    FILE *trace = fopen("trace.log", "w");
    if (!trace) {
        printf("Error: cant open trace.log\n");
        return 1;
    }

    char line[MAX_LINE];

    while (fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\n")] = 0;
        if (strlen(line) == 0) continue;

        process_line(trace, line);
    }

    fclose(trace);
    return 0;
}
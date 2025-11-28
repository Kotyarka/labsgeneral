#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "../include/functions.h"

// Объявляем глобальные переменные из functions.c
extern int vars[26];
extern int initialized[26];

void run(FILE *trace, const char *cmd) {
    char buf[MAX_LINE];
    strcpy(buf, cmd);
    process_line(trace, buf);
}

void reset_vars() {
    for (int i = 0; i < 26; i++) {
        vars[i] = 0;
        initialized[i] = 0;
    }
}

int main() {
    FILE *trace = fopen("test_trace.log", "w");
    assert(trace != NULL);

    reset_vars();

    run(trace, "A = 5");
    assert(initialized['A' - 'A'] == 1);
    assert(vars['A' - 'A'] == 5);

    run(trace, "B = A + 3");
    assert(vars['B' - 'A'] == 8);

    run(trace, "C = B * 2");
    assert(vars['C' - 'A'] == 16);

    run(trace, "D = (A + B) * 2");
    assert(vars['D' - 'A'] == (5 + 8) * 2);

    run(trace, "E = 2 ^ 5");
    assert(vars['E' - 'A'] == 32);

    run(trace, "F = A + B * C - D");
    assert(vars['F' - 'A'] == 5 + 8 * 16 - ((5 + 8) * 2));

    run(trace, "G = 2 ^ 3 ^ 2");  // 2^(3^2) = 2^9 = 512
    assert(vars['G' - 'A'] == 512);

    run(trace, "print(A)");
    run(trace, "print(B)");
    run(trace, "print(G)");

    run(trace, "H = (2 + 3) * (4 + 1)");
    assert(vars['H' - 'A'] == 25);

    run(trace, "I = -5 + 2");
    assert(vars['I' - 'A'] == -3);

    run(trace, "J   =   A   +    B");
    assert(vars['J' - 'A'] == vars['A' - 'A'] + vars['B' - 'A']);

    printf("Все тесты успешно пройдены!\n");

    fclose(trace);
    return 0;
}
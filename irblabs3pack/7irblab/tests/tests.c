#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "../include/functions.h"

// Объявляем глобальные переменные из functions.c
extern int vars[26];
extern int initialized[26];

void run(FILE *trace, const char *cmd, int *operation_counter) {
    char buf[MAX_LINE];
    strcpy(buf, cmd);
    process_line(trace, buf, operation_counter);
}

void reset_vars() {
    for (int i = 0; i < 26; i++) {
        vars[i] = 0;
        initialized[i] = 0;
    }
}

void test_valid_expressions(FILE *trace) {
    printf("Testing valid expressions...\n");
    reset_vars();
    int op_counter = 1;
    
    run(trace, "A = 5", &op_counter);
    assert(initialized['A' - 'A'] == 1);
    assert(vars['A' - 'A'] == 5);

    run(trace, "B = A + 3", &op_counter);
    assert(vars['B' - 'A'] == 8);

    run(trace, "C = B * 2", &op_counter);
    assert(vars['C' - 'A'] == 16);

    run(trace, "D = (A + B) * 2", &op_counter);
    assert(vars['D' - 'A'] == (5 + 8) * 2);

    run(trace, "E = 2 ^ 5", &op_counter);
    assert(vars['E' - 'A'] == 32);

    run(trace, "F = A + B * C - D", &op_counter);
    assert(vars['F' - 'A'] == 5 + 8 * 16 - ((5 + 8) * 2));

    run(trace, "G = 2 ^ 3 ^ 2", &op_counter);
    assert(vars['G' - 'A'] == 512);

    run(trace, "H = (2 + 3) * (4 + 1)", &op_counter);
    assert(vars['H' - 'A'] == 25);

    run(trace, "I = -5 + 2", &op_counter);
    assert(vars['I' - 'A'] == -3);

    run(trace, "J   =   A   +    B", &op_counter);
    assert(vars['J' - 'A'] == vars['A' - 'A'] + vars['B' - 'A']);

    run(trace, "print(A)", &op_counter);
    run(trace, "print(B)", &op_counter);
    run(trace, "print(G)", &op_counter);
}

void test_invalid_expressions(FILE *trace) {
    printf("Testing invalid expressions...\n");
    reset_vars();
    int op_counter = 1;
    
    // Некорректные имена переменных
    run(trace, "a = 5", &op_counter);  // строчная буква
    run(trace, "1A = 5", &op_counter); // начинается с цифры
    run(trace, "AB = 5", &op_counter); // две буквы
    
    // Некорректный синтаксис
    run(trace, "A = ", &op_counter);          // пустое выражение
    run(trace, "A = 5 + ", &op_counter);      // выражение заканчивается оператором
    run(trace, "A = + 5", &op_counter);       // начинается с бинарного оператора
    run(trace, "A = 5 + + 3", &op_counter);   // два оператора подряд
    run(trace, "A = (5 + 3", &op_counter);    // незакрытая скобка
    run(trace, "A = 5 + 3)", &op_counter);    // лишняя закрывающая скобка
    run(trace, "A = 5 & 3", &op_counter);     // недопустимый оператор
    run(trace, "print", &op_counter);         // print без скобок
    run(trace, "print(", &op_counter);        // print без переменной
    run(trace, "print()", &op_counter);       // print без аргумента
    run(trace, "print(A", &op_counter);       // print без закрывающей скобки
    run(trace, "print(AB)", &op_counter);     // print с двумя переменными
    
    // Деление на ноль
    run(trace, "K = 5 / 0", &op_counter);
    
    // Возведение нуля в отрицательную степень
    run(trace, "L = 0 ^ -2", &op_counter);
    
    printf("Invalid expressions handled correctly\n");
}

int main() {
    FILE *trace = fopen("test_trace.log", "w");
    assert(trace != NULL);

    test_valid_expressions(trace);
    test_invalid_expressions(trace);

    printf("Все тесты успешно пройдены!\n");

    fclose(trace);
    return 0;
}
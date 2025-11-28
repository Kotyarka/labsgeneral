#include "../include/functions.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

static void test_fast_power() {
    assert(fast_power(2, 3) == 8);
    assert(fast_power(5, 0) == 1);
    assert(fast_power(3, 4) == 81);
    assert(fast_power(2, 10) == 1024);
    assert(fast_power(7, 2) == 49);
}

static void test_assignment() {
    Interpreter interpreter;
    init_interpreter(&interpreter);
    
    FILE* log_file = fopen("test.log", "w");
    
    assert(execute_line(&interpreter, "A = 5", 1, log_file) == true);
    assert(interpreter.initialized[0] == true);
    assert(interpreter.variables[0] == 5);
    
    assert(execute_line(&interpreter, "B = A + 3", 2, log_file) == true);
    assert(interpreter.initialized[1] == true);
    assert(interpreter.variables[1] == 8);
    
    fclose(log_file);
}

static void test_arithmetic() {
    Interpreter interpreter;
    init_interpreter(&interpreter);
    
    FILE* log_file = fopen("test.log", "w");
    
    execute_line(&interpreter, "A = 10", 1, log_file);
    execute_line(&interpreter, "B = 3", 2, log_file);
    execute_line(&interpreter, "C = A + B * 2", 3, log_file);
    
    assert(interpreter.variables[2] == 16);
    
    execute_line(&interpreter, "D = A - B", 4, log_file);
    assert(interpreter.variables[3] == 7);
    
    execute_line(&interpreter, "E = A * B", 5, log_file);
    assert(interpreter.variables[4] == 30);
    
    execute_line(&interpreter, "F = A / B", 6, log_file);
    assert(interpreter.variables[5] == 3);
    
    fclose(log_file);
}

static void test_power() {
    Interpreter interpreter;
    init_interpreter(&interpreter);
    
    FILE* log_file = fopen("test.log", "w");
    
    execute_line(&interpreter, "A = 2", 1, log_file);
    execute_line(&interpreter, "B = 3", 2, log_file);
    execute_line(&interpreter, "C = A ^ B", 3, log_file);
    
    assert(interpreter.variables[2] == 8);
    
    execute_line(&interpreter, "D = 5 ^ 2", 4, log_file);
    assert(interpreter.variables[3] == 25);
    
    fclose(log_file);
}

static void test_invalid_syntax() {
    Interpreter interpreter;
    init_interpreter(&interpreter);
    
    FILE* log_file = fopen("test.log", "w");
    
    assert(execute_line(&interpreter, "print", 2, log_file) == false);
    assert(execute_line(&interpreter, "1 = 2", 3, log_file) == false);
    
    fclose(log_file);
}

void run_all_tests() {
    test_fast_power();
    test_assignment();
    test_arithmetic();
    test_power();
    test_invalid_syntax();
    
    printf("All tests passed!\n");
}

int main() {
    run_all_tests();
    return 0;
}
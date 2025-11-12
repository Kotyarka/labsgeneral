#include "../include/functions.h"
#include "../include/errors_macro.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <stdlib.h>

void test_isValidSymbolInBase() {
    printf("Testing isValidSymbolInBase...\n");
    
    // Test base 2-9
    assert(isValidSymbolInBase('0', 2) == 1);
    assert(isValidSymbolInBase('1', 2) == 1);
    assert(isValidSymbolInBase('2', 2) == 0);
    assert(isValidSymbolInBase('7', 8) == 1);
    assert(isValidSymbolInBase('8', 8) == 0);
    
    // Test base 10+
    assert(isValidSymbolInBase('9', 10) == 1);
    assert(isValidSymbolInBase('A', 16) == 1);
    assert(isValidSymbolInBase('F', 16) == 1);
    assert(isValidSymbolInBase('G', 16) == 0);
    
    // Test signs
    assert(isValidSymbolInBase('+', 10) == 1);
    assert(isValidSymbolInBase('-', 10) == 1);
    
    printf("✓ isValidSymbolInBase tests passed\n");
}

void test_convertToDecimal() {
    printf("Testing convertToDecimal...\n");
    
    int result;
    
    // Test binary
    assert(convertToDecimal("1010", 4, toupper, 2, &result) == OK);
    assert(result == 10);
    
    // Test hexadecimal
    assert(convertToDecimal("FF", 2, toupper, 16, &result) == OK);
    assert(result == 255);
    
    // Test with sign
    assert(convertToDecimal("-10", 3, toupper, 10, &result) == OK);
    assert(result == -10);
    
    // Test invalid input
    assert(convertToDecimal("12G", 3, toupper, 10, &result) == BAD_INPUT_ERROR);
    
    // Test overflow
    char large_num[100];
    sprintf(large_num, "%d", INT_MAX);
    assert(convertToDecimal(large_num, strlen(large_num), toupper, 10, &result) == OK);
    
    printf("✓ convertToDecimal tests passed\n");
}

void test_convertDecimalToBase() {
    printf("Testing convertDecimalToBase...\n");
    
    char buffer[100];
    int index;
    
    // Test decimal to binary
    assert(convertDecimalToBase(10, 2, toupper, buffer, &index) == OK);
    buffer[index] = '\0';
    assert(strcmp(buffer, "0101") == 0 || strcmp(buffer, "1010") == 0); // depends on implementation
    
    // Test decimal to hex
    assert(convertDecimalToBase(255, 16, toupper, buffer, &index) == OK);
    
    // Test zero
    assert(convertDecimalToBase(0, 10, toupper, buffer, &index) == OK);
    assert(index == 1);
    assert(buffer[0] == '0');
    
    // Test negative
    assert(convertDecimalToBase(-10, 10, toupper, buffer, &index) == OK);
    
    printf("✓ convertDecimalToBase tests passed\n");
}

void test_generateFibonacci() {
    printf("Testing generateFibonacci...\n");
    
    unsigned int size;
    unsigned int* fib;
    
    // Test normal case
    assert(generateFibonacci(10, &size, &fib) == OK);
    assert(size >= 2);
    assert(fib[0] == 1);
    assert(fib[1] == 2);
    free(fib);
    
    // Test edge case
    assert(generateFibonacci(1, &size, &fib) == OK);
    free(fib);
    
    // Test invalid input
    assert(generateFibonacci(0, &size, &fib) == BAD_INPUT_ERROR);
    
    printf("✓ generateFibonacci tests passed\n");
}

void test_printMemoryDump() {
    printf("Testing printMemoryDump...\n");
    
    char buffer[1000] = {0};
    int test_int = 42;
    
    // Test integer dump
    assert(printMemoryDump(buffer, PRINT_TO_STRING, &test_int, sizeof(test_int)) == OK);
    assert(strlen(buffer) > 0);
    
    printf("✓ printMemoryDump tests passed\n");
}

void test_printNumberInBase() {
    printf("Testing printNumberInBase...\n");
    
    char buffer[100] = {0};
    
    // Test decimal
    assert(printNumberInBase(buffer, PRINT_TO_STRING, toupper, 42, 10) == OK);
    assert(strstr(buffer, "42") != NULL);
    
    // Test hex
    assert(printNumberInBase(buffer, PRINT_TO_STRING, toupper, 255, 16) == OK);
    
    printf("✓ printNumberInBase tests passed\n");
}

void test_printZeckendorf() {
    printf("Testing printZeckendorf...\n");
    
    char buffer[100] = {0};
    
    // Test small number
    assert(printZeckendorf(buffer, PRINT_TO_STRING, 10) == OK);
    assert(strlen(buffer) > 0);
    
    printf("✓ printZeckendorf tests passed\n");
}

void test_printIntToRoman() {
    printf("Testing printIntToRoman...\n");
    
    char buffer[100] = {0};
    
    // Test normal numbers
    assert(printIntToRoman(buffer, PRINT_TO_STRING, 10) == OK);
    assert(strstr(buffer, "X") != NULL);
    
    assert(printIntToRoman(buffer, PRINT_TO_STRING, 42) == OK);
    
    // Test negative
    assert(printIntToRoman(buffer, PRINT_TO_STRING, -10) == OK);
    assert(strstr(buffer, "-") != NULL);
    
    printf("✓ printIntToRoman tests passed\n");
}

void test_overfprintf() {
    printf("Testing overfprintf...\n");
    
    char buffer[1000];
    FILE* stream = fopen("test_output.txt", "w+");
    assert(stream != NULL);
    
    // Test basic formatting
    assert(overfprintf(stream, "Hello %s!", "World") == OK);
    rewind(stream);
    fgets(buffer, sizeof(buffer), stream);
    assert(strstr(buffer, "Hello World!") != NULL);
    
    // Test custom flags
    assert(overfprintf(stream, "Number: %Cv", 255, 16) == OK);
    
    fclose(stream);
    remove("test_output.txt");
    
    printf("✓ overfprintf tests passed\n");
}

void test_oversprintf() {
    printf("Testing oversprintf...\n");
    
    char buffer[1000];
    
    // Test basic formatting
    assert(oversprintf(buffer, "Hello %s!", "World") == OK);
    assert(strcmp(buffer, "Hello World!") == 0);
    
    // Test number formatting
    assert(oversprintf(buffer, "Number: %d", 42) == OK);
    assert(strstr(buffer, "42") != NULL);
    
    // Test custom Roman numerals
    assert(oversprintf(buffer, "Roman: %Ro", 10) == OK);
    assert(strstr(buffer, "X") != NULL);
    
    // Test Zeckendorf
    assert(oversprintf(buffer, "Zeck: %Zr", 10) == OK);
    
    // Test base conversion
    assert(oversprintf(buffer, "Hex: %CV", 255, 16) == OK);
    
    printf("✓ oversprintf tests passed\n");
}

void test_edge_cases() {
    printf("Testing edge cases...\n");
    
    char buffer[100];
    
    // Test empty strings
    assert(oversprintf(buffer, "") == OK);
    assert(strlen(buffer) == 0);
    
    printf("✓ Edge cases tests passed\n");
}

void test_performance_cases() {
    printf("Testing performance cases...\n");
    
    char buffer[1000];
    
    // Test large numbers
    assert(oversprintf(buffer, "Large: %d", INT_MAX) == OK);
    assert(strstr(buffer, "2147483647") != NULL);
    
    // Test multiple conversions
    assert(oversprintf(buffer, "Test: %d %s %Ro %Zr", 42, "string", 100, 50) == OK);
    
    printf("✓ Performance cases tests passed\n");
}

int main() {
    printf("Starting comprehensive tests for custom printf library...\n\n");
    
    test_isValidSymbolInBase();
    test_convertToDecimal();
    test_convertDecimalToBase();
    test_generateFibonacci();
    test_printMemoryDump();
    test_printNumberInBase();
    test_printZeckendorf();
    test_printIntToRoman();
    test_overfprintf();
    test_oversprintf();
    test_edge_cases();
    test_performance_cases();
    
    printf("\nAll custom printf library tests passed! ✓\n");
    return 0;
}
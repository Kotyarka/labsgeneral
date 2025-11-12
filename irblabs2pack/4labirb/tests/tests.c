#include "../include/functions.h"
#include <regex.h>
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

void test_isValidSymbolInBase() {
    printf("Testing isValidSymbolInBase...\n");
    
    // Test base 10
    assert(isValidSymbolInBase('0', 10) == 1);
    assert(isValidSymbolInBase('9', 10) == 1);
    assert(isValidSymbolInBase('A', 10) == 0);
    assert(isValidSymbolInBase('+', 10) == 1);
    assert(isValidSymbolInBase('-', 10) == 1);
    
    // Test base 16
    assert(isValidSymbolInBase('0', 16) == 1);
    assert(isValidSymbolInBase('9', 16) == 1);
    assert(isValidSymbolInBase('A', 16) == 1);
    assert(isValidSymbolInBase('F', 16) == 1);
    assert(isValidSymbolInBase('G', 16) == 0);
    
    // Test base 2
    assert(isValidSymbolInBase('0', 2) == 1);
    assert(isValidSymbolInBase('1', 2) == 1);
    assert(isValidSymbolInBase('2', 2) == 0);
    
    printf("isValidSymbolInBase tests passed!\n\n");
}

void test_zeckendorfToInt() {
    printf("Testing zeckendorfToInt...\n");
    
    unsigned int result;
    
    // Test valid Zeckendorf representations
    assert(zeckendorfToInt("11", &result) == OK);
    assert(result == 1); // 3
    
    assert(zeckendorfToInt("1011", &result) == OK);
    assert(result == 1 + 3); // 4
    
    // Test error cases
    assert(zeckendorfToInt(NULL, &result) == BAD_POINTER_ERROR);
    assert(zeckendorfToInt("11", NULL) == BAD_POINTER_ERROR);
    
    printf("zeckendorfToInt tests passed!\n\n");
}

void test_romanToInt() {
    printf("Testing romanToInt...\n");
    
    int result;
    
    // Test valid Roman numerals
    assert(romanToInt("I", &result) == OK);
    assert(result == 1);
    
    assert(romanToInt("IV", &result) == OK);
    assert(result == 4);
    
    assert(romanToInt("IX", &result) == OK);
    assert(result == 9);
    
    assert(romanToInt("XLII", &result) == OK);
    assert(result == 42);
    
    assert(romanToInt("CXXIII", &result) == OK);
    assert(result == 123);
    
    // Test invalid Roman numerals
    assert(romanToInt("IIII", &result) == BAD_INPUT_ERROR);
    assert(romanToInt("VV", &result) == BAD_INPUT_ERROR);
    
    // Test error cases
    assert(romanToInt(NULL, &result) == BAD_POINTER_ERROR);
    assert(romanToInt("I", NULL) == BAD_POINTER_ERROR);
    
    printf("romanToInt tests passed!\n\n");
}

void test_convertToDecimal() {
    printf("Testing convertToDecimal...\n");
    
    int result;
    
    // Test base 10
    assert(convertToDecimal("123", 3, toupper, 10, &result) == OK);
    assert(result == 123);
    
    assert(convertToDecimal("-456", 4, toupper, 10, &result) == OK);
    assert(result == -456);
    
    // Test base 16 lowercase
    assert(convertToDecimal("1a", 2, tolower, 16, &result) == OK);
    assert(result == 26);
    
    // Test base 16 uppercase
    assert(convertToDecimal("1A", 2, toupper, 16, &result) == OK);
    assert(result == 26);
    
    // Test base 2
    assert(convertToDecimal("1010", 4, toupper, 2, &result) == OK);
    assert(result == 10);
    
    // Test error cases
    assert(convertToDecimal(NULL, 3, toupper, 10, &result) == BAD_POINTER_ERROR);
    assert(convertToDecimal("123", 3, NULL, 10, &result) == BAD_POINTER_ERROR);
    assert(convertToDecimal("123", 3, toupper, 10, NULL) == BAD_POINTER_ERROR);
    
    // Test invalid symbols
    assert(convertToDecimal("12G", 3, toupper, 10, &result) == BAD_INPUT_ERROR);
    
    printf("convertToDecimal tests passed!\n\n");
}

void test_overfscanf_basic() {
    printf("Testing overfscanf basic functionality...\n");
    
    FILE* test_file = fopen("test_input.txt", "w+");
    assert(test_file != NULL);
    
    // Write test data
    fprintf(test_file, "42 hello 3.14");
    rewind(test_file);
    
    int int_val;
    char str_val[20];
    double double_val;
    
    // Test basic scanf functionality
    assert(overfscanf(test_file, "%d %s %lf", &int_val, str_val, &double_val) == OK);
    assert(int_val == 42);
    assert(strcmp(str_val, "hello") == 0);
    assert(double_val == 3.14);
    
    fclose(test_file);
    remove("test_input.txt");
    
    printf("overfscanf basic tests passed!\n\n");
}


void test_custom_scan_flags() {
    printf("Testing custom scan flags...\n");
    
    // Test Roman numerals
    const char* roman_test = "XLII";
    int roman_result;
    assert(oversscanf(roman_test, "%Ro", &roman_result) == OK);
    assert(roman_result == 42);
    
    // Test Zeckendorf
    const char* zeck_test = "1011";
    unsigned int zeck_result;
    assert(oversscanf(zeck_test, "%Zr", &zeck_result) == OK);
    assert(zeck_result == 4);
    
    // Test base conversion uppercase
    const char* base_test_upper = "1A";
    int base_result_upper;
    assert(oversscanf(base_test_upper, "%CV", &base_result_upper, 16) == OK);
    assert(base_result_upper == 26);
    
    printf("Custom scan flags tests passed!\n\n");
}

void test_error_handling() {
    printf("Testing error handling...\n");
    
    // Test NULL pointers
    assert(overfscanf(NULL, "%d", NULL) == BAD_POINTER_ERROR);
    assert(oversscanf(NULL, "%d", NULL) == BAD_POINTER_ERROR);
    
    // Test with invalid file
    FILE* invalid_file = NULL;
    int val;
    assert(overfscanf(invalid_file, "%d", &val) == BAD_POINTER_ERROR);
    
    printf("Error handling tests passed!\n\n");
}

void run_all_tests() {
    printf("=== Starting All Tests ===\n\n");
    
    test_isValidSymbolInBase();
    test_zeckendorfToInt();
    test_romanToInt();
    test_convertToDecimal();
    test_overfscanf_basic();
    test_custom_scan_flags();
    test_error_handling();
    
    printf("=== All Tests Passed! ===\n");
}

int main() {
    run_all_tests();
    return 0;
}
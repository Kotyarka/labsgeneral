#include "../include/include.h"
#include <stdio.h>
#include <assert.h>

void test_bad_base() {
    printf("Testing bad base...\n");
    int results[3];
    errorCodes result = isFinitePresent(1, results, 3, 0.3, 0.25, 0.1);
    assert(result == BAD_BASE);
    
    result = isFinitePresent(0, results, 3, 0.3, 0.25, 0.1);
    assert(result == BAD_BASE);
    printf("✓ Bad base test passed\n");
}

void test_pointer_error() {
    printf("Testing pointer error...\n");
    errorCodes result = isFinitePresent(3, NULL, 3, 0.3, 0.25, 0.1);
    assert(result == POINTER_ERROR);
    printf("✓ Pointer error test passed\n");
}

void test_wrong_arguments() {
    printf("Testing wrong arguments...\n");
    int results[3];
    errorCodes result = isFinitePresent(3, results, 0, 0.3, 0.25, 0.1);
    assert(result == WRONG_ARGUMENTS);
    
    result = isFinitePresent(3, results, -1, 0.3, 0.25, 0.1);
    assert(result == WRONG_ARGUMENTS);
    printf("✓ Wrong arguments test passed\n");
}

void test_bad_input() {
    printf("Testing bad input...\n");
    int results[3];
    errorCodes result = isFinitePresent(3, results, 3, 1.5, 0.25, 0.1);
    assert(result == BAD_INPUT);
    
    result = isFinitePresent(3, results, 3, -0.5, 0.25, 0.1);
    assert(result == BAD_INPUT);
    
    result = isFinitePresent(3, results, 3, 1.0, 0.25, 0.1);
    assert(result == BAD_INPUT);
    printf("✓ Bad input test passed\n");
}

void test_finite_numbers() {
    printf("Testing finite numbers...\n");
    int results[3];
    errorCodes result = isFinitePresent(3, results, 3, 0.3333333333333333, 0.25, 0.5);
    assert(result == OK);
    assert(results[0] == 1); 
    assert(results[1] == 0); 
    assert(results[2] == 0); 
    printf("✓ Finite numbers test passed\n");
}

void test_infinite_numbers() {
    printf("Testing infinite numbers...\n");
    int results[3];
    errorCodes result = isFinitePresent(2, results, 3, 0.1, 0.2, 0.3);
    assert(result == OK);
    assert(results[0] == 0); 
    assert(results[1] == 0);  
    assert(results[2] == 0); 
    printf("✓ Infinite numbers test passed\n");
}

void test_mixed_numbers() {
    printf("Testing mixed numbers...\n");
    int results[4];
    errorCodes result = isFinitePresent(10, results, 3, 0.5, 0.25, 0.1);
    assert(result == OK);
    assert(results[0] == 1); 
    assert(results[1] == 1); 
    assert(results[2] == 1); 
    printf("✓ Mixed numbers test passed\n");
}

void test_edge_cases() {
    printf("Testing edge cases...\n");
    int results[5];
    
    errorCodes result = isFinitePresent(10, results, 4, 
        0.5, 
        0.25,  
        0.125, 
        0.2
    );
    assert(result == OK);
    assert(results[0] == 1);
    assert(results[1] == 1);
    assert(results[2] == 1);
    assert(results[3] == 1);
    
    result = isFinitePresent(2, results, 3, 0.5, 0.25, 0.1);
    assert(result == OK);
    assert(results[0] == 1);
    assert(results[1] == 1);
    assert(results[2] == 0);
    
    printf("✓ Edge cases test passed\n");
}

void test_single_number() {
    printf("Testing single number...\n");
    int results[1];
    errorCodes result = isFinitePresent(10, results, 1, 0.5);
    assert(result == OK);
    assert(results[0] == 1);
    printf("✓ Single number test passed\n");
}

int main() {
    printf("Starting comprehensive tests for isFinitePresent function...\n\n");
    
    test_bad_base();
    test_pointer_error();
    test_wrong_arguments();
    test_bad_input();
    test_finite_numbers();
    test_infinite_numbers();
    test_mixed_numbers();
    test_edge_cases();
    test_single_number();
    
    printf("\nAll internal tests passed! ✓\n");
    return 0;
}